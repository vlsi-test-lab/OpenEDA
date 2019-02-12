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
Testpoint_control<_primitive>::Testpoint_control(Value<_primitive> _value, FaultyLine<_primitive>* _location) : Testpoint<_primitive>(_location){
	this->value_ = _value;
	this->oldDriver_ = nullptr;
	this->oldDriverWasNode_ = false;
}


template<class _primitive>
SimulationNode<_primitive>* Testpoint_control<_primitive>::activate() {
	if (this->newNode_ != nullptr) {
		throw "Cannot activate control testpoint: already activated.";
	}
	this->newNode = new SimulationNode<_primitive>(
		new CopyFunction<_primitive>(
			"constant"
			)
		);

	std::vector<Connecting*> inputs = this->location_->inputs();
	if (inputs.size() > 0) {
		this->oldDriver_ = inputs.at(0);
		this->location_->removeInput(oldDriver_);
	}
	this->location_->setInputNode(this->newNode);
	return this->newNode;
}

template<class _primitive>
SimulationNode<_primitive>* Testpoint_control<_primitive>::deactivate() {
	this->location_->removeInput(this->newNode_);
	if (this->oldDriver_ != nullptr) {
		this->location_->addInput(oldDriver_);
	}
	SimulationNode<_primitive>* toReturn = this->newNode;
	this->newNode_ = nullptr;
	return nullptr;
}
