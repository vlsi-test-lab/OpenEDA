/**
 * @file SimulationStructures.hpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-02
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef SimulationStructures_h
#define SimulationStructures_h

#include "Value.h"
#include "Level.h"
#include "Function.h"
#include "EventQueue.h"
#include "SimulationNet.hpp"

#include <string>

/*
 * A Line which can be used for basic binary Simulation.
 *
 * A BinaryLine is capible of holding a Value.
 *
 * @param _primitive The underlying primitive to implement in Simulation (bool, char, etc.)
 */
template <class _primitive>
class SimulationLine : public Evented<_primitive> {
public:
	/*
	 * Create a simulation line with a "UNDEF" name.
	 */
	SimulationLine() : Evented<_primitive>() {
	};

	/*
	 * Create a Line with a given name
	 *
	 * @param _name The name of the Line
	 */
	SimulationLine(
		std::string _name
	) : 
		Evented<_primitive>(
			std::unordered_set<Evented<_primitive>*>() ,
			std::unordered_set<Evented<_primitive>*>(),
			_name
		) 
	{
	};
};


/*
 * A Node which contains all parts needed for event-based simulation.

 * @param _primitive The underlying primitive to implement in Simulation (bool, char, etc.)
 */
template <class _primitive>
class SimulationNode : public Functioned<_primitive>, public Evented<_primitive> {
public:
	/*
	 * Create a node with no inputs, no outputs, and a "copy" function.
	 */
	SimulationNode() : Evented<_primitive>() {
		this->function_ = new BooleanFunction("copy");
	}

	/*
	 * Create a Simulation node.
	 *
	 * @param _function The function of this node.
	 * @param _inputs Input lines to the given node.
	 * @param _outputs Output lines to the given node.
	 */
	SimulationNode(
		Function<_primitive>* _function, 
		std::unordered_set<SimulationLine<_primitive>*> _inputs, 
		std::unordered_set<SimulationLine<_primitive>*> _outputs) :
		Evented<_primitive>(
			std::unordered_set<Evented<_primitive>*>(_inputs.begin(), _inputs.end()),
			std::unordered_set<Evented<_primitive>*>(_outputs.begin(), _outputs.end())
		) 
	{
		this->function(_function);
	}



};


#endif