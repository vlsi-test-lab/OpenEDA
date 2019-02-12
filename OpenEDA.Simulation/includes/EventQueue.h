/**
 * @file EventQueue.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-18
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef EventQueue_h
#define EventQueue_h

#include <utility>
#include <vector>
#include <unordered_set>
#include <set>

#include "Value.h"
#include "Level.h"

/*
 * An object which can be called to do an "event".
 *
 * @parameter _primitive The primitive data value simulated.
 */
template <class _primitive>
class Evented : public Valued<_primitive>, public Levelized {
public:
	/*
	 * Create an object which are connected to other Levelized objects.
	 *
	 * @param (optional) _inputs A vector of input Levelized objects.
	 * @param (optioanl) _outputs A vector of output Levelized objects.
	 * @param (optional) _name Name of the connection (defaults to empty strying).
	 */
	Evented(std::unordered_set<Evented<_primitive>*> _inputs = std::unordered_set<Evented<_primitive>*>(),
			std::unordered_set<Evented<_primitive>*> _outputs = std::unordered_set<Evented<_primitive>*>(),
			std::string _name = ""
	);

	/*
	 * Activate the event associated with this object and fetch subsequent events.
	 *
	 * An optional override of values to base this event on can be given.
	 *
	 * @param (optional) _values Values used to evaluate this event.
	 * @return New events (and their priority) created by activating this event.
	 */
	std::set<std::pair<size_t, Evented<_primitive>*>> go(
		std::vector<Value<_primitive>> _values = std::vector<Value<_primitive>>()
	);
};

/*
 * A queue which contains and manages events.
 *
 * @parameter _primitive The primitive data value simulated.
 */
template <class _primitive>
class EventQueue {
public:
	/*
	 * A blank queue.
	 */
	EventQueue();

	/*
	 * Add an evented object to the queue.
	 *
	 * @param The "level" of the Evented object.
	 * @param The Evented object.
	 */
	void add(size_t _level, Evented<_primitive>* _event);

	/*
	 * Manually add a list of events to the queue.
	 *
	 * @param The events (and their level) to add to the queue.
	 */
	void add(std::set<std::pair<size_t, Evented<_primitive>*>> _add);

	/*
	 * Process all elements in the queue.
	 *
	 * If during processing an event is added which has a "level" less than or
	 * equal to the event being processed, an exception will be thrown.
	 */
	void process();

private:
	/*
	 * The event-containing data structures.
	 *
	 * Each "index" of the vector is a "priority level".
	 * Each "index entry" is a set of Events.
	 */
	std::vector<std::unordered_set<Evented<_primitive>*>> queue_;

	/*
	 * The current maximum level of the queue.
	 */
	size_t maxLevel_;
};


#endif