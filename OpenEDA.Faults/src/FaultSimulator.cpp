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
std::vector<Value<_primitive>> FaultSimulator<_primitive>::applyStimulus(Circuit * _circuit, 
																		 std::vector<Value<_primitive>> _stimulus,
																		 EventQueue<_primitive> _simulationQueue,
																		 std::vector<SimulationNode<_primitive>*> _inputs) 
{
	//Obatin the "non-faulty" state.
	this->Simulator<_primitive>::applyStimulus(_circuit, _stimulus, _simulationQueue, _inputs);
	std::vector<Value<_primitive>> goodOutputs = this->outputs(_circuit);

	//Obtain all faults which are "worth simulating".
	std::unordered_set<Fault<_primitive>> faults;
	for (Fault<_primitive> fault : this->undetectedFaults_) {
		if (this->hasImpact(fault) == true) {
			faults.emplace(fault);
		}
	}

	//Simulate every fault.
	for (Fault<_primitive> fault : faults) {
		fault.activate(); _simulationQueue.add(0, fault);
		this->Simulator<_primitive>::applyStimulus(_circuit, _stimulus, _simulationQueue, _inputs);
		std::vector<Value<_primitive>> faultyOutputs = this->outputs(_circuit);
		if (ValueVectorFunction<_primitive>::mismatch(goodOutputs, faultyOutputs)) { //The fault is detected.
			this->undetectedFaults_.erase(fault);
			this->detectedFaults_.emplace(fault);
		}
		fault.activate(); _simulationQueue.add(0, fault);
	}

	//Reset the state of the circuit. //NOTE: is this step needed?
	this->Simulator<_primitive>::applyStimulus(_circuit, _stimulus, _simulationQueue, _inputs);
	return goodOutputs;
}

template<class _primitive>
void FaultSimulator<_primitive>::setFaults(std::unordered_set<Fault<_primitive>> _faults) {
	this->undetectedFaults_ = _faults;
	this->detectedFaults_.clear();
}

template<class _primitive>
std::unordered_set<Fault<_primitive>> FaultSimulator<_primitive>::detectedFaults() {
	return this->detectedFaults_;
}
