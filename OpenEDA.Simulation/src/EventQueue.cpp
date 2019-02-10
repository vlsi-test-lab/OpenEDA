/**
 * @file Simulator.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2018-12-27
 *
 * @copyright Copyright (c) 2018
 *
 */

#include "EventQueue.h"

EventQueue::EventQueue() {
	maxLevel_ = 0;
}

void EventQueue::add(size_t _level, Evented * _event) {
	if (_level > maxLevel_ || queue_.empty() == true) {
		this->queue_[_level] = std::unordered_set<Evented*>({ _event });
		this->maxLevel_ = _level;
	} else {
		this->queue_.at(_level).emplace(_event);
	}
}

void EventQueue::process() {
	for (size_t currentLevel = 0; currentLevel < maxLevel_; currentLevel++) {
		std::unordered_set<Evented*> events = this->queue_.at(currentLevel);
		for (Evented* currentEvent : events) {
			std::set<std::pair<size_t, Evented*>> newEvents = currentEvent->go();
			for (std::pair<size_t, Evented*> toAdd : newEvents) {
				if (toAdd.first <= currentLevel) {
					throw "EventQueue can only add events during processing 'in order'.";
				}
				this->add(toAdd.first, toAdd.second);
			}
		}
	}
	this->queue_.clear();
	this->maxLevel_ = 0;
}
