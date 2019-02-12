/**
 * @file Combination.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-14
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef Combination_h
#define Combination_h

#include <set>
#include <vector>

#include "SimulationStructures.hpp"
#include "TraceStructures.hpp"
#include "Function.h"


/*
 * A combination of Line values in a circuit.
 *
 * A Combination is a special type of 'Node' which represents a combination of 
 * particular objects in a circuit at particular Values.
 *
 * During simulation, if the combination is updated to the designated Values,
 * then the input connections to the combination will be removed.
 *
 * @param _primitive The underlying data primitive to simulate.
 */
template <class _primitive>
class Combination : public TraceNode<_primitive> {
public:
	/*
	 * By default, a Combination has no Lines and no Values, which will be
	 * interpreted as not-seen.
	 */
	Combination();

	/*
	 * Create a Combination of a given set of lines at a given set (vector) of Values.
	 *
	 * It is not valid to have a combination with no Lines or Values, or to have the number
	 * of Lines and Values not match.
	 *
	 * @param _lines The Lines to measure values on.
	 * @param _values The Values to be measured.
	 * @param _seen (optional) If set, this parameter is considered "already seen".
	 */
	Combination(
		std::unordered_set<TraceLine<_primitive>*> _lines, 
		std::vector<Value<_primitive>> _values, 
		bool _seen = false
	);

	/*
	 * Check if this combination has been seen. If so, remove its connections.
	 *
	 * An exception will be thrown if the size of the given Values is different the the Combination's Values.
	 *
	 * @param _values The Values to evaluate using this object's function.
	 * @return The evaluated value of this object (will always be the default Value).
	 */
	virtual Value<_primitive> value(std::vector<Value<_primitive>> _values);

	/*
	 * Has this combination been seen.
	 *
	 * @return True if the combination has been seen.
	 */
	bool seen() const;

	/*
	 * The current input Values seen by this Combination.
	 *
	 * @return The current input Values seen by this Combination.
	 */
	std::vector<Value<_primitive>> currentValues() ;

	/*
	 * The target values of this Combination.
	 *
	 * @return The target values of this Combination.
	 */
	std::vector<Value<_primitive>> targetValues() const;

	/*
	 * Return the Lines polled by this Combination.
	 *
	 * @return The Lines polled by this Combination.
	 */
	std::unordered_set<TraceLine<_primitive>*> lines();

private:
	/*
	 * The Lines of this Combination.
	 */
	std::unordered_set<TraceLine<_primitive>*> lines_;

	/*
	 * The Values of this Combination.
	 */
	std::vector<Value<_primitive>> values_;

};


#endif