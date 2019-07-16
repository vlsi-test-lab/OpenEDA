/**
 * @file Combination.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-14
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef Combination_h
#define Combination_h

#include <unordered_set>
#include <vector>

#include "Value.h"
#include "ValueVectorFunctions.hpp"
#include "Function.h"

 //Forward declaration
template <class T>
class SATLine;

/*
 * A combination of Line values in a circuit.
 *
 * A Combination is a special type of 'Node' which represents a combination of 
 * particular objects in a circuit at particular Values.
 *
 * During simulation, if the combination is updated to the designated Values,
 * then the input connections to the combination will be removed.
 *
 * @param _primitive The underlying data primitive to simulate.
 * @param _nodeType The type of node implemented as the "polling node" for this
 *        Combination. It should ideally be the same kind of node as
 *        implemented in the rest of the Circuit.
 */
template <class _primitive, class _lineType, class _nodeType>
class Combination : public _nodeType {
public:
	/*
	 * By default, a Combination has no Lines and no Values, which will be
	 * interpreted as not-seen.
	 */
	Combination() {
		//DELETE: flawed. throw "A undefined Combination is not valid.";
	}

	/*
	 * Create a Combination of a given set of lines at a given set (vector) of Values.
	 *
	 * It is not valid to have a combination with no Lines or Values, or to have the number
	 * of Lines and Values not match.
	 *
	 * @param _lines The Lines to measure values on.
	 * @param _values The Values to be measured.
	 * @param _seen (optional) If set, this parameter is considered "already seen".
	 */
	Combination(
		std::vector<_lineType*> _lines,
		std::vector<Value<_primitive>> _values, 
		bool _seen = false
	) : _nodeType(
		new CopyFunction<_primitive>("comb")
		) {
		lines_ = _lines;
		values_ = _values;
		if (lines_.size() != values_.size()) {
			throw "Lines and Values must match in size.";
		}
		if (lines_.size() == 0) {
			throw "At least one Line must be given";
		}
		if (_seen == true) {
			return;
		}
		for (_lineType* line : _lines) { //This will only be called if "not seen".
			line->addOutput(this);
		}
	};

	/*
	 * Create a seen Combination of a given set of lines, and get the values from the lines.
	 *
	 * It is presumed that this combination has been seen, and therefore no circuit
	 * connections will be made.
	 *
	 * EXCEPTION: At least one line must be given.
	 *
	 * @param _lines The lines to measure values on which currently hold their needed values.
	 */
	Combination(
		std::vector<_lineType*> _lines
	) : _nodeType(
		) {
		this->lines_ = _lines;
		this->values_ = std::vector<Value<_primitive>>();
		for (_lineType* line : _lines) {
			this->values_.push_back(line.value());
		}
		if (lines_.size() == 0) {
			throw "At least one line must be given";
		}
	};

	/*
	 * Create a seen Combination of a given set of nodes, and get the values from the nodes.
	 *
	 * It is presumed that this combination has been seen, and therefore no circuit
	 * connections will be made.
	 *
	 * EXCEPTION: At least one node must be given.
	 *
	 * @param _nodes The nodes to measure values on which currently hold their needed values.
	 */
	Combination(
		std::vector<_nodeType*> _nodes
	) : _nodeType(
	) {
		std::vector<_lineType*> lines;
		for (_nodeType* node : _nodes) {
			if (node->outputs().size() != 1) {
				throw "Cannot make a combination from nodes which do not have 1 output.";
			}
			_lineType* outputLine = dynamic_cast<_lineType*>(*(node->outputs().begin()));
			if (outputLine == nullptr) {
				throw "Combination line is not of the right type.";
			}
			lines.push_back(outputLine);
		}

		this->lines_ = lines;
		this->values_ = std::vector<Value<_primitive>>();
		for (_lineType* line : this->lines_) {
			this->values_.push_back(line->value());
		}
		if (lines_.size() == 0) {
			throw "At least one node must be given";
		}
	};

	/*
	 * Check if this combination has been seen. If so, remove its connections.
	 *
	 * An exception will be thrown if the size of the given Values is different 
	 * than the Combination's Values.
	 *
	 * If the value has already been seen, a default value will be returned.
	 *
	 * NOTE: The returned value is in-effect useless. This is because this
	 *       function overwrites the inherited value to allow "seen" values to
	 *       be easily implemented.
	 *
	 * NOTE: Since the values given (_values) cannot be gauranteed to be in the
	 *       same order, the given values will be ignored. Instead, values will be
	 *       fetched manaully by this function.
	 *
	 * @param _values The Values to evaluate using this object's function.
	 * @return The evaluated value of this object (will always be the default Value).
	 */
	virtual Value<_primitive> value(std::vector<Value<_primitive>> _values) {
		if (this->inputs().size() == 0) {
			return Value<_primitive>();
			//DELETE: flawed. throw "This combination has already been seen.";
		}
		if (_values.size() != values_.size()) {
			throw "The size of values must match";
		}
		for (size_t i = 0; i < this->values_.size(); i++) {
			if (values_.at(i) == this->lines_.at(i)->value()) {
				continue;
			} else {
				return Value<_primitive>();
			}
		}
		//Values match, delete all input connections.
		//NOTE: the "critical" part is needed because if multiple processes try to "disconect"
		//      this combination at the same time, it can cause a memory race condition. The
		//      project which compiles this needs to have openMP enabled.
		#pragma omp critical 
		this->inputs(std::unordered_set<Connecting*>());
		/*for (SATLine<_primitive>* line : this->lines_) {
			line->removeOutput(this);
		}*/
		return Value<_primitive>();
	};

	/*
	 * Has this combination been seen.
	 *
	 * @return True if the combination has been seen.
	 */
	bool seen() const {
		return this->inputs().size() == 0;
	};

	/*
	 * The current input Values seen by this Combination.
	 *
	 * @return The current input Values seen by this Combination.
	 */
	std::vector<Value<_primitive>> currentValues() {
		std::vector<Value<_primitive>> toReturn;
		for (TraceLine<_primitive>* line : this->lines_) {
			toReturn.push_back(line->value());
		}
		return toReturn;
	};

	/*
	 * The target values of this Combination.
	 *
	 * @return The target values of this Combination.
	 */
	std::vector<Value<_primitive>> targetValues() const {
		return this->values_;
	};

	/*
	 * Return the Lines polled by this Combination.
	 *
	 * @return The Lines polled by this Combination.
	 */
	std::vector<SATLine<_primitive>*> lines() const {
		//DELETE: obsolete return std::unordered_set<SATLine<_primitive>*>(this->lines_.begin(), this->lines_.end());
		return this->lines_;
	};

	/*
	 * For a given node, create and return all possible input combinations.
	 *
	 * @param _node The node to generate all (not yet seen) Combinations for.
	 * @return All (not yet seen) input Combinations for this node.
	 */
	static std::unordered_set<Combination<_primitive, _lineType, _nodeType>*> allNodeCombinations(_nodeType* _node) {
		std::unordered_set<Combination<_primitive, _lineType, _nodeType>*> toReturn;
		std::vector<Value<_primitive>> inputValues(_node->inputs().size(), Value<_primitive>(0));
		if (inputValues.size() == 0) {
			return toReturn;
		}
		std::vector<_lineType*> inputLines;
		for (Connecting* input : _node->inputs()) {
			_lineType* inputCast = dynamic_cast<_lineType*>(input);
			inputLines.push_back(inputCast);
		}
		do {
			Combination<_primitive, _lineType, _nodeType>* newCombination = new Combination<_primitive, _lineType, _nodeType>(inputLines, inputValues);
			toReturn.emplace(newCombination);
		} while (ValueVectorFunction<_primitive>::increment(inputValues) == true);
		return toReturn;
	}

private:
	/*
	 * The Lines of this Combination.
	 */
	std::vector<SATLine<_primitive>*> lines_;

	/*
	 * The Values of this Combination.
	 */
	 std::vector<Value<_primitive>> values_;

};


#endif