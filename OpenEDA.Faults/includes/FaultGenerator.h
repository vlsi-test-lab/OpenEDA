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
#include <unordered_map>

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
	 * @param (optional) _checkpointReduce Reduce the number of faults by doing
	 *        checkpoint equivalence.
	 * @return The list of Faults.
	 */
	static std::unordered_set<Fault<_primitive>*> allFaults(Circuit* _circuit, bool _checkpointReduce = true);



private:
	/*
	 * Return all Faults associated with a given Node.
	 *
	 * @param _node The Node to generate faults for.
	 * @return The list of Faults.
	 */
	//DELETE: obsolete. static std::set<Fault<_primitive>> allFaults(SimulationNode<_primitive>* _node);

	/*
	 * Return all "checkpoints" (in terms of fault generation) in the circuit.
	 *
	 * @param _circuit The circuit to get the checkpoints for.
	 * @return The list of checkpoint lines.
	 */
	static std::unordered_set<FaultyLine<_primitive>*> checkpoints(Circuit* _circuit);

	/*
	 * Return all fan-out objects starting from the given object.
	 *
	 * @param _line The object to start tracing forward from.
	 * @return The set of all fan-out object.
	 */
	static std::unordered_set<Connecting*> fanouts(Connecting * _base, std::unordered_map<Connecting*, bool> & _visited);


};

#endif