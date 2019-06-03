/**
 * @file Testpoint.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-05
 *
 * @copyright Copyright (c) 2019
 *
 */


#ifndef Testpoint_h
#define Testpoint_h

#include "Circuit.h"
#include "FaultStructures.hpp"
#include "Value.h"


/*
 * An object capible of modifying a circuit when activated.
 *
 * This class is pure virtual. Other methods must define the actions
 * corresponding to activation.
 *
 * A testpoint is "valued" in the sense that it will return value of its
 * location (presuming it is active).
 *
 * @parameter _primitive The data primitive of simulation.
 * @parameter _nodeType When new needs are created, what kind of node should be created?
 * @parameter _lineType When new lines are created, what kind of line should be created?
 */
template <class _primitive, class _nodeType, class _lineType>
class Testpoint : virtual public Valued<_primitive> {
public:
	/*
	 * Create a testpoint on a given Line.
	 *
	 * The testpoint will not be activated (i.e., no circuit modification will be
	 * done.
	 *
	 * @param _location The location of the testpoint
	 * @param (optional) _value The "value" of this testpoint.
	 */
	Testpoint(_lineType* _location, Value<_primitive> _value = Value<_primitive>()) {
		this->location_ = _location;
	}

	/*
	 * Two Testpoints are equal if they are on the same location.
	 *
	 * @param _other The other Testpoint being compared to.
	 * @return True if both are on the same location.
	 */
	virtual bool operator == (const Testpoint<_primitive, _nodeType, _lineType>& _other) const {
		return (this->location_ == _other.location());
	}

	/*
	 * See the overloaded operator "==", as this is the logical opposite.

	 * @param _other The other Testpoint being compared to.
	 * @return True if the Testpoints are different.
	 */
	virtual bool operator != (const Testpoint<_primitive, _nodeType, _lineType>& _other) const {
		return !(*this == _other);
	}

	/*
	 * Compaitor function (needed for sorted hashes of faults).
	 *
	 * The first "priotiry" of the sort is the pointer to the location.
	 *
	 * @param _other The other Testpoints being compared to.
	 */
	virtual bool operator < (const Testpoint<_primitive, _nodeType, _lineType>& _other) const {
		return (this->location_ < _other.location());
	}

	/*
	 * Activate the Testpoint by modifying the circuit.
	 *
	 * Lines may be created by this function.
	 *
	 * @param (optional) _circuit The circuit which (may) be modified (extra
	 *        nodes/pis/pos may be added/removed). If no circuit is given, then no
	 *        circuit will be modified. This can be useful if adding/removing
	 *        nodes to the circuit is not necessary.	 
	 * @return A set of new nodes created during activation.
	 */
	virtual std::unordered_set<_nodeType*> activate(Circuit* _circuit = nullptr) = 0;

	/*
	 * Deactivate the Testpoint by modifying the circuit.
	 *
	 * Lines may be deleted by this function.
	 *
	 * @param (optional) _circuit The circuit which (may) be modified (extra 
	 *        nodes/pis/pos may be added/removed). If no circuit is given, then no
	 *        circuit will be modified. This can be useful if adding/removing
	 *        nodes to the circuit is not necessary.
	 * @return A set of node whichs should be (but was not) deleted.
	 */
	virtual std::unordered_set<_nodeType*> deactivate(Circuit* _circuit = nullptr) = 0;

	/*
	 * The location of the TP.
	 *
	 * @return The location of the TP.
	 */
	_lineType* location() const {
		return this->location_;
	}


protected:
	/*
	 * The location of the Testpoint.
	 *
	 * @return The location of the Testpoint.
	 */
	_lineType* location_;
};




#endif
