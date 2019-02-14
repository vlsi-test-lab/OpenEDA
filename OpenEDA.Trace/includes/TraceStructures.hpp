/**
 * @file TraceStructures.hpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-09
 *
 * @copyright Copyright (c) 2019
 *
 */


#ifndef TraceStructures_h
#define TraceStructures_h

#include <set>

#include "SimulationStructures.hpp"
#include "Tracable.h"

// Forward declaration
template <class T>
class TraceLine;

/*
 * A Node which supports tracing, forward and backwards.
 *
 * @param _primitive The underlying data type to simulate.
 */
template <class _primitive>
class TraceNode : public SimulationNode<_primitive>, public Tracable {
public:
	/*
	 * Create a default TraceNode.
	 */
	TraceNode() : SimulationNode<_primitive>(), Tracable() {

	}

	/*
	 * Create a Trace node.
	 *
	 * @param _function The function of this node.
	 * @param _inputs Input lines to the given node.
	 * @param _outputs Output lines to the given node.
	 */
	TraceNode(
		Function<_primitive>* _function, 
		std::unordered_set<TraceLine<_primitive>*> _inputs, 
		std::unordered_set<TraceLine<_primitive>*> _outputs) :
		SimulationNode<_primitive>(
			_function, 
			std::unordered_set<SimulationLine<_primitive>*>(_inputs.begin(), _inputs.end()),
			std::unordered_set<SimulationLine<_primitive>*>(_outputs.begin(), _outputs.end())
			), 
		Tracable(
			std::unordered_set<Tracable*>(_inputs.begin(), _inputs.end()),
			std::unordered_set<Tracable*>(_outputs.begin(), _outputs.end()),
			_function->string() == "pi" || _function->string() == "po"
		) ,
		Connecting(
			std::unordered_set<Connecting*>(_inputs.begin(), _inputs.end()),
			std::unordered_set<Connecting*>(_outputs.begin(), _outputs.end())
		)
	{
	
	}

	/*
	 * Get all PIs (and COI) which drive this node.
	 *
	 * @param _coi The cone of influence of this node (returned by reference).
	 * @return All PIs which drive this node.
	 */
	std::unordered_set <TraceNode<_primitive>*> pis(std::unordered_set<TraceNode<_primitive>*>& _coi) {
		std::unordered_set <TraceNode<_primitive>*> toReturn;
		std::unordered_set<Tracable*> flagged;
		std::unordered_set<Tracable*> endpoints = this->backwards(flagged);
		_coi = std::unordered_set<TraceNode<_primitive>*>(flagged.begin(), flagged.end());
		for (Tracable endpoint : endpoints) {
			TraceNode<_primitive>* cast = dynamic_cast<TraceNode<_primitive>*>(endpoint);
			if (cast == nullptr) {
				throw "Big problem: the endpoint of a trace was not a node.";
			}
			if (cast->function()->string() == "pi") {
				//add to the list to return 
				toReturn.emplace(cast);
			}
		}
		return toReturn;
	}

private:

};

/*
 * A Line which supports tracing, forwards and backwards.
 *
 * @param _primitive The underlying data type to simulate.
 */
template <class _primitive>
class TraceLine : public SimulationLine<_primitive>, public Tracable {
public:
	/*
	 * Create a default TraceLine.
	 */
	TraceLine() : SimulationLine<_primitive>(), Tracable() {

	}

	/*
	 * Create a Line with a given name
	 *
	 * @param _name The name of the Line
	 */
	TraceLine(
		std::string _name) :
		SimulationLine<_primitive>(_name),
		Tracable(
			std::unordered_set<Tracable*>(), 
			std::unordered_set<Tracable*>(), 
			false, 
			_name
		) ,
		Connecting(
			_name
		)
	{ 
	}
};
#endif
