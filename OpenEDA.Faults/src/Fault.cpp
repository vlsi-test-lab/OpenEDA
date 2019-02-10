/**
 * @file Fault.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-21
 *
 * @copyright Copyright (c) 2018
 *
 */

#include "Fault.h"
#include "SimulationStructures.hpp"

template<class _primitive>
Fault<_primitive>::Fault(FaultyLine<_primitive> _location, Value<_primitive> _value) {
	this->location_ = _location;
	this->value_ = _value;
}

template<class _primitive>
Value<_primitive> Fault<_primitive>::value() const {
	return this->value();
}

template<class _primitive>
Value<_primitive> Fault<_primitive>::activate() {
	Value<_primitive> oldValue = this->location_->value();
	this->location_->activate(this);
	return oldValue;
}

template<class _primitive>
Value<_primitive> Fault<_primitive>::deactivate() {
	Value<_primitive> oldValue = this->location_->value();
	this->location_->deactivate(this);
	return oldValue;
}

template<class _primitive>
std::set<std::pair<size_t, Evented*>> Fault<_primitive>::go() {
	std::set<std::pair<size_t, Evented*>> toReturn;

	SimulationLine<_primitive> line = dynamic_cast<SimulationLine<_primitive>*>(this->location_);
	line->value(this->value_);

	//Is this a fanout?
	if (line->isOutputNode() == true) {//yes
		SimulationNode<_primitive>* output = dynamic_cast<SimulationNode<_primitive>*>(*(line->outputs().begin()));
		toReturn.emplace(
			std::pair<size_t, SimulationNode<_primitive>*>(
				output->inputLevelConst(), output
			)
		);
		return toReturn;
	}

	//no
	SimulationNet<_primitive> net(line);
	for (SimulationNode<_primitive>* fanoutNode : net.fanoutNodes()) {
		toReturn.emplace(
			std::pair<size_t, SimulationNode<_primitive>*>(
				fanoutNode->inputLevelConst(), 
				fanoutNode
				)
		);
	}

	return toReturn;
}

template<class _primitive>
Faulty<_primitive>::Faulty() {
	this->active_ = false;
}

template<class _primitive>
Value<_primitive> Faulty<_primitive>::value() const {
	//Is there an active fault on this line?
	if (this->active_ == false) {//yes
		return this->Valued<_primitive>::value();
	}
	//no
	return this->fault_.value();
}

template<class _primitive>
Value<_primitive> Faulty<_primitive>::value(Value<_primitive> _value) {
	this->Valued<_primitive>::value(_value);
	return this->value(); //Will redirect to faulty value if needed.
}

template<class _primitive>
Value<_primitive> Faulty<_primitive>::activate(Fault<_primitive> _fault) {
	if (this->active_ == true) {
		throw "Cannot active fault: already active.";
	}
	this->active_ = true;
	this->fault_ = _fault;
	return this->fault_.value();
}

template<class _primitive>
Value<_primitive> Faulty<_primitive>::deactivate(Fault<_primitive> _fault) {
	if (this->active_ == false) {
		throw "Cannot deactivate fault: no fault is active.";
	}
	if (_fault != this->fault_) {
		throw "Cannot deactiveate fault: incorrect fault.";
	}
	this->active_ = false;
	return this->value();
}
