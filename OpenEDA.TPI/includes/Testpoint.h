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

#include "FaultStructures.hpp"


/*
 * An object capible of modifying a circuit when activated.
 *
 * This class is pure virtual. Other methods must define the actions
 * corresponding to activation.
 *
 * @parameter _primitive The data primitive of simulation.
 */
template <class _primitive>
class Testpoint {
public:
	/*
	 * Create a testpoint on a given Line.
	 *
	 * The testpoint will not be activated (i.e., no circuit modification will be
	 * done.
	 *
	 * @param _location The location of the testpoint
	 */
	Testpoint(FaultyLine<_primitive>* _location) {
		this->location_ = _location;
	}

	/*
	 * Activate the Testpoint by modifying the circuit.
	 *
	 * @return A new node created during activation.
	 */
	virtual SimulationNode<_primitive>* activate() = 0;

	/*
	 * Deactivate the Testpoint by modifying the circuit.
	 *
	 * @return A node which must be (but is not yet) deleted.
	 */
	virtual SimulationNode<_primitive>* deactivate() = 0;


private:
	/*
	 * The location of the Testpoint.
	 *
	 * @return The location of the Testpoint.
	 */
	FaultyLine<_primitive>* location_;
};

#endif