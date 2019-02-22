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
	 * Two Testpoints are equal if they are on the same location.
	 *
	 * @param _other The other Testpoint being compared to.
	 * @return True if both are on the same location.
	 */
	bool operator == (const Testpoint<_primitive>& _other) const;

	/*
	 * See the overloaded operator "==", as this is the logical opposite.

	 * @param _other The other Testpoint being compared to.
	 * @return True if the Testpoints are different.
	 */
	bool operator != (const Testpoint<_primitive>& _other) const;

	/*
	 * Compaitor function (needed for sorted hashes of faults).
	 *
	 * The first "priotiry" of the sort is the pointer to the location.
	 *
	 * @param _other The other Testpoints being compared to.
	 */
	bool operator < (const Testpoint<_primitive>& _other) const;

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

	/*
	 * The location of the TP.
	 *
	 * @return The location of the TP.
	 */
	FaultyLine<_primitive>* location() const {
		return this->location_;
	}


protected:
	/*
	 * The location of the Testpoint.
	 *
	 * @return The location of the Testpoint.
	 */
	FaultyLine<_primitive>* location_;
};


template<class _primitive>
inline bool Testpoint<_primitive>::operator==(const Testpoint<_primitive>& _other) const {
	return (this->location_ == _other.location());
}

template<class _primitive>
inline bool Testpoint<_primitive>::operator!=(const Testpoint<_primitive>& _other) const {
	return !(*this == _other);
}

template<class _primitive>
inline bool Testpoint<_primitive>::operator<(const Testpoint<_primitive>& _other) const {
	return (this->location_ < _other.location());
}

#endif
