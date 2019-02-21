/**
 * @file TPI_COP.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-21
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "TPI_COP.h"

TPI_COP::TPI_COP(Circuit* _circuit, size_t _TPLimit, float _qualityLimit, size_t _timeLimit) :
	TPI<bool>(_circuit, _TPLimit, _qualityLimit, _timeLimit), FaultCoverageCalculator_(_circuit)
{
	baseFaultCoverage_ = -1;
}

float TPI_COP::quality(Testpoint<bool>* _testpoint) {
	_testpoint->activate();
	float base = this->base();
	float toReturn = this->FaultCoverageCalculator_.faultCoverage() - base;
	_testpoint->deactivate();
	return toReturn;
}

float TPI_COP::base() {
	 if (this->baseFaultCoverage_ < 0) {
		 this->baseFaultCoverage_ = this->FaultCoverageCalculator_.faultCoverage();
	 }
	 return this->baseFaultCoverage_;
 }

 float TPI_COP::base(float _base) {
	 this->baseFaultCoverage_ = _base;
	 return this->baseFaultCoverage_;
 }
