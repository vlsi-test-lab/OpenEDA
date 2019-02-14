/**
 * @file Testpoint_observe.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-13
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "Testpoint_observe.h"

template<class _primitive>
Testpoint_observe<_primitive>::Testpoint_observe(
	FaultyLine<_primitive>* _location
) :
	Testpoint<_primitive>(_location)
{
}

template<class _primitive>
SimulationNode<_primitive>* Testpoint_observe<_primitive>::activate() {
	this->newNode_ = new SimulationNode<_primitive>(
		new CopyFunction<_primitive>(
			"po"
			)
		);
	this->location_->addOutput(this->newNode_);
	return this->newNode_;
}

template<class _primitive>
SimulationNode<_primitive>* Testpoint_observe<_primitive>::deactivate() {
	this->location_->removeOutput(this->newNode_);
	return this->newNode_;
}

template class Testpoint_observe<bool>;