/**
 * @file Tracable.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-08
 *
 * @copyright Copyright (c) 2019
 *
 */


#ifndef Tracable_h
#define Tracable_h

#include <unordered_set>
#include <limits>

#include "Flagged.hpp"
#include "Connection.h"

/*
 * This object is capible of "tracing" forward and backwards and returning
 * related objects.
 */
class Tracable : public Flagged, public virtual Connecting {
public:
	/*
	 * Create an object connected to the given inputs and outputs.
	 *
	 * Optionally, designate this as a trace-stopping object (default not).
	 *
	 * @param (optional) inputs A vector of input Connecting objects.
	 * @param (optional) outputs A vector of output Connecting objects.
	 * @param (optional) _stop Does tracing stop at this object?
	 * @param (optional) _name Name of the connection (defaults to empty strying).
	 */
	Tracable(std::unordered_set<Tracable*> _inputs = std::unordered_set<Tracable*>(),
			 std::unordered_set<Tracable*> _outputs = std::unordered_set<Tracable*>(),
			 bool _stop = false,
			 std::string _name = ""
	);

	/*
	 * Trace backwards a given number of levels from this node.
	 *
	 * The returned value are the endpoints of the trace.
	 *
	 * All visited nodes are returned by refference through the input parameter,
	 * "_flagged". All visited nodes will have their flags disabled after being
	 * visited.
	 *
	 * If the number of levels to trace backwards is given, the maximum
	 * value is given (trace to endpoints).
	 *
	 * An exception will be thrown if this object does not any inputs and is not
	 * a stopping point.
	 *
	 * @param _flagged The set of visited nodes. An empty set can be given.
	 * @param (optional) _levels How many levels to trace backwards by.
	 * @return The set of end-nodes reached through tracing backwards
	 */
	std::unordered_set<Tracable*> backwards(
		std::unordered_set<Tracable*> & _flagged,
		size_t _levels = std::numeric_limits<std::size_t>::max()
	);
	 

private:
	/*
	 * Does tracing stop at this object?
	 */
	bool stop_;
};

#endif