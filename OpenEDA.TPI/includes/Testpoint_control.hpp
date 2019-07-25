/**
 * @file Testpoint_control.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-05
 *
 * @copyright Copyright (c) 2019
 *
 */


#ifndef Testpoint_control_h
#define Testpoint_control_h

#include "Testpoint.hpp"
#include "FaultStructures.hpp"
#include "Value.h"

/*
 * A control testpoint (both control-0 and control-1).
 *
 * @parameter _primitive The data primitive of simulation.
 * @parameter _nodeType When new needs are created, what kind of node should be created?
 * @parameter _lineType When new lines are created, what kind of line should be created?
 */
template <class _primitive, class _nodeType, class _lineType>
class Testpoint_control : public Testpoint<_primitive, _nodeType, _lineType> {
public:
	/*
	 * Create a control testpoint with a given constant value.
	 *
	 * @param _locaiton The location of the testpoint.
	 * @param _value The value forced by the testpoint.
	 */
	Testpoint_control(_lineType* _location, Value<_primitive> _value) :
		Testpoint<_primitive, _nodeType, _lineType>(_location),
		Valued<_primitive>(_value)
	{
		
	};

	/*
	 * Two control testpoints are equal if they are on the same location and
	 * the same value.
	 *
	 * @param _other The other Testpoint being compared to.
	 * @return True if both are on the same location.
	 */
	virtual bool operator == (const Testpoint_control<_primitive, _nodeType, _lineType>& _other) const {
		if (this->value() != _other.value()) {
			return false;
		}
		if (this->location_ != _other.location()) {
			return false;
		}
		return true;
	};

	/*
	 * See the overloaded operator "==", as this is the logical opposite.

	 * @param _other The other Testpoint being compared to.
	 * @return True if the Testpoints are different.
	 */
	virtual bool operator != (const Testpoint_control<_primitive, _nodeType, _lineType>& _other) const {
		return !(*this == _other);
	};

	/*
	 * Compaitor function (needed for sorted hashes of faults).
	 *
	 * The first "priotiry" of the sort is the pointer to the location.
	 *
	 * @param _other The other Testpoints being compared to.
	 */
	virtual bool operator < (const Testpoint_control<_primitive, _nodeType, _lineType>& _other) const {
		if (this->location_ < _other.location()) {
			return true;
		}
		if (this->location_ > _other.location()) {
			return false;
		}
		if (this->value() < _other.value()) {
			return true;
		}
		return false;
	};

	/*
	 * Activate the Testpoint by modifying the circuit.
	 *
	 * The location will have its input removed and replaced by a constant-value
	 * holding Node (returned).
	 *
	 * @param (optional) _circuit The circuit which (may) be modified (extra
	 *        nodes/pis/pos may be added/removed). If no circuit is given, then no
	 *        circuit will be modified. This can be useful if adding/removing
	 *        nodes to the circuit is not necessary.	 
	 * @return A set of new nodes created during activation.
	 */
	virtual std::unordered_set<_nodeType*> activate(Circuit* _circuit = nullptr) {
		//DEBUG
		//if (this->location_->inputs().size() != 1) {
		//	throw "Problem: Before control point inserted, the location does not have exactly 1 driver.";
		//}
		if (this->newNode_ != nullptr) {
			throw "Cannot activate control testpoint: already activated.";
		}
		this->newNode_ = new _nodeType(
			new CopyFunction<_primitive>(
				"const",
				this->value()
				)
			);
		
		//DELETE: flawed. Replaced with the following.
		/*std::unordered_set<Connecting*> inputs = this->location_->inputs();
		if (inputs.size() > 0) {
			this->oldDriver_ = *(inputs.begin());
			this->location_->removeInput(oldDriver_);
		}*/
		float oldcc = this->location_->controllability();
		float c = this->value().magnitude();
		float newcc = (c + oldcc) / 2;
		this->location_->clearControllability();
		this->location_->controllability(newcc);
		this->oldDrivers_ = this->location_->inputs();
		for (Connecting* input : this->oldDrivers_) {
			input->removeOutput(this->location_);
			input->addOutput(this->newNode_);
		}
		//DEBUG
		//if (this->location_->inputs().size() != 0) {
		//	throw "Problem: after old inputs disconnected, the location still has drivers.";
		//}
		this->location_->addInput(this->newNode_);
		//DEBUG
		/*if (this->location_->inputs().size() != 1) {
			throw "Problem: after control point inserted, the location does not have exactly 1 driver.";
		}*/
		if (_circuit != nullptr) {
			_circuit->addNode(this->newNode_);
		}
		return std::unordered_set<_nodeType*>({ this->newNode_ });
	}

	/*
	 * Deactivate the Testpoint by modifying the circuit.
	 *
	 * @param (optional) _circuit The circuit which (may) be modified (extra
	 *        nodes/pis/pos may be added/removed). If no circuit is given, then no
	 *        circuit will be modified. This can be useful if adding/removing
	 *        nodes to the circuit is not necessary.	 
	 * @return A set of node whichs should be (but was not) deleted.
	 */
	virtual std::unordered_set<_nodeType*> deactivate(Circuit* _circuit = nullptr) {
		this->location_->removeInput(this->newNode_);

		//DELETE: flawed. Replaced with the following.
		/*if (this->oldDriver_ != nullptr) {
			this->location_->addInput(oldDriver_);
		}*/
		for (Connecting* oldDriver : this->oldDrivers_) {
			oldDriver->removeOutput(this->newNode_);
			oldDriver->addOutput(this->location_);
		}
		this->oldDrivers_.clear();

		if (_circuit != nullptr) {
			_circuit->removeNode(this->newNode_);
		}
		_nodeType* toReturn = this->newNode_;
		this->newNode_ = nullptr;
		return std::unordered_set<_nodeType*>({ toReturn });
	};

private:
	/*
	 * The object(s) which was/were previously connected to before this TP was activated.
	 *
	 * Can be empty if not yet activated.
	 */
	std::unordered_set<Connecting*> oldDrivers_;

	/*
	 * The new node created to implement a constant value.
	 *
	 * This will feed the controlled line as well as be fed by the original driver
	 * (which will force it's observability to 0 if needed).
	 */
	_nodeType* newNode_ = nullptr;


};

#endif