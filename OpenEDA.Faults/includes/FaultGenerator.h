/**
 * @file FaultSimulator.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-23
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef FaultGenerator_h
#define FaultGenerator_h

#include <set>

#include "Fault.h"
#include "Circuit.h"
#include "SimulationStructures.hpp"
#include "FaultStructures.hpp"

/*
 * An object capible of populating a list of faults for a Circuit.
 *
 * The base implementation generates stuck-at faults using checkpoint theorem
 * (not applied to XOR gates).
 *
 * The base implementation does only binary faults.
 *
 * @param _primitive The data primitive of the fault (only valid option is "bool").
 */
template <class _primitive>
class FaultGenerator {
public:
	/*
	 * Return a list of all faults for a given Circuit.
	 *
	 * @param _circuit The circuit to generate Faults for.
	 * @return The list of Faults.
	 */
	std::set<Fault<_primitive>> allFaults(Circuit* _circuit);



private:
	/*
	 * Return all Faults associated with a given Node.
	 *
	 * @param _node The Node to generate faults for.
	 * @return The list of Faults.
	 */
	std::set<Fault<_primitive>> allFaults(SimulationNode<_primitive>* _node);


};

#endif