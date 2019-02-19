/**
 * @file Testpoint_invert.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-19
 *
 * @copyright Copyright (c) 2019
 *
 */


#ifndef Testpoint_invert_h
#define Testpoint_invert_h

#include "Testpoint.h"

 /*
  * A control testpoint (both control-0 and control-1).
  *
  * @parameter _primitive The data primitive of simulation.
  */
template <class _primitive>
class Testpoint_invert : public Testpoint<_primitive> {
public:
	/*
	 * Create a testpoint with an inverstion on the given line.
	 *
	 * @param _locaiton The location of the testpoint.
	 */
	Testpoint_invert(FaultyLine<_primitive>* _location);

	/*
	 * Activate the Testpoint by modifying the circuit.
	 *
	 * The location will have its driver replaced by an inverter (which will be
	 * driven by the old driver).
	 *
	 * An exception will be thrown if already active.
	 *
	 * An exception will be thrown if the TP's location has no driver.
	 *
	 * NOTE: a new line will also be created by this function, but it is NOT
	 *       returned.
	 *
	 * @return A new node created during activation.
	 */
	virtual SimulationNode<_primitive>* activate();

	/*
	 * Deactivate the Testpoint by modifying the circuit.
	 *
	 * An exception will be thrown if the node is not activated.
	 *
	 * NOTE: the "new line" created during activation will be DELETED by this 
	 *       function.
	 *
	 * @return A node which must be (but is not yet) deleted.
	 */
	virtual SimulationNode<_primitive>* deactivate();

private:


	/*
	 * The object which was previously connected to before this TP was activated.
	 *
	 * Can be null.
	 */
	Connecting* oldDriver_;

	/*
	 * The new line created by activating this testpoint.
	 *
	 * Can be null.
	 */
	SimulationLine<_primitive>* newLine_;

	/*
	 * The new node created to implement a constant value.
	 */
	SimulationNode<_primitive>* newNode_;
};

#endif
