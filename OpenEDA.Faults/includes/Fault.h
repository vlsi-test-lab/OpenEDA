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
	 * The given object is stuck at the given Value.
	 *
	 * @param _location The location of the Fault.
	 * @param _value The stuck-at value of the Fault.
	 */
	Fault(FaultyLine<_primitive> _location, Value<_primitive> _value);

	/*
	 * Return the value of this Fault.
	 *
	 * @return The stuck-at value of the fault.
	 */
	Value<_primitive> value() const;

	/*
	 * Activate the Fault.
	 *
	 * @return The Value currently on the Faulty object (before activation).
	 */
	Value<_primitive> activate();

	/*
	 * Deactivate the Fault.
	 *
	 * @return The Value of the Faulty object (before deactivation).
	 */
	Value<_primitive> deactivate();

	/*
	 * Activate this Fault and return all output nodes which need to be 
	 * re-evaluated.
	 *
	 * It will be presumed that the (de)activation changes the value.
	 *
	 * The fault will not be (de)activated.
	 *
	 * @return New events (and their priority) created by activating this event.
	 */
	virtual std::set<std::pair<size_t, Evented<_primitive>*>> go();

private:
	/*
	 * The location of the Fault.
	 */
	FaultyLine<_primitive>* location_;

	/*
	 * The Value (when active) of the Fault.
	 */
	Value<_primitive> value_;
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
class Faulty : public Valued<_primitive> {
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
	virtual Value<_primitive> value(Value<_primitive> _value);

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