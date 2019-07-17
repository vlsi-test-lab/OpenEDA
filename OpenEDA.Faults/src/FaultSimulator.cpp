/**
 * @file FaultSimulator.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-21
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "FaultSimulator.h"
#include "ValueVectorFunctions.hpp"

template<class _primitive>
FaultSimulator<_primitive>::FaultSimulator(bool _tdfEnable) {
	this->tdfEnable_ = _tdfEnable;
}

template<class _primitive>
FaultSimulator<_primitive>::~FaultSimulator() {
	this->clearFaults();
}

/*
 * Given a "faulty" value and the current line value, set what the faulty value
 * will be when active (i.e., modifiy it) as well as a mask of what values may
 * change in future fault simulation simulations (i.e., for TDFs).
 *
 * NOTE: inputs are modified through reference.
 *
 * @param _faultyValue The value to appear in the circuit during simulation.
 * @param _lineValue The value of the line in the circuit (where the fault is).
 * @param _mask The mask of values which may be affected for future iterations.
 * @param _same When calculating the mask, do we want unknown circuit values to
 *              be the same as or different than the fault? (FOR TDF: first vec
 *              is true, second vec is false.
 * @return Will the fault matter, i.e., will it have an effect on the circuit.
 */
template<class _primitive>
bool maskAndModify(
	Value<_primitive> & _faultyValue,
	Value<_primitive> & _lineValue,
	_primitive & _mask,
	bool _same
) {
	//Any non-valid values on the line need to be made the opposite magnitude as the fault.
	_primitive toForce = ~_lineValue.valid(); //The non-valid bits.
	_primitive toFlip;
	if (_same) {
		toFlip = _lineValue.magnitude() ^ _faultyValue.magnitude();
	} else {
		toFlip = _lineValue.magnitude() ^ ~(_faultyValue.magnitude());
	}
	toFlip = toFlip & toForce;
	_lineValue.magnitude(toFlip ^ _lineValue.magnitude());

	if (_same) {
		_mask = ~(_faultyValue.magnitude() ^ _lineValue.magnitude()) & _mask;
	} else {
		_mask = (_faultyValue.magnitude() ^ _lineValue.magnitude()) & _mask;
	}

	_primitive changedMagnitude = _mask; //It just so happened that the mask is the same as magnitudes the flip. Not necessarly the same as valids to flip.
	_primitive changedValids = ~_lineValue.valid();
	if (_same == false) {
		_faultyValue.magnitude(_lineValue.magnitude() ^ changedMagnitude);
		changedValids = (~changedValids ^ _faultyValue.valid()) & _mask;
		_faultyValue.valid(_lineValue.valid() ^ changedValids);
	} else {
		changedValids = changedValids & _mask;
		_faultyValue.valid(_faultyValue.valid() ^ changedValids);
	}


	return changedMagnitude | changedValids;
}

template<>
bool maskAndModify(
	Value<bool> & _faultyValue,
	Value<bool> & _lineValue,
	bool & _mask,
	bool _same
) {
	//Any non-valid values on the line need to be made the opposite magnitude as the fault.
	bool toForce = !_lineValue.valid(); //The non-valid bits.
	bool toFlip;
	if (_same) {
		toFlip = _lineValue.magnitude() ^ _faultyValue.magnitude();
	} else {
		toFlip = _lineValue.magnitude() ^ !(_faultyValue.magnitude());
	}
	toFlip = toFlip & toForce;
	_lineValue.magnitude(toFlip ^ _lineValue.magnitude());

	if (_same) {
		_mask = !(_faultyValue.magnitude() ^ _lineValue.magnitude()) & _mask;
	} else {
		_mask = (_faultyValue.magnitude() ^ _lineValue.magnitude()) & _mask;
	}

	bool changedMagnitude = _mask; //It just so happened that the mask is the same as magnitudes the flip. Not necessarly the same as valids to flip.
	bool changedValids = !_lineValue.valid();
	if (_same == false) {
		_faultyValue.magnitude(_lineValue.magnitude() ^ changedMagnitude);
		changedValids = (!changedValids ^ _faultyValue.valid()) & _mask;
		_faultyValue.valid(_lineValue.valid() ^ changedValids);
	} else {
		changedValids = changedValids & _mask;
		_faultyValue.valid(_faultyValue.valid() ^ changedValids);
	}


	return changedMagnitude | changedValids;
}


template<class _primitive>
std::vector<Value<_primitive>> FaultSimulator<_primitive>::applyStimulus(
	Circuit * _circuit, 
	std::vector<Value<_primitive>> _stimulus,
	EventQueue<_primitive> _simulationQueue,
	std::vector<SimulationNode<_primitive>*> _inputs,
	std::vector<SimulationNode<_primitive>*> _outputs,
	std::vector<bool> _observe
)
{	
	//Populated (observable) output list (if not given)
	if (_outputs.empty() == true) {
		for (Levelized* output : _circuit->pos()) {
			_outputs.push_back(dynamic_cast<SimulationNode<_primitive>*>(output));
		}
	}
	if (_observe.empty() == true) {
		_observe = std::vector<bool>(_outputs.size(), true);
	} else if (_observe.size() != _outputs.size()) {
		throw "_outputs/_observe size mismach during fault simulation.";
	}

	//Chose (and conditionally modifiy) which faults to simulation.
	//This structure contains the list of faults to simulate and the fault's original value:
	// the fault's "value" may be changed during simulation if some bits of the faults will
	// not have an impact during simulation. This is only needed because of TDF simulation.
	//This structure also contains a "mask" of values to simulate.
	std::vector<
		std::pair<
				Fault<_primitive>* , //The fault, .first
				std::pair<
					Value<_primitive>, //The fault's original value, .first.first
					_primitive         //The mask of the fault (for s-a-f simulation, should be all 1s), .first.second
				>
		>
	> faultsToSimulate;

	for (Fault<_primitive>* fault : this->undetectedFaults_) {
		Value<_primitive> faultValue = fault->value();
		_primitive mask = (_primitive) 0xFFFFFFFFFFFFFFFF;
		if (this->tdfEnable_ == true) {
			Value<_primitive> newFaultValue = faultValue;
			Value<_primitive> lineValue = fault->location()->value();
			maskAndModify<_primitive>(newFaultValue, lineValue, mask, true);
			fault->value(
				std::vector <Value<_primitive>>(1, newFaultValue)
			);
		}

		faultsToSimulate.push_back(
			std::pair<Fault<_primitive>*, std::pair<Value<_primitive>, _primitive>>(
				fault,
				std::pair<Value<_primitive>, _primitive>(
					faultValue, 
					mask
				)
			)
		);
	}



	//Obatin the "non-faulty" state.
	std::vector<Value<_primitive>> goodOutputs  = this->Simulator<_primitive>::applyStimulus(_circuit, _stimulus, _simulationQueue, _inputs, _outputs, _observe);
	//DELETE: not needed. this->Simulator<_primitive>::applyStimulus(_circuit,  _stimulus,  _simulationQueue, _inputs);
	//DELETE: not needed. std::vector<Value<_primitive>> goodOutputs = this->outputs(_circuit);

	//Obtain all faults which are "worth simulating".
	auto it = faultsToSimulate.begin();
	while (it != faultsToSimulate.end()) {
		std::pair<Fault<_primitive>*, std::pair<Value<_primitive>, _primitive > > entry = *it;
		Fault<_primitive>* fault = entry.first;
		Value<_primitive> faultValue = fault->value();
		Value<_primitive> curentCircuitValue = fault->location()->value();
		_primitive mask = entry.second.second;
		if (
			maskAndModify<_primitive>(faultValue, curentCircuitValue, mask, false) == true
			) { //A chnage will be made by this fault.
			fault->value(
				std::vector<Value<_primitive>>(
					1,
					faultValue
					)
			);
			++it;
		
		} else { //... else, remove it from the list (and restore the fault's effect).
			Value<_primitive> originalFaultValue = entry.second.first;
			fault->value(std::vector<Value<_primitive>>(
				1,
				originalFaultValue)
			);
			it = faultsToSimulate.erase(it);
		}
	}


	//Simulate every fault.
	for (auto entry : faultsToSimulate) {
		Fault<_primitive>* fault = entry.first;
		
		_simulationQueue.add(fault->go()); //NOTE: "Go" will toggle the activation of the fault and return all new events from this (de)activation.
		//DELETE do we need this? this->Simulator<_primitive>::applyStimulus(_circuit, _stimulus, _simulationQueue, _inputs);
		_simulationQueue.process();
		std::vector<Value<_primitive>> faultyOutputs = this->outputs(_circuit, _outputs, _observe);
		if (ValueVectorFunction<_primitive>::mismatch(goodOutputs, faultyOutputs, _observe) == true) {
			this->undetectedFaults_.erase(fault);
			this->detectedFaults_.emplace(fault);
		}

		Value<_primitive> originalFaultValue = entry.second.first;
		fault->value(std::vector<Value<_primitive>>(
			1,
			originalFaultValue)
			);
		
		_simulationQueue.add(fault->go()); //NOTE: "Go" will toggle the activation of the fault and return all new events from this (de)activation.
		//DEBUG: I want to know ALL stimulus generated by a fault alone.
		_simulationQueue.process();
		
	}

	//Reset the state of the circuit. //NOTE: is this step needed?
	this->Simulator<_primitive>::applyStimulus(_circuit, _stimulus, _simulationQueue, _inputs, _outputs, _observe);
	return goodOutputs;
}

template<class _primitive>
void FaultSimulator<_primitive>::setFaults(std::unordered_set<Fault<_primitive>*> _faults) {
	this->clearFaults();
	this->undetectedFaults_ = _faults;
}

template<class _primitive>
void FaultSimulator<_primitive>::resetFaults() {
	this->undetectedFaults_.insert(this->detectedFaults_.begin(), this->detectedFaults_.end());
	this->detectedFaults_.clear();
}



template<class _primitive>
std::unordered_set<Fault<_primitive>*> FaultSimulator<_primitive>::detectedFaults() {
	return this->detectedFaults_;
}

template<class _primitive>
float FaultSimulator<_primitive>::faultcoverage() {
	
	float fc = (float) detectedFaults_.size() /((float) detectedFaults_.size() + (float) undetectedFaults_.size());
	return fc*100;
}




template<class _primitive>
bool FaultSimulator<_primitive>::hasImpact(Fault<_primitive>* _fault) {
	Value<_primitive> curLineValue = _fault->location()->value();
	Value<_primitive> faultValue = _fault->value();
	return curLineValue != faultValue;
}

template<class _primitive>
bool FaultSimulator<_primitive>::notExcited(Fault<_primitive>* _fault) {
	Value<_primitive> curLineValue = _fault->location()->value();
	Value<_primitive> faultValue = _fault->value();
	if (curLineValue.valid() == false || faultValue.valid() == false) {
		return false;
	}
	return curLineValue.magnitude() == faultValue.magnitude();
}

template<class _primitive>
void FaultSimulator<_primitive>::clearFaults() {
	for (Fault<_primitive>* fault : this->detectedFaults_) {
		delete fault;
	}
	this->detectedFaults_.clear();
	for (Fault<_primitive>* fault : this->undetectedFaults_) {
		delete fault;
	}
	this->undetectedFaults_.clear();
}

template class FaultSimulator<bool>;
template class FaultSimulator<unsigned long long int>;