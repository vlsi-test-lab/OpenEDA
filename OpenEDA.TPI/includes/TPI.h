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
#include "Circuit.h"

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
	 * Create a TPI algorithm with a given TP, quality, and time limit (in 
	 * seconds).
	 *
	 * @param _circuit The circuit to insert TPs into.
	 * @param (optional) _TPLimit The maximumum allowed TPs to insert. By
	 *        default, this will be the maximum possible.
	 * @param (optional) _qualityLimit The maximum quality to achieve.
	 *        By default, this is will 100% (1.0f).
	 * @param (optional) _timeLimit The maximum time (in seconds) to spend
	 *        on TPI. By default, this will be the "maximum possible time".
	 */
	TPI(
		Circuit* _circuit,
		size_t _TPLimit = std::numeric_limits<size_t>::max(),
		float _qualityLimit = 1.0,
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
	 * An exception will be thrown if the testpoint limits do not match the
	 * number of testpoint sets.
	 *
	 * @param _testpoints The testpoints to evaluate. This is given as a "set
	 *        of sets", where each set as a limit assigned to it. This limit
	 *        designates the maximum number of testpoints to choose from the 
	 *        attached set.
	 * @param (optional) _limits The limit to the number of testpoints for each
	 *        set. If no limits is given, no limit will be given to any set.
	 */
	std::set<Testpoint<_primitive>*> testpoints(
		std::vector<std::set<Testpoint<_primitive>*>> _testpoints,
		std::vector<size_t> _limits = std::vector<size_t>
	);

	/*
	 * Set the time limit (and reset the timer).
	 *
	 * @param The new time limit (in seconds).
	 */
	void timeLimit(size_t _timeLimit);

	/*
	 * Set the testpoint limit.
	 *
	 * @param The new testpoint limit.
	 */
	void testpointLimit(size_t _testpointLimit);

protected:
	/*
	 * Return the "quality" of this testpoint.
	 *
	 * The relative measure of this testpoing is irrelevant as long as
	 * "no quality" (i.e., this testpoint should never be chosen) is a negative
	 * number.
	 *
	 * @param _testpoint The testpoint to measure.
	 * @return The quality of the testpoint.
	 */
	virtual float quality(Testpoint<_primitive>* _testpoint) = 0;

	/*
	 * The circuit this TPI is attached to
	 */
	Circuit* circuit_;

private:
	/*
	 * Return the "base" quality (no extra TP fault coverage) to compare other
	 * testpoints against.
	 *
	 * This function will be used to "bestTestpoint" to return final quality.
	 *
	 * If no base is needed, have it return "0" always.
	 *
	 * @return The base quality"
	 */
	virtual float base() = 0;

	/*
	 * Reset the "base" quality to compare against other testpoints against.
	 *
	 * The  input parameter manually sets the value.
	 *
	 * @param _base The manually set base value.
	 * @return The new base quality.
	 */
	virtual float base(float _base) = 0;

	/*
	 * For a given set of testpoints, return the best testpoint and its quality.
	 *
	 * @param _testpoints the set of testpoints to evaluate.
	 * @return A pair: the best testpoint and its quality.
	 */
	std::pair<Testpoint<_primitive>*, float> bestTestpoint(std::set<Testpoint<_primitive>*> _testpoints);

	/*
	 * Reset the timer.
	 */
	void resetTimer();

	/*
	 * Is time up?
	 *
	 * @return True if time is up.
	 */
	bool timeUp();
	

	/*
	 * The set TP limit
	 */
	size_t TPLimit_;

	/*
	 * The set quality limit
	 */
	float qualityLimit_;

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