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
#include "SAT.h"
#include "Combination.h"
#include "Value.h"
#include "ValueVectorFunctions.hpp"

/*
 * The combination of Node elements required to perform SAT.
 *
 * @param _primitive The underlying data primitive for simulation.
 */
template <class _primitive>
class SatisfiableNode : public TraceNode<_primitive> {
public:
	/*
	 * Create a SatisfiableNode.
	 *
	 * For convenience, this structure tracks and can return input
	 * combinations. These will be created and tracked upon construction.
	 *
	 * @param _function The function of this node.
	 * @param _inputs Input lines to the given node.
	 * @param _outputs Output lines to the given node.
	 * @param _pi (optional) Is the Node a PI (optional, default = false).
	 * @param _po (optional) Is the node a PO (optional, default = false).
	 */
	SatisfiableNode(
		Function<_primitive>* _function, 
		std::unordered_set<TraceLine<_primitive>*> _inputs, 
		std::unordered_set<TraceLine<_primitive>*> _outputs
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
		std::vector<Value<_primitive>> inputVector(_inputs.size(), Value<_primitive>((_primitive)0));
		do {
			Combination<_primitive>* newCombination = new Combination<_primitive>(_inputs, inputVector);
			combinations_.emplace(newCombination);
		} while (ValueVectorFunction<_primitive>::increment(inputVector));
	}

	/*
	 * Activate this Node and return all output nodes which need to be evaluated.
	 *
	 * New nodes will only be returned if the node's flag is not set.
	 *
	 * @return New events (and their priority) created by activating this event.
	 */
	virtual std::set<std::pair<size_t, Evented<_primitive>*>> go() {
		if (this->flag() == false) {
			return this->Evented<_primitive>::go();
		}
		return std::set<std::pair<size_t, Evented<_primitive>*>>();
	}

	/*
	 * Create all possible input Combinations for this Node, i.e., every possible
	 * input vector this node can have.
	 *
	 * @return All input combinations (which will be stored locally in the Node
	 *         as well).
	 */
	std::unordered_set<Combination<_primitive>*> populateAllCombinations() {
		if (this->inputs().size() == 0) {
			return std::unordered_set<Combination<_primitive>*>();
		}
		std::vector<Value<_primitive>> inputVector;
		std::unordered_set<TraceLine<_primitive>*> lines;
		for (Connecting* input : this->inputs()) {
			TraceLine<_primitive>* cast = dynamic_cast<TraceLine<_primitive>*>(input);
			lines.emplace(cast);
			inputVector.push_back(cast->value());
		}
		for (Value<_primitive> value : inputVector) {
			value.valid(true);
			value.magnitude(value.min());
		}
		do {
			Combination<_primitive>* combination = new Combination<_primitive>(lines, inputVector);
			this->combinations_.emplace(combination);
		} while (ValueVectorFunction<_primitive>::increment(inputVector) == true);
		return this->combinations_;
	}

private:
	/*
	 * A set of all input combinations of this node.
	 */
	std::unordered_set<Combination<_primitive>*> combinations_;
	
};

#endif