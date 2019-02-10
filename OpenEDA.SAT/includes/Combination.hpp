/**
 * @file Combination.hpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-14
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef Combination_h
#define Combination_h

#include <set>
#include <vector>

#include "SimulationStructures.hpp"
#include "TraceStructures.hpp"
#include "Function.h"
#include "Net.hpp"


/*
 * A combination of Line values in a circuit.
 *
 * A Combination is a special type of Node which represents a combination of 
 * Line holding particular Values in a Circuit.
 *
 * During simulation, if the Line's Values match, then the input connections to
 * the node will be removed.
 *
 * @param _primitive The underlying data primitive to simulate.
 */
template <class _primitive>
class Combination : public TraceNode<_primitive> {
public:
	/*
	 * By default, a Combination has no Lines and no Values, which will be
	 * interpreted as not-seen.
	 */
	Combination();

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
	Combination(std::unordered_set<SimulationLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);

	/*
	 * Check if this combination has been seen. If so, remove its connections.
	 *
	 * An exception will be thrown if the size of the given Values is different the the Combination's Values.
	 *
	 * @param _values The Values to evaluate using this object's function.
	 * @return The evaluated value of this object (will always be the default Value).
	 */
	virtual Value<_primitive> evaluate(std::vector<Value<_primitive>> _values);

	/*
	 * Has this combination been seen.
	 *
	 * @return True if the combination has been seen.
	 */
	bool seen() const;

	/*
	 * The current input Values seen by this Combination.
	 *
	 * @return The current input Values seen by this Combination.
	 */
	std::vector<Value<_primitive>> currentValues() ;

	/*
	 * The target values of this Combination.
	 *
	 * @return The target values of this Combination.
	 */
	std::vector<Value<_primitive>> targetValues() const;

	/*
	 * Return the Lines polled by this Combination.
	 *
	 * @return The Lines polled by this Combination.
	 */
	std::unordered_set<SimulationLine<_primitive>*> lines();

private:
	/*
	 * The Lines of this Combination.
	 */
	std::unordered_set<SimulationLine<_primitive>*> lines_;

	/*
	 * The Values of this Combination.
	 */
	std::vector<Value<_primitive>> values_;

};


template<class _primitive>
inline Combination<_primitive>::Combination() {
}

template<class _primitive>
inline Combination<_primitive>::Combination(
	std::unordered_set<SimulationLine<_primitive>*> _lines,
	std::vector<Value<_primitive>> _values, 
	bool _seen) 
	: TraceNode<_primitive>(new CopyFunction<_primitive>("comb"), std::unordered_set<Line*>(_lines.begin(), _lines.end()), std::unordered_set<Line*>()) {
	lines_ = _lines;
	values_ = _values;
	if (lines_.size() != values_.size()) {
		throw "Lines and Values must match in size.";
	}
	if (lines_.size() == 0) {
		throw "At least one Line must be given" ;
	}
	if (_seen == true) {
		return;
	}
	for (SimulationLine<_primitive>* line : _lines) {
		Net<SimulationLine<_primitive>, SimulationNode<_primitive>> net(line); net.addFanout(this);
	}
}

template<class _primitive>
inline Value<_primitive> Combination<_primitive>::evaluate(std::vector<Value<_primitive>> _values) {
	if (_values.size() != values_.size()) {
		throw "The size of values must match";
	}
	for (size_t i = 0; i < values_.size(); i++) { 
		if (values_.at(i) != _values.at(i)) {
			return Value<_primitive>();
		}
	}
	//Values match, delete all input connections.
	for (SimulationLine<_primitive>* line : this->lines_) {
		Net<SimulationLine<_primitive>, SimulationNode<_primitive>> net(line); net.removeFanout(this);
	}
	return Value<_primitive>();
}

template<class _primitive>
inline bool Combination<_primitive>::seen() const {
	if (this->lines_.size() == 0) {
		return false;
	}
	return this->Node::inputs().size() == 0;
}

template<class _primitive>
inline std::vector<Value<_primitive>> Combination<_primitive>::currentValues() {
	std::vector<Value<_primitive>> toReturn;
	for (SimulationLine<_primitive>* line : this->lines_) {
		toReturn.push_back(line->value());
	}
	return toReturn;
}

template<class _primitive>
inline std::vector<Value<_primitive>> Combination<_primitive>::targetValues() const {
	return this->values_;
}

template<class _primitive>
inline std::unordered_set<SimulationLine<_primitive>*> Combination<_primitive>::lines() {
	return this->lines_;
}


#endif