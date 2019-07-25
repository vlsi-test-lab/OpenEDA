/**
 * @file COP_fault_calculator.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-21
 *
 * @copyright Copyright (c) 2019
 *
 */


#ifndef COP_fault_calculator_h
#define COP_fault_calculator_h

#include "Circuit.h"
#include "Fault.h"
#include "FaultGenerator.h"
#include "COPStructures.h"

/*
 * Calculates the fault coverage of a circuit using COP values.
 *
 * @param _primitive The primitive measured by cop (bool or unsigned long long int).
 */
template <class _primitive>
class COP_fault_calculator {
public:
	/*
	 * Create the calculator for a given Circuit
	 *
	 * @param _circuit The circuit to calculate for.
	 */
	COP_fault_calculator(Circuit* _circuit, bool stuck_target);

	/*
	 * Upon deletion, delete all faults.
	 */
	~COP_fault_calculator();


	/*
	 * The predicted fault coverage
	 *
	 * @return The predicted fault coverage.
	 */
	float faultCoverage();

private:
	/*
	 * The faults for this calculator.
	 */
	std::unordered_set<Fault<_primitive>*> faults_;

	/*
	 * The probability a given fault is detected.
	 *
	 * @param _fault The fault to detect.
	 * @return The probability of detection.
	 */
	float detect(Fault<_primitive>* _fault);

	/*
	*if it is true use stuck target cop. if it is false use delay target cop
	*/

	bool stuck_target_;
};


#endif
