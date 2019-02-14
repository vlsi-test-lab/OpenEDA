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
Fault<_primitive>::Fault() {
	this->location_ = nullptr;
	this->value_ = Value<_primitive>();
}

template<class _primitive>
Fault<_primitive>::Fault(FaultyLine<_primitive> * _location, Value<_primitive> _value) {
	this->location_ = _location;
	this->value_ = _value;
}

template<class _primitive>
Fault<_primitive>::~Fault() {
}

template<class _primitive>
Fault<_primitive>::Fault(const Fault<_primitive>& _fault) {
	this->location_ = _fault.location();
	this->value_ = _fault.value();
}

template<class _primitive>
Fault<_primitive> Fault<_primitive>::operator=(const Fault<_primitive> _fault) {
	this->location_ = _fault.location();
	this->value_ = _fault.value();
	return *this;
}

template<class _primitive>
bool Fault<_primitive>::operator==(const Fault<_primitive>& _other) const {
	if (this->value_ != _other.value()) {
		return false;
	}
	if (this->location_ != _other.location()) {
		return false;
	}
	return true;
}

template<class _primitive>
bool Fault<_primitive>::operator!=(const Fault<_primitive>& _other) const {
	return !(*this == _other);
}

template<class _primitive>
Value<_primitive> Fault<_primitive>::value() const {
	return this->value();
}

template<class _primitive>
FaultyLine<_primitive>* Fault<_primitive>::location() const {
	return this->location_;
}

template<class _primitive>
bool Fault<_primitive>::activate() {
	Value<_primitive> oldValue = this->location_->value();
	Value<_primitive> newValue = this->location_->activate(*this);
	return oldValue != newValue ;
}

template<class _primitive>
bool Fault<_primitive>::deactivate() {
	Value<_primitive> oldValue = this->location_->value();
	Value<_primitive> newValue = this->location_->deactivate(*this);
	return oldValue != newValue;
}

template<class _primitive>
std::set<std::pair<size_t, Evented<_primitive>*>> Fault<_primitive>::go() {
	bool forwardUpdateCall = false;
	//Is this fault currently active?
	if (this->location_->isFaultActive(*this) == true) {
		forwardUpdateCall = this->deactivate();
	} else {
		forwardUpdateCall = this->activate();
	}

	if (forwardUpdateCall == true) {
		return this->location_->go();
	}

	return std::set<std::pair<size_t, Evented<_primitive>*>>();
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
Value<_primitive> Faulty<_primitive>::value(std::vector<Value<_primitive>> _values) {
	this->Valued<_primitive>::value(_values);
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

template<class _primitive>
bool Faulty<_primitive>::isFaultActive(Fault<_primitive> _fault) {
	return fault_ == _fault;
}

template class Fault<bool>;
template class Faulty<bool>;