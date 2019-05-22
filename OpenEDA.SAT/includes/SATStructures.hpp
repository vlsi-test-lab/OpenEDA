/**
 * @file SATStructures.hpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-15
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef SATStructures_h
#define SATStructures_h

#include "SimulationStructures.hpp"
#include "TraceStructures.hpp"
#include "Combination.hpp"
#include "Value.h"
#include "ValueVectorFunctions.hpp"


/*
 * The combination of Node elements required to perform SAT.
 *
 * Functions are modified to create "boundary simulation" as well as to
 * generate all combinations.
 *
 * @param _primitive The underlying data primitive for simulation.
 */
template <class _primitive>
class SATNode : public TraceNode<_primitive> {
public:
	SATNode() : TraceNode<_primitive>() {

	}

	/*
	 * Create a SATNode.
	 *
	 * For convenience, this structure tracks and can return input
	 * combinations. These will be created and tracked upon construction.
	 *
	 * @param _function The function of this node.
	 * @param _inputs Input lines to the given node.
	 * @param _outputs Output lines to the given node.
	 */
	SATNode(
		Function<_primitive>* _function, 
		std::unordered_set<SATLine<_primitive>*> _inputs = std::unordered_set<SATLine<_primitive>*>(),
		std::unordered_set<SATLine<_primitive>*> _outputs = std::unordered_set<SATLine<_primitive>*>()
	) : 
		TraceNode<_primitive>(
			_function, 
			std::unordered_set<TraceLine<_primitive>*>(_inputs.begin(), _inputs.end()),
			std::unordered_set<TraceLine<_primitive>*>(_outputs.begin(), _outputs.end())
			) ,
		Connecting(
			std::unordered_set<Connecting*>(_inputs.begin(), _inputs.end()),
			std::unordered_set<Connecting*>(_outputs.begin(), _outputs.end())
		)
	{
		
	}

	/*
	 * Activate this Node and return all output nodes which need to be evaluated.
	 *
	 * New nodes will only be returned if the node's flag is not set.
	 *
	 * @return New events (and their priority) created by activating this event.
	 */
	virtual std::set<std::pair<size_t, Evented<_primitive>*>> go(
		std::vector<Value<_primitive>> _values = std::vector<Value<_primitive>>()
	) {
		if (this->flag() == true) {
			return this->Evented<_primitive>::go(_values);
		}
		return std::set<std::pair<size_t, Evented<_primitive>*>>();
	}

	//DELETE
	//The following was deleted because it required "hard coding" the line type
	//that SATNodes are connected to. Instead, a separate tool should create all
	//combinations and should be able to track what combinations are present on
	//which Nodes.
//	/*
//	 * Create all possible input Combinations for this Node, i.e., every possible
//	 * input vector this node can have.
//	 *
//	 * @return All input combinations (which will be stored locally in the Node
//	 *         as well).
//	 */
//	std::unordered_set<Combination<_primitive, _lineType, _nodeType>*> populateAllCombinations() {
//		if (this->inputs().size() == 0) {
//			return std::unordered_set<Combination<_primitive>*>();
//		}
//		std::vector<Value<_primitive>> inputVector;
//		std::unordered_set<TraceLine<_primitive>*> lines;
//		for (Connecting* input : this->inputs()) {
//			TraceLine<_primitive>* cast = dynamic_cast<TraceLine<_primitive>*>(input);
//			lines.emplace(cast);
//			inputVector.push_back(cast->value());
//		}
//		for (Value<_primitive> value : inputVector) {
//			value.valid(true);
//			value.magnitude(value.min());
//		}
//		do {
//			Combination<_primitive>* combination = new Combination<_primitive>(lines, inputVector);
//			this->combinations_.emplace(combination);
//		} while (ValueVectorFunction<_primitive>::increment(inputVector) == true);
//		return this->combinations_;
//	}
//
//private:
//	/*
//	 * A set of all input combinations of this node.
//	 */
//	std::unordered_set<Combination<_primitive>*> combinations_;
	
};

/*
 * A Line used in conjunction with SATNode.
 *
 * @param _primitive The data primitive used for simulation (typically bool).
 */
template <class _primitive>
class SATLine : virtual public TraceLine<_primitive> {
public:
	/*
	 * Create a with a "UNDEF" name.
	 */
	SATLine() : TraceLine<_primitive>(), Connecting("UNDEF") {
	};

	/*
	 * Create a Line with a given name
	 *
	 * @param _name The name of the Line
	 */
	SATLine(std::string _name) :
		TraceLine<_primitive>(_name),
		Connecting(_name) {
	};

	/*
	 * Activate this Line and return all outputs which need to be evaluated.
	 *
	 * New objects will only be returned if the line's flag is not set.
	 *
	 * @return New events (and their priority) created by activating this event.
	 */
	virtual std::set<std::pair<size_t, Evented<_primitive>*>> go(
		std::vector<Value<_primitive>> _values = std::vector<Value<_primitive>>()
	) {
		if (this->flag() == true) {
			return this->Evented<_primitive>::go(_values);
		}
		return std::set<std::pair<size_t, Evented<_primitive>*>>();
	}
};


#endif