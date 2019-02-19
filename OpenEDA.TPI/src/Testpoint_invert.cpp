/**
 * @file Testpoint_invert.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-19
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "Testpoint_invert.h"

template<class _primitive>
Testpoint_invert<_primitive>::Testpoint_invert(FaultyLine<_primitive>* _location) :
	Testpoint<_primitive>(_location)
{
	this->oldDriver_ = nullptr;
	this->newLine_ = nullptr;
	this->newNode_ = nullptr;
}

template<class _primitive>
SimulationNode<_primitive>* Testpoint_invert<_primitive>::activate() {
	if (this->oldDriver_ != nullptr || this->newLine_ != nullptr || this->newNode_ != nullptr) {
		throw "This inversion TP is already active.";
	}

	this->oldDriver_ = *(this->location_->inputs().begin());
	if (this->oldDriver_ == nullptr) {
		throw "Cannot add inverstion TP to something which has no driver.";
	}

	//Remove the old driver connection.
	this->location_->removeInput(this->oldDriver_);

	//Create the new node and new line.
	this->newNode_ = new SimulationNode<_primitive>(
		new BooleanFunction("not")
		);
	std::string name = this->location_->name() + "_pre-invert";
	this->newLine_ = new SimulationLine<_primitive>(
			name
		);
	
	//Make connections.
	this->newLine_->addOutput(this->newNode_);
	this->newLine_->addInput(this->oldDriver_);
	this->location_->addInput(this->newNode_);

	return this->newNode_;
}

template<class _primitive>
SimulationNode<_primitive>* Testpoint_invert<_primitive>::deactivate() {
	if (this->oldDriver_ == nullptr && this->newLine_ == nullptr && this->newNode_ == nullptr) {
		throw "This inversion TP is not active: it cannot be deactivated.";
	}

	this->location_->addInput(this->oldDriver_);
	this->location_->removeInput(this->newNode_);
	delete this->newLine_;
	SimulationNode<_primitive>* toReturn = this->newNode_;
	this->newLine_ = nullptr;
	this->newNode_ = nullptr;
	this->oldDriver_ = nullptr;
	return toReturn;
}



template class Testpoint_invert<bool>;