/**
 * @file Tracer.hpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-05-17
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef Tracer_h
#define Tracer_h

#include "Tracable.h"

/*
 * A tracer is able to trace forward and backwards in a circuit and return the
 * requested elements.
 *
 * This class is purely static and therefore has no constructors.
 *
 * NOTE: The node type and line types to be trace must both inherit from
 *       "Tracable".
 *
 * @param _lineType When tracing, the type of lines to consider.
 * @param _nodeType When tracing, the type of nodes to consider.
 *
 */
template <class _lineType, class _nodeType>
class Tracer {
public:
	/*
	 * Trace backwards a given number of levels from the tracable elements. When
	 * tracing, only nodes will be considered a "level" (i.e., lines will not
	 * count as a level).
	 *
	 * The returned value are the end nodes of the trace.
	 *
	 * All visited elements are returned by refference through the input parameter,
	 * "_flagged". All visited nodes will have their flags disabled after being
	 * visited.
	 *
	 * If the number of levels to trace backwards is given, the maximum
	 * value is given (trace to endpoints).
	 *
	 * An exception will be thrown if this object does not any inputs and is not
	 * a stopping point (i.e., is not a node of the given type and has no inputs).
	 *
	 * @param _points The elements (nodes or lines) to trace backwards on.
	 * @param _flagged The set of visited nodes. An empty set can be given.
	 * @param (optional) _levels How many levels to trace backwards by.
	 * @return The set of end-nodes reached through tracing backwards
	 */
	static std::unordered_set<_nodeType*> backwards(
		std::unordered_set<Tracable*> _points,
		std::unordered_set<Tracable*> & _flagged,
		size_t _levels = std::numeric_limits<std::size_t>::max()
	) {
		std::unordered_set<_nodeType*> toReturn;
		for (Tracable* point : _points) {
			if (point->flag() == true) {
				throw "Cannot trace on point which has had flag set elsewhere.";
			}
			std::unordered_set<_nodeType*> toAdd = Tracer<_lineType, _nodeType>::backwards(point, _flagged, _levels);
			toReturn.insert(toAdd.begin(), toAdd.end());
		}
		Tracer<_lineType, _nodeType>::cleanUp(_flagged);
		return toReturn;
	}

private:
	/*
	 * Trace backwards a given number of levels from this tracable element. When
	 * tracing, only nodes will be considered a "level" (i.e., lines will not
	 * count as a level).
	 *
	 * The returned value are the end nodes of the trace.
	 *
	 * All visited elements are returned by refference through the input parameter,
	 * "_flagged". All visited nodes will have their flags disabled after being
	 * visited.
	 *
	 * If the number of levels to trace backwards is given, the maximum
	 * value is given (trace to endpoints).
	 *
	 * An exception will be thrown if this object does not any inputs and is not
	 * a stopping point (i.e., is not a node of the given type and has no inputs).
	 *
	 * @param _point The element (node or line) to trace backwards on.
	 * @param _flagged The set of visited nodes. An empty set can be given.
	 * @param (optional) _levels How many levels to trace backwards by.
	 * @return The set of end-nodes reached through tracing backwards
	 */
	static std::unordered_set<_nodeType*> backwards(
		Tracable* _point,
		std::unordered_set<Tracable*> & _flagged,
		size_t _levels = std::numeric_limits<std::size_t>::max()
	) {
		std::unordered_set<_nodeType*> toReturn;
		
		if (_point->flag(true) == true) { //Already visited.
			return toReturn;
		}
		_flagged.emplace(_point);

		_nodeType* endpointCast = dynamic_cast<_nodeType*>(_point);
		if (endpointCast != nullptr) { //This is possibly an endpoint.
			_levels--;
			if (_levels == 0 || _point->inputs().size() == 0) { //Don't go any further: depth and/or endpoint reached.
				toReturn.emplace(endpointCast);
				return toReturn;
			}
		}

		//Error condition: this is not a endpoint but has no inputs.
		if (_point->inputs().size() == 0) {
			throw "Trace failure: no endpoint could be reached.";
		}
		
		//Computation.
		for (Connecting* input : _point->inputs()) {
			Tracable* cast = dynamic_cast<Tracable*>(input);
			std::unordered_set<_nodeType*> toAdd = Tracer<_lineType, _nodeType>::backwards(cast, _flagged, _levels);
			toReturn.insert(toAdd.begin(), toAdd.end());
		}
		return toReturn;

	}


	/*
	 * Clean up a list of visited elements.
	 *
	 * @param _visited The list of visited elements.
	 */
	static void cleanUp(std::unordered_set<Tracable*> _visited) {
		for (Tracable* visited : _visited) {
			if (visited->flag(false) == false) {
				throw "During trace clean-up, this should be impossible.";
			}
		}
	}
};
 

#endif