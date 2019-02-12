/**
 * @file Combination.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-14
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "Combination.h"

template<class _primitive>
Combination<_primitive>::Combination() {
}

template<class _primitive>
Combination<_primitive>::Combination(
	std::unordered_set<TraceLine<_primitive>*> _lines,
	std::vector<Value<_primitive>> _values,
	bool _seen)
	: TraceNode<_primitive>(
		new CopyFunction<_primitive>("comb"),
		_lines,
		std::unordered_set<TraceLine<_primitive>*>()
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
	for (TraceLine<_primitive>* line : _lines) {
		line->addOutput(this);
//DELETE		Net<TraceLine<_primitive>, SimulationNode<_primitive>> net(line); net.addFanout(this);
	}
}

template<class _primitive>
Value<_primitive> Combination<_primitive>::value(std::vector<Value<_primitive>> _values) {
	if (_values.size() != values_.size()) {
		throw "The size of values must match";
	}
	for (size_t i = 0; i < values_.size(); i++) {
		if (values_.at(i) != _values.at(i)) {
			return Value<_primitive>();
		}
	}
	//Values match, delete all input connections.
	for (TraceLine<_primitive>* line : this->lines_) {
		line->removeOutput(this);
//Delete		Net<TraceLine<_primitive>, SimulationNode<_primitive>> net(line); net.removeFanout(this);
	}
	return Value<_primitive>();
}

template<class _primitive>
bool Combination<_primitive>::seen() const {
	if (this->lines_.size() == 0) {
		return false;
	}
	return this->inputs().size() == 0;
}

template<class _primitive>
std::vector<Value<_primitive>> Combination<_primitive>::currentValues() {
	std::vector<Value<_primitive>> toReturn;
	for (TraceLine<_primitive>* line : this->lines_) {
		toReturn.push_back(line->value());
	}
	return toReturn;
}

template<class _primitive>
std::vector<Value<_primitive>> Combination<_primitive>::targetValues() const {
	return this->values_;
}

template<class _primitive>
std::unordered_set<TraceLine<_primitive>*> Combination<_primitive>::lines() {
	return this->lines_;
}

template class Combination<bool>;