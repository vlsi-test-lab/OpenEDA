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

template <class _primitive>
COP_fault_calculator< _primitive>::COP_fault_calculator(Circuit * _circuit) {
	this->faults_ = FaultGenerator<_primitive>::allFaults(_circuit);
}

template <class _primitive>
COP_fault_calculator< _primitive>::~COP_fault_calculator() {
	for (Fault<_primitive>* fault : this->faults_) {
		delete fault;
	}
}

template <class _primitive>
float COP_fault_calculator< _primitive>::faultCoverage() {
	float toReturn = 0.0;
	for (Fault<_primitive>* fault : this->faults_) {
		toReturn += this->detect(fault);
	}
	toReturn /= (float)this->faults_.size();
	return toReturn;
}

template <class _primitive>
float COP_fault_calculator< _primitive>::detect(Fault<_primitive>* _fault) {
	FaultyLine<_primitive>* location = _fault->location();
	COP* cast = dynamic_cast<COP*>(location);
	if (cast == nullptr) {
		throw "Cannot calculate fault-based fault coverage: COP not enabled on the fault location.";
	}
	_primitive SAValue = _fault->value().magnitude();
	float CC = cast->controllability();
	float CO = cast->observability();
	if (SAValue) {
		CC = 1 - CC;
	}
	//DEBUG printf("DBG Fault: %s (%d outputs) sa%d -> %f\n", _fault->location()->name().c_str(), _fault->location()->outputs().size(), SAValue, CC*CO); //DEBUG
	return CC * CO;
}

template class COP_fault_calculator<unsigned long long int>;
template class COP_fault_calculator<bool>;