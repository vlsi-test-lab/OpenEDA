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

/*
 * An object which can be called to do an "event".
 */
class Evented {
public:
	/*
	 * Activate this evented object.
	 *
	 * @return New events (and their priority) created by activating this event.
	 */
	virtual std::set<std::pair<size_t, Evented*>> go() = 0;
};

/*
 * A queue which contains and manages events.
 */
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
	void add(size_t _level, Evented* _event);

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
	std::vector<std::unordered_set<Evented*>> queue_;

	/*
	 * The current maximum level of the queue.
	 */
	size_t maxLevel_;
};


#endif