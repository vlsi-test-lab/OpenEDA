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
class SimulationLine : virtual public Evented<_primitive> {
public:
	/*
	 * Create a simulation line with a "UNDEF" name.
	 */
	SimulationLine() : 
		Evented<_primitive>(
			std::unordered_set<Evented<_primitive>*>(),
			std::unordered_set<Evented<_primitive>*>(),
			"UNDEF"
		) ,
		Connecting(
			"UNDEF"
		)
	{
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
		) , 
		Connecting(
			_name
		)
	{
	};



	/*
	 * Return Create an copy of this object.
	 *
	 *
	 *
	 * @return new simulationline.
	 */
	virtual Connecting* clone() const {
		return new SimulationLine(this->name());
	}
};


/*
 * A Node which contains all parts needed for event-based simulation.

 * @param _primitive The underlying primitive to implement in Simulation (bool, char, etc.)
 */
template <class _primitive>
class SimulationNode : virtual  public Functioned<_primitive>, virtual public Evented<_primitive> {
public:
	/*
	 * Create a node with no inputs, no outputs, and a "copy" function.
	 */
	SimulationNode() : Evented<_primitive>() {
		this->function_ = new BooleanFunction<_primitive>("copy");
	}

	/*
	 * Create a Simulation node.
	 *
	 * @param _function The function of this node.
	 * @param (optional) _inputs Input lines to the given node.
	 * @param (optional) _outputs Output lines to the given node.
	 */
	SimulationNode(
		Function<_primitive>* _function, 
		std::unordered_set<SimulationLine<_primitive>*> _inputs = std::unordered_set<SimulationLine<_primitive>*>(),
		std::unordered_set<SimulationLine<_primitive>*> _outputs = std::unordered_set<SimulationLine<_primitive>*>()
	) :
		Evented<_primitive>(
			std::unordered_set<Evented<_primitive>*>(_inputs.begin(), _inputs.end()),
			std::unordered_set<Evented<_primitive>*>(_outputs.begin(), _outputs.end())
		) ,
		Connecting(
			std::unordered_set<Connecting*>(_inputs.begin(), _inputs.end()),
			std::unordered_set<Connecting*>(_outputs.begin(), _outputs.end())
		)
	{
		this->function(_function);
	}

	/*
	 * Return the name of the node's output.
	 *
	 * Throw an exception if there is no output.
	 *
	 * @return This object's name.
	 */
	virtual std::string name() const {
		std::string toReturn = this->function_->string() + " ";
		if (this->outputs().size() != 0) {
			toReturn += (*(this->outputs().begin()))->name();
		} else {
			toReturn += "UNKOWN";
		}
		return toReturn;
	}


	/*
	 * Return Create an copy of this object.
	 *
	 * 
	 *
	 * @return new simulationnode.
	 */
	virtual Connecting* clone() const {
		return new SimulationNode(this->function());
	}


};


#endif