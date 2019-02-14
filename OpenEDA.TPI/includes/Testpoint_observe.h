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

#include "Testpoint.h"
#include "FaultStructures.hpp"
#include "Value.h"

 /*
  * An observe testpoint.
  *
  * @parameter _primitive The data primitive of simulation.
  */
template <class _primitive>
class Testpoint_observe : public Testpoint<_primitive> {
public:
	/*
	 * Create an observe testpoint with a given constant value.
	 *
	 * @param _locaiton The location of the testpoint.
	 */
	Testpoint_observe(FaultyLine<_primitive>* _location);

	/*
	 * Activate the Testpoint by modifying the circuit.
	 *
	 * The location will have an output node added.
	 *
	 * @return A new node created during activation.
	 */
	virtual SimulationNode<_primitive>* activate();

	/*
	 * Deactivate the Testpoint by modifying the circuit.
	 *
	 * @return A node which must be (but is not yet) deleted.
	 */
	virtual SimulationNode<_primitive>* deactivate();

private:
	/*
	 * The new node created to implement the observe point.
	 */
	SimulationNode<_primitive>* newNode_;
};

#endif


