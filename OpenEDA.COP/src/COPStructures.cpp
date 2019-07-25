/**
 * @file COPStructures.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-04
 *
 * @copyright Copyright (c) 2019
 *
 */

#include <vector>
#include "ValueVectorFunctions.hpp"

#include "COPStructures.h"

COP::COP(bool _calculateAlways) {
	this->controllability_ = -1;
	this->observability_ = -1;
	this->calculateAlways_ = _calculateAlways;
}


float COP::controllability() {
	if (this->controllability_ >= 0) {
		//DEBUG printf("DBG CC %s (%d outputs) = %f (no calc)\n", this->name().c_str(), this->outputs().size(), this->controllability_);//DEBUG
		return this->controllability_;
	}

	//DELETE: Flawed and redundant.
	//if (this->inputs().size() == 1) { //This has only one input, so forward the call.
	//	Connecting* input = *(this->inputs().begin());
	//	COP* cast = dynamic_cast<COP*>(input);
	//	this->controllability_ = cast->controllability();
	//} else if (this->inputs().size() == 0) { //We have a problem.
	//	throw "Cannot calculate COP CC: no values to calculate from.";
	//} else { //Multiple inputs, calculate as defined.
	//	this->controllability_ = this->calculateControllability();
	//	if (this->controllability_ < 0) {
	//		throw "Cannot calculate COP CC: failure to calculate.";
	//	}
	//}
	this->controllability_ = this->calculateControllability();
	if (this->controllability_ < 0) {
		throw "Cannot calculate COP CC: failure to calculate.";
	}
	//DEBUG printf("DBG CC %s (%d outputs) = %f (calc)\n", this->name().c_str(), this->outputs().size(), this->controllability_);//DEBUG
	return this->controllability_;
}

float COP::controllability(float _controllability) {
	this->controllability_ = _controllability;
	return this->controllability_;
}

float COP::observability(COP* _calling) {
	if (this->observability_ >= 0) {
		//DEBUG printf("DBG CO %s (%d outputs) = %f (no calc)\n", this->name().c_str(), this->outputs().size(), this->observability_);//DEBUG
		return this->observability_;
	}

	//DELETE: flawed and redundant.
	//if (this->outputs().size() == 1) { //This has only one outputs, so forward the call.
	//	COP* cast = dynamic_cast<COP*>((*this->outputs().begin()));
	//	this->observability_ = cast->observability(this);
	//} else if (this->outputs().size() == 0) { //We have a problem.
	//	throw "Cannot calculate COP CO: no values to calculate from.";
	//} else { //Multiple outputs, calculate as defined.
	//	float toReturn = this->calculateObservability(_calling);
	//	if (toReturn < 0) {
	//		throw "Cannot calculate COP CC: failure to calculate.";
	//	}
	//	if (this->calculateAlways_ == true) {
	//		return toReturn;
	//	}
	//	this->observability_ = toReturn;
	//}
	float toReturn = this->calculateObservability(_calling);
	if (toReturn < 0) {
		throw "Cannot calculate COP CO: failure to calculate.";
	}
	//DEBUG printf("DBG CO %s (%d outputs) = %f (no calc)\n", this->name().c_str(), this->outputs().size(), toReturn);//DEBUG
	if (this->calculateAlways_ == true) {
		return toReturn;
	}
	this->observability_ = toReturn;
	return this->observability_;
}

float COP::observability(float _observability) {
	this->observability_ = _observability;
	return this->observability_;
}

//DELETE: flawed
//void COP::removeInput(Connecting * _rmv) {
//	this->clearControllability();
//	this->Connecting::removeInput(_rmv);
//}
//
//void COP::removeOutput(Connecting * _rmv) {
//	this->clearObservability();
//	this->Connecting::removeOutput(_rmv);
//}
//
//void COP::addInput(Connecting * _add) {
//	this->clearControllability();
//	this->Connecting::addInput(_add);
//}
//
//void COP::addOutput(Connecting * _add) {
//	this->clearObservability();
//	this->Connecting::addOutput(_add);
//}

void COP::clearObservability() {
	//DEBUG printf("DBG CO CLEAR %s (%d outputs) ... ", this->name().c_str(), this->outputs().size());//DEBUG
	if (this->observability_ < 0 && this->calculateAlways_ == false) { //Already cleared
		//DEBUG printf("STOP: %f %d\n", this->observability_, this->calculateAlways_);//DEBUG
		return;
	}
	this->observability_ = -1;
	std::unordered_set<Connecting*> inputs = this->inputs();
	//DEBUG printf("DONE, forward to %d\n", inputs.size());
	for (Connecting * input : inputs) {
		COP* cast = dynamic_cast<COP*>(input);
		if (cast != nullptr) {
			//A SPECIAL NOTE:
			//This is one of the few places where casting to a nullptr is allowed. When a node is deleted, it will
			//call "clear observability/controllability" on itself. The controllability call will lead to clear
			//observability calls coming back to it, but by this time, the node will no longer be considered "COP"
			//(since it is in the process of being deconstructed). To avoid this, nullptrs are skipped.
			cast->clearObservability();
		}
	}
}

void COP::clearControllability() {
	if (this->controllability_ < 0 && this->calculateAlways_ == false) { //Already cleared
		return;
	}
	//DEBUG printf("DBG CC CLEAR %s (%d outputs)\n", this->name().c_str(), this->outputs().size());//DEBUG
	this->controllability_ = -1;
	std::unordered_set<Connecting*> outputs = this->outputs();
	for (Connecting * output : outputs) {
		COP* cast = dynamic_cast<COP*>(output);
		cast->clearControllability();

		//Change CC can change CO on "parallel" lines (e.g., the lines feeding the
		//same gate). NOTE: see deleted segment below.
		for (Connecting * possiblyParralInput : output->inputs()) {
			if (possiblyParralInput != this) {
				COP* parallelInput = dynamic_cast<COP*>(possiblyParralInput);
				parallelInput->clearObservability();
			}
		}
	}

	//DELETE, bad performance: Because the clearControllability call will always go forward,
	//the clearObservability call be be done directly here instead of finding
	//what objects are "in parallel" with this one.
	//this->clearObservability();
}

void COP::removeInputConnection(Connection * _rmv, bool _deleteConnection) {
	this->clearControllability();
	this->Levelized::removeInputConnection(_rmv, _deleteConnection);
}

void COP::removeOutputConnection(Connection * _rmv, bool _deleteConnection) {
	this->clearObservability();
	this->Levelized::removeOutputConnection(_rmv, _deleteConnection);
}

void COP::addInputConnection(Connection * _add) {
	this->clearControllability();
	this->Levelized::addInputConnection(_add);
}

void COP::addOutputConnection(Connection * _add) {
	this->clearObservability();
	this->Levelized::addOutputConnection(_add);
}

template<class _width>
COPLine<_width>::COPLine() : 
	COP(false) , 
	SimulationLine<_width>() 
{
}

template<class _width>
COPLine<_width>::COPLine(std::string _name) :
	COP(false),
	SimulationLine<_width>(_name),
	Connecting(_name)
{
}
template<class _width>
float COPLine<_width>::calculateControllability() {
	if (this->inputs().size() != 1) {
		throw "Cannot calculate COPLine controllability: need exactly 1 input.";
	}
	COP* cast = dynamic_cast<COP*>(*(this->inputs().begin()));
	float toReturn = cast->controllability();
	if (toReturn > 1 || toReturn < 0) {
		throw "CO fail.";
	}
	return toReturn;
}

template<class _width>
float COPLine<_width>::calculateObservability(COP * _calling) {
	if (this->outputs().size() == 0) {
		return 0.0;
		//DELETE: incorrect. throw "A line with no outputs cannot calculate its observability.";
	}
	float toReturn = 1;
	for (Connecting* output : this->outputs()) {
		COP* cast = dynamic_cast<COP*>(output);
		float other = cast->observability(this);
		toReturn *= (1 - other);
		//DELETE: flawed. toReturn = other > toReturn ? other : toReturn;
	}
	toReturn = 1 - toReturn;
	if (toReturn > 1 || toReturn < 0) {
		throw "CO fail.";
	}
	return toReturn;
}

template<class _width>
Connecting* COPLine<_width>::clone() {
	return new COPLine<_width>(this->name());
}

/*
 * Count the number of 1s in a number
 *
 * https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetNaive
 */
//NOTE: this function is not actually used for anything, but it's kept here for reference.
template<class _width>
unsigned long int numOnes(_width v) {
	unsigned long int c; // c accumulates the total bits set in v
	for (c = 0; v; c++) {
		v &= v - 1; // clear the least significant bit set
	}
	return c;
}

/*
 * Manually calculate COP for a given node.
 */
template<class _width>
float manualCOP(COPNode<_width>* node, std::vector<float> inputControllabilities) {
	Function<_width>* func = dynamic_cast<Function<_width>*>(node->function());
	//TODO: what's the "initial" value?
	std::vector<Value<_width>> nodeInputVals = std::vector<Value<_width>>(node->inputs().size(), Value<_width>((_width)0x0));
	float ret = 0.0;
	do {
		Value<_width> outVal = func->evaluate(nodeInputVals);
		_width valid = outVal.valid();
		_width magnitude = outVal.magnitude();
		_width inputMask = (_width)0x1;//Which input values are we currently looking at?
		while (valid) {//There's at least one valid output to measure.
			if (valid & magnitude & 0x1) { //We have a valid 1, so calculate the prob. of it occuring.
				float prob = 1;
				for (size_t a = 0; a < nodeInputVals.size(); a++) {
					if (nodeInputVals.at(a).magnitude() & inputMask) { //Input is a 1
						prob = prob * (inputControllabilities.at(a));
					} else { //Input is a 0
						prob = prob * (1 - inputControllabilities.at(a));
					}
				}
				ret = ret + prob;
			}
			valid = valid >> 1;
			magnitude = magnitude >> 1;
			inputMask = inputMask << 1;
		}
		
	} while (ValueVectorFunction<_width>::increment(nodeInputVals) == true);

	return ret;
}

template<class _width>
float COPNode<_width>::calculateControllability() {
	//First, get the input controllabilities.
	std::vector<float> inputControllabilities;
	for (Connecting* input : this->inputs()) {
		COP* cast = dynamic_cast<COP*>(input);
		inputControllabilities.push_back(cast->controllability());
	}

	//Second, calculate depending on the gate type.
	float toReturn = 1.0;
	Function<_width>* function = this->function();
	std::string functionName = function->string();
	if (functionName == "pi") {
		return 0.5;
	} else if (functionName == "const") {
		Value<_width> value = function->evaluate(std::vector<Value<_width>>());
		if (value.valid() == false) {
			throw "Cannot calculate COP CC: constant value is not valid.";
		}
		if (value.magnitude() == false) {
			return 0.0;
		}
		return 1.0;
	} else if (//The controllability depends on the probability of all 1's?
		   functionName == "and" ||
		   functionName == "nand" ||
		   functionName == "buf" ||
		   functionName == "not"
		) {
		for (float value : inputControllabilities) {
			toReturn *= value;
		}
	} else if (//The controllability depends on the probability of all 0's?
		   functionName == "or" ||
		   functionName == "nor"
		  ) {
		for (float value : inputControllabilities) {
			toReturn *= (1 - value);
		}
	} else { //Manual evaluation is needed.
		return manualCOP(this, inputControllabilities);
	}

	if (
		functionName == "nand" ||
		functionName == "nor" ||
		functionName == "not"
		) {
		toReturn = 1 - toReturn;
	}
	return toReturn;
}

template<class _width>
float COPNode<_width>::calculateObservability(COP * _calling) {
	Function<_width>* function = this->function();
	if (function->string() == "po") {
		return 1.0;
	}
	if (function->string() == "const") {
		return 0.0;
	}
	float pPass = 1.0;  //The probability that a signal will pass through the given gate.
	if (function->string() == "and" || function->string() == "nand") {
		for (Connecting* input : this->inputs()) {
			if (input == _calling) {
				continue;
			}
			COP* cast = dynamic_cast<COP*>(input);
			pPass *= cast->controllability();
		}
	} else if (function->string() == "or" || function->string() == "nor") {
		for (Connecting* input : this->inputs()) {
			if (input == _calling) {
				continue;
			}
			COP* cast = dynamic_cast<COP*>(input);
			pPass *= 1 - cast->controllability();
		}
	}



	COP* outputLine = dynamic_cast<COP*>(*(this->outputs().begin()));
	float outputObservability = outputLine->observability(this);
	float toReturn =  pPass * outputObservability;
	if (toReturn < 0 || toReturn > 1) {
		throw "Impossible pPass calculation.";
	}
	return toReturn;
}



template<class _width>
Connecting* COPNode<_width>::clone() {
	return new COPNode<_width>(this->function());
}


template<class _width>
void COPNode<_width>::clearControllability()
{
	Function<_width>* function = this->function();

	if (function->string() == "pi" || function->string() == "const") {
		return;
	}
	else {
		this->controllability(-1);

	}
	//DEBUG printf("DBG CC CLEAR %s (%d outputs)\n", this->name().c_str(), this->outputs().size());//DEBUG

	std::unordered_set<Connecting*> outputs = this->outputs();
	for (Connecting * output : outputs) {
		COP* cast = dynamic_cast<COP*>(output);
		cast->clearControllability();

		//Change CC can change CO on "parallel" lines (e.g., the lines feeding the
		//same gate). NOTE: see deleted segment below.
		for (Connecting * possiblyParralInput : output->inputs()) {
			if (possiblyParralInput != this) {
				COP* parallelInput = dynamic_cast<COP*>(possiblyParralInput);
				parallelInput->clearObservability();
			}
		}
	}

}



template<class _width>
void COPNode<_width>::clearObservability() {
	Function<_width>* function = this->function();

	if (function->string() == "po") {
		return;
	}
	//DEBUG printf("DBG CO CLEAR %s (%d outputs) ... ", this->name().c_str(), this->outputs().size());//DEBUG
	else
	{
		this->observability(-1);
	}



	std::unordered_set<Connecting*> inputs = this->inputs();
	//DEBUG printf("DONE, forward to %d\n", inputs.size());
	for (Connecting * input : inputs) {
		COP* cast = dynamic_cast<COP*>(input);
		if (cast != nullptr) {
			//A SPECIAL NOTE:
			//This is one of the few places where casting to a nullptr is allowed. When a node is deleted, it will
			//call "clear observability/controllability" on itself. The controllability call will lead to clear
			//observability calls coming back to it, but by this time, the node will no longer be considered "COP"
			//(since it is in the process of being deconstructed). To avoid this, nullptrs are skipped.
			cast->clearObservability();
		}
	}
}
template class COPNode<bool>;
template class COPNode<unsigned long long int>;

template class COPLine<bool>;
template class COPLine<unsigned long long int>;