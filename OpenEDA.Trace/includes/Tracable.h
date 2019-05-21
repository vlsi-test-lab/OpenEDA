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
			 std::string _name = ""
	);

private:

};

#endif