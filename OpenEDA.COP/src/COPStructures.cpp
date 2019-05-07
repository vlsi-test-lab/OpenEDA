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
	this->controllability_ = 0;
	this->observability_ = 0;
	this->calculateAlways_ = _calculateAlways;
}


float COP::controllability() {
	if (this->controllability_ >= 0) {
		return this->controllability_;
	}

	if (this->inputs().size() == 1) { //This has only one input, so forward the call.
		Connecting* input = *(this->inputs().begin());
		COP* cast = dynamic_cast<COP*>(input);
		this->controllability_ = cast->controllability();
	} else if (this->inputs().size() == 0) { //We have a problem.
		throw "Cannot calculate COP CC: no values to calculate from.";
	} else { //Multiple inputs, calculate as defined.
		this->controllability_ = this->calculateControllability();
		if (this->controllability_ < 0) {
			throw "Cannot calculate COP CC: failure to calculate.";
		}
	}
	return this->controllability_;
}

float COP::controllability(float _controllability) {
	this->controllability_ = _controllability;
	return this->controllability_;
}

float COP::observability(COP* _calling) {
	if (this->observability_ >= 0) {
		return this->observability_;
	}

	if (this->outputs().size() == 1) { //This has only one outputs, so forward the call.
		COP* cast = dynamic_cast<COP*>((*this->outputs().begin()));
		this->observability_ = cast->observability(this);
	} else if (this->outputs().size() == 0) { //We have a problem.
		throw "Cannot calculate COP CO: no values to calculate from.";
	} else { //Multiple outputs, calculate as defined.
		float toReturn = this->calculateObservability(_calling);
		if (toReturn < 0) {
			throw "Cannot calculate COP CC: failure to calculate.";
		}
		if (this->calculateAlways_ == true) {
			return toReturn;
		}
		this->observability_ = toReturn;
	}
	return this->controllability_;
}

float COP::observability(float _observability) {
	this->observability_ = _observability;
	return this->observability_;
}

COPLine::COPLine() : 
	COP(false) , 
	SimulationLine<bool>() 
{
}

COPLine::COPLine(std::string _name) : 
	COP(false) ,
	SimulationLine<bool>(_name) 
{
}

float COPLine::calculateControllability() {
	COP* cast = dynamic_cast<COP*>(*(this->inputs().begin()));
	return cast->controllability();
}

float COPLine::calculateObservability(COP * _calling) {
	float toReturn = -1;
	for (Connecting* output : this->outputs()) {
		COP* cast = dynamic_cast<COP*>(output);
		float other = cast->observability(this);
		toReturn = other > toReturn ? other : toReturn;
	}
	return toReturn;
}

/*
 * Manually calculate COP for a given node.
 */
float manualCOP(COPNode* node, std::vector<float> inputControllabilities) {
	Function<bool>* func = dynamic_cast<Function<bool>*>(node->function());
	std::vector<Value<bool>> nodeInputVals = std::vector<Value<bool>>(node->inputs().size(), Value<bool>(false));
	unsigned long int num0 = 0;
	unsigned long int num1 = 0;
	float ret = 1.0;
	float ret1;
	do {
		Value<bool> outVal = func->evaluate(nodeInputVals);
		if (outVal.valid() == false) {
			throw "COP cannot be calculated for a non-valid function output.";
		}
		if (outVal.magnitude() == false) {
			num0++;
		}
		if (outVal.magnitude() == true) {
			ret1 = 1;
			for (size_t a = 0; a < nodeInputVals.size(); a++) {

				if (nodeInputVals.at(a).magnitude() == true) {
					ret1 = ret1 * (inputControllabilities.at(a));
				} else {
					ret1 = ret1 * (1 - inputControllabilities.at(a));
				}
			}
			ret = ret + ret1;
		}
	} while (ValueVectorFunction<bool>::increment(nodeInputVals) == true);

	return ret;
}

float COPNode::calculateControllability() {
	//First, get the input controllabilities.
	std::vector<float> inputControllabilities;
	for (Connecting* input : this->inputs()) {
		COP* cast = dynamic_cast<COP*>(input);
		inputControllabilities.push_back(cast->controllability());
	}

	//Second, calculate depending on the gate type.
	float toReturn = 1.0;
	Function<bool>* function = this->function();
	if (function->string() == "pi") {
		return 0.5;
	} else if (function->string() == "const") {
		Value<bool> value = function->evaluate(std::vector<Value<bool>>());
		if (value.valid() == false) {
			throw "Cannot calculate COP CC: constant value is not valid.";
		}
		if (value.magnitude() == false) {
			return 0.0;
		}
		return 1.0;
	} else if (//The controllability depends on the probability of all 1's?
		function->string() == "and" ||
		function->string() == "nand" ||
		function->string() == "buf" ||
		function->string() == "not"
		) {
		for (float value : inputControllabilities) {
			toReturn *= value;
		}
	} else if (//The controllability depends on the probability of all 0's?
		  function->string() == "or" ||
		  function->string() == "nor"
		  ) {
		for (float value : inputControllabilities) {
			toReturn *= (1 - value);
		}
	} else { //Manual evaluation is needed.
		return manualCOP(this, inputControllabilities);
	}

	if (
		function->string() == "nand" ||
		function->string() == "nor" ||
		function->string() == "not"
		) {
		toReturn = 1 - toReturn;
	}
	return toReturn;
}

float COPNode::calculateObservability(COP * _calling) {
	Function<bool>* function = this->function();
	if (function->string() == "po") {
		return 1.0;
	}
	float pPass = 1.0;  //The probability that a signal will pass through the given gate.
	if (function->string() == "and" || function->string() == "nand") {
		for (Connecting* input : this->inputs()) {
			COP* cast = dynamic_cast<COP*>(input);
			pPass *= cast->controllability();
		}
	} else if (function->string() == "or" || function->string() == "nor") {
		for (Connecting* input : this->inputs()) {
			COP* cast = dynamic_cast<COP*>(input);
			pPass *= 1 - cast->controllability();
		}
	}

	COP* outputLine = dynamic_cast<COP*>(*(this->outputs().begin()));
	return pPass * outputLine->observability(this);
}
