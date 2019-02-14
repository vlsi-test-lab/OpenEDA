/**
 * @file Testpoint_control.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-05
 *
 * @copyright Copyright (c) 2019
 *
 */


#include "Testpoint_control.h"

template<class _primitive>
Testpoint_control<_primitive>::Testpoint_control(Value<_primitive> _value, FaultyLine<_primitive>* _location) : 
	Testpoint<_primitive>(_location){
	this->value_ = _value;
	this->oldDriver_ = nullptr;
}


template<class _primitive>
SimulationNode<_primitive>* Testpoint_control<_primitive>::activate() {
	if (this->newNode_ != nullptr) {
		throw "Cannot activate control testpoint: already activated.";
	}
	this->newNode_ = new SimulationNode<_primitive>(
		new CopyFunction<_primitive>(
			"constant"
			)
		);
	this->newNode_->value(std::vector<Value<_primitive>>({this->value_}));

	std::unordered_set<Connecting*> inputs = this->location_->inputs();
	if (inputs.size() > 0) {
		this->oldDriver_ = *(inputs.begin());
		this->location_->removeInput(oldDriver_);
	}
	this->location_->addInput(this->newNode_);
	return this->newNode_;
}

template<class _primitive>
SimulationNode<_primitive>* Testpoint_control<_primitive>::deactivate() {
	this->location_->removeInput(this->newNode_);
	if (this->oldDriver_ != nullptr) {
		this->location_->addInput(oldDriver_);
	}
	SimulationNode<_primitive>* toReturn = this->newNode_;
	this->newNode_ = nullptr;
	return nullptr;
}

template class Testpoint_control<bool>;