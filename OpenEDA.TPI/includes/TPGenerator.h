/**
 * @file TPGenerator.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-22
 *
 * @copyright Copyright (c) 2019
 *
 */


#ifndef TPGenerator_h
#define TPGenerator_h

#include <unordered_set>

#include "Circuit.h"
#include "Testpoint.h"

/*
 * Create all TPs for a circuit.
 *
 * @param _TPType The type of TPs to generate.
 * @param _primitive The data primitive of simulation.
 */
template <class _TPType, class _primitive>
class TPGenerator {
public:
	/*
	 * Create all TPs for the given circuit.
	 *
	 * @param _circuit The circuit to generate all TPs for.
	 * @return The set of all testpoints.
	 */
	static std::set<Testpoint<_primitive>*> allTPs(Circuit* _circuit) {
		std::set<_TPType> toReturn;
		for (Levelized* node : _circuit->nodes()) {
			SimulationNode<_primitive>* cast = dynamic_cast<SimulationNode<_primitive>*>(node);
			std::set<_TPType> toAdd = allTPs(cast);
			toReturn.insert(toAdd.begin(), toAdd.end());
		}
		//Convert to pointers (previously non-pointers to allow for easy indentical fault removeal).
		std::set<Testpoint<_primitive>*> pointers;
		for (_TPType TP : toReturn) {
			pointers.emplace(new _TPType(TP));
		}
		return pointers;
	}

private:
	/*
	 * Create all TPs for a given node (input and output TPs).
	 *
	 * @param _node The node to make all TPs for.
	 * @return The list of TPs.
	 */
	static std::set<_TPType> allTPs(SimulationNode<_primitive>* _node) {
		std::set<_TPType> toReturn;
		for (Connecting* input : _node->inputs()) {
			FaultyLine<_primitive>* line = dynamic_cast<FaultyLine<_primitive>*>(input);
			std::set<_TPType> toAdd = allTPs(line);
			toReturn.insert(toAdd.begin(), toAdd.end());
		}
		for (Connecting* output : _node->outputs()) {
			FaultyLine<_primitive>* line = dynamic_cast<FaultyLine<_primitive>*>(output);
			std::set<_TPType> toAdd = allTPs(line);
			toReturn.insert(toAdd.begin(), toAdd.end());
		}
		return toReturn;
	}

	/*
	 * Create all TPs for a given line.
	 *
	 * This function must be specialized for each TP type. See the CPP file.
	 *
	 * @param _line The line to make all TPs for.
	 * @return All TPs on the given line.
	 */
	static std::set<_TPType> allTPs(FaultyLine<_primitive>* _line);
};


#endif