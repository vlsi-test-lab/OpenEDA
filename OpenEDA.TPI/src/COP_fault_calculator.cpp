/**
 * @file COP_fault_calculator.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-21
 *
 * @copyright Copyright (c) 2019
 *
 */


#include "COP_fault_calculator.h"

COP_fault_calculator::COP_fault_calculator(Circuit * _circuit) {
	this->faults_ = FaultGenerator<bool>::allFaults(_circuit);
}

COP_fault_calculator::~COP_fault_calculator() {
	for (Fault<bool>* fault : this->faults_) {
		delete fault;
	}
}

float COP_fault_calculator::faultCoverage() {
	float toReturn = 0.0;
	for (Fault<bool>* fault : this->faults_) {
		toReturn += this->detect(fault);
	}
	toReturn /= (float)this->faults_.size();
	return toReturn;
}

float COP_fault_calculator::detect(Fault<bool>* _fault) {
	FaultyLine<bool>* location = _fault->location();
	COP* cast = dynamic_cast<COP*>(location);
	if (cast == nullptr) {
		throw "Cannot calculate fault-based fault coverage: COP not enabled on the fault location.";
	}
	bool SAValue = _fault->value().magnitude();
	float CO = cast->observability();
	float CC = cast->controllability();
	if (SAValue == true) {
		CC = 1 - CC;
	}
	return CC * CO;
}
