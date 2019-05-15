/**
 * @file Testpoint_observe.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-13
 *
 * @copyright Copyright (c) 2019
 *
 */


#ifndef Testpoint_observe_h
#define Testpoint_observe_h

#include "Testpoint.hpp"
#include "FaultStructures.hpp"
#include "Value.h"

 /*
  * An observe testpoint.
  *
 * @parameter _primitive The data primitive of simulation.
 * @parameter _nodeType When new needs are created, what kind of node should be created?
 * @parameter _lineType When new lines are created, what kind of line should be created?
 */
template <class _primitive, class _nodeType, class _lineType>
class Testpoint_observe : public Testpoint<_primitive, _nodeType, _lineType> {
public:
	/*
	 * Create an observe testpoint with a given constant value.
	 *
	 * @param _locaiton The location of the testpoint.
	 * @param (ignored) _value
	 */
	Testpoint_observe(_lineType* _location, Value<_primitive> _value = Value<_primitive>()) :
		Testpoint<_primitive, _nodeType, _lineType>(_location) {
		this->newNode_ = nullptr;
	};

	/*
	 * Activate the Testpoint by modifying the circuit.
	 *
	 * The location will have an output node added.
	 *
	 * @return A set of new nodes created during activation.
	 */
	virtual std::unordered_set<_nodeType*> activate() {
		if (this->newNode_ != nullptr) {
			throw "Obseve point is already active.";
		}
		this->newNode_ = new _nodeType(
			new CopyFunction<_primitive>(
				"po"
				)
			);
		this->location_->addOutput(this->newNode_);
		return std::unordered_set<_nodeType*>({ this->newNode_ });
	};

	/*
	 * Deactivate the Testpoint by modifying the circuit.
	 *
	 * @return A set of node whichs should be (but was not) deleted.
	 */
	virtual std::unordered_set<_nodeType*> deactivate(){
		this->location_->removeOutput(this->newNode_);
		_nodeType* toReturn = this->newNode_;
		this->newNode_ = nullptr;
		return std::unordered_set<_nodeType*>({ toReturn });
	};

private:
	/*
	 * The new node created to implement the observe point (the PO).
	 */
	_nodeType* newNode_;
};

#endif


