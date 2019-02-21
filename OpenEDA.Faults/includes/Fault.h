/**
 * @file Fault.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-17
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef Fault_h
#define Fault_h

#include <set>
#include <vector>

#include "Value.h"
#include "EventQueue.h"
#include "FaultStructures.hpp"

// Forward declaration.
template <class T>
class Faulty;
template <class T>
class FaultyLine;

/*
 * A modification to a Valued (Faulty) object.
 *
 * A Fault, when activated, will change the Value returned by a Faulty object.
 *
 * The "event" of the fault is to "activate and change fault values".
 *
 * @param _primitive The data primitive to simulate.
 */
template <class _primitive>
class Fault : public Evented<_primitive> {
public:
	/*
	 * The default fault has no (nullptr) location and a default value.
	 */
	Fault();

	/*
	 * The given object is stuck at the given Value.
	 *
	 * @param _location The location of the Fault.
	 * @param _value The stuck-at value of the Fault.
	 */
	Fault(FaultyLine<_primitive> * _location, Value<_primitive> _value);

	/*
	 * When a fault is destoryed, nothing will happen: the location will be 
	 * untouched.
	 */
	~Fault();

	/*
	 * Copy constructor: copy the fault's location and value.
	 *
	 * @param _fault The fault to copy.
	 */
	Fault(const Fault<_primitive>& _fault);

	/*
	 * Assignment operator.
	 *
	 * @param _fault The fault to assign (copy).
	 */
	Fault<_primitive> operator = (const Fault<_primitive> _fault) ;

	/*
	 * Two faults are equal if they are on the same location and hold the same value.
	 *
	 * @param _other The other fault being compared to.
	 * @return True if both magnitudes are the same and they are both valid.
	 */
	bool operator == (const Fault<_primitive>& _other) const;

	/*
	 * See the overloaded operator "==", as this is the logical opposite.

	 * @param _other The other fault being compared to.
	 * @return True if the faults are different.
	 */
	bool operator != (const Fault<_primitive>& _other) const;

	/*
	 * Compaitor function (needed for sorted hashes of faults).
	 *
	 * The first "priotiry" of the sort is the pointer to the location.
	 * The second "priotiry" is the value of the fault.
	 *
	 * @param _other The other fault being compared to.
	 */
	bool operator < (const Fault<_primitive>& _other) const;


	/*
	 * Return the value of this Fault.
	 *
	 * @return The stuck-at value of the fault.
	 */
	Value<_primitive> value() const;

	/*
	 * Return the loaction of this Fault.
	 *
	 * @return The location of this fault.
	 */
	FaultyLine<_primitive>* location() const;



	/*
	 * (De)activate this Fault and return all output nodes which need to be 
	 * re-evaluated.
	 *
	 * @return New events (and their priority) created by activating this event.
	 */
	virtual std::set<std::pair<size_t, Evented<_primitive>*>> go();

private:
	/*
	 * Activate the Fault.
	 *
	 * @return True if activating the fault changes the line's value.
	 */
	bool activate();

	/*
	 * Deactivate the Fault.
	 *
	 * @return True if deactivating the fault changes the line's value.
	 */
	bool deactivate();


	/*
	 * The location of the Fault.
	 */
	FaultyLine<_primitive>* location_;

	/*
	 * The Value (when active) of the Fault.
	 */
//DELETE (stored in the "Valued" portion)	Value<_primitive> value_;
};

/*
 * An object which can contain and act on a Fault.
 *
 * A Faulty object acts like a normal Valued object, except the Value it
 * returns can be overwritten by an active Fault.
 *
 * @param _primitive The data primitive to simulate.
 */
template <class _primitive>
class Faulty : public virtual Valued<_primitive> {
public:
	/*
	 * Initialize with the "Default" Value, which is not valid.
	 */
	Faulty();

	/*
	 * Return the Value held by this Valued object.
	 *
	 * If there is an active Fault, then the Fault's value will be returned.
	 *
	 * @return the Value held by this object (with the effect of the Fault).
	 */
	virtual Value<_primitive> value() const;



	/*
	 * Set the Value to the given Value.
	 *
	 * If a Fault is active, no effect may happen.
	 *
	 * The underlying Valued object will have its Value set, but the return Value
	 * will include the effect of the Fault.
	 *
	 * @param _value The Value to set to.
	 * @return The Value after the object is set.
	 */
	virtual Value<_primitive> value(std::vector<Value<_primitive>> _values);

	/*
	 * Activate a given Fault.
	 *
	 * An exception will be thrown if a Fault is already active.
	 *
	 * @param The Fault to activate.
	 * @return The Value of the object after the Fault is activated.
	 */
	Value<_primitive> activate(Fault<_primitive> _fault);

	/*
	 * Deactivate a given Fault.
	 *
	 * An exception will be thrown if the Fault given does not match the currently
	 * active Fault or no Fault is currently active.
	 *
	 * @param The Fault to deactivate.
	 * @return The Value of the object after the Fault is deactivated.
	 */
	Value<_primitive> deactivate(Fault<_primitive> _fault);

	/*
	 * Return true if the given fault is currently active on this line.
	 *
	 * @param _fault the Fault to check if active.
	 * @return True if the fault is currently cative.
	 */
	bool isFaultActive(Fault<_primitive> _fault);

private:
	/*
	 * Is there a fault currently active?
	 */
	bool active_;

	/*
	 * What is the currently active fault?
	 */
	Fault<_primitive> fault_;
	
};


#endif