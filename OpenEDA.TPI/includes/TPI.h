/**
 * @file TPI.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-19
 *
 * @copyright Copyright (c) 2019
 *
 */


#ifndef TPI_h
#define TPI_h

#include <utility> //pair
#include <limits>
#include <ctime>

#include "Testpoint.h"

/*
 * An algroithm which implements iterative test point insertion (TPI).
 *
 * This is a pure-virtual class describing the features of any TPI algorithm.
 *
 * @parameter _primitive The underlying data primitive used for simulation.
 */
template <class _primitive>
class TPI {
public:
	/*
	 * Create a TPI algorithm with a given TP, fault coverage
	 * (float percentage, 1.0 = 100%), and time limit (in seconds).
	 *
	 * @param (optional) _TPLimit The maximumum allowed TPs to insert. By
	 *        default, this will be the maximum possible.
	 * @param (optional) _FCLimit The maximum fault coverage to achieve.
	 *        By default, this is will 100% (1.0f).
	 * @param (optional) _timeLimit The maximum time (in seconds) to spend
	 *        on TPI. By default, this will be the "maximum possible time".
	 */
	TPI(
		size_t _TPLimit = numeric_limits<size_t>::max(),
		float _FCLimit = 1.0,
		size_t _timeLimit = std::numeric_limits<size_t>::max()
	);


	/*
	 * Evaluate the given set(s) of testpoints and return those selected to be
	 * inserted.
	 *
	 * After selection, the testpoints will NOT be active.
	 *
	 * Provding multiple sets of testpoints allows limits to be set on each
	 * set. This is given as a "limit-set" pair.
	 *
	 * @param _testpoints The testpoints to evaluate. This is given as a "set
	 *        of sets", where each set as a limit assigned to it. This limit
	 *        designates the maximum number of testpoints to choose from the 
	 *        attached set.
	 */
	std::set<Testpoint<_primitive>> testpoints(
		std::set<
			std::set<
				std::pair<
					std::size_t, Testpoint<_primitive>
				>
			>
		>
	);

	/*
	 * Set the time limit.
	 *
	 * @param The new time limit (in seconds).
	 */
	void timeLimit(size_t _timeLimit);



private:
	/*
	 * The set TP limit
	 */
	size_t TPLimit_;

	/*
	 * The set FC limit
	 */
	float FCLimit_;

	/*
	 * The time limit (in seconds).
	 */
	size_t timeLimit_;

	/*
	 * The end of the timer (in "tick time")
	 */
	std::clock_t endTime_;


};

#endif