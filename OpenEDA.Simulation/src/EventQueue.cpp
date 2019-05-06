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

	 template<class _primitive>
 Evented<_primitive>::Evented(
	 std::unordered_set<Evented<_primitive>*> _inputs, 
	 std::unordered_set<Evented<_primitive>*> _outputs, 
	 std::string _name) :
	 Levelized(
		 std::unordered_set<Levelized*>(_inputs.begin(), _inputs.end()),
		 std::unordered_set<Levelized*>(_outputs.begin(), _outputs.end()),
		 _name
	 )
 {
 }

 template<class _primitive>
std::set<std::pair<size_t, Evented<_primitive>*>> Evented<_primitive>::go(
	std::vector <Value<_primitive>> _values
) {
	if (_values.size() == 0) {
		for (Connecting* input : this->inputs()) {
			Evented<_primitive>* cast = dynamic_cast<Evented<_primitive>*>(input);
			_values.push_back(
				cast->value()
			);
		}
	}
	std::unordered_set<Connecting*> temp_inps = this->inputs();
	//SimulationLine<_primitive>* outputLine = dynamic_cast<SimulationLine<_primitive>*>(*(this->Levelized::outputs().begin())); //NOTE: do I NEED the "Levelized"?
	Value<_primitive> oldValue = this->value();
	Value<_primitive> newValue = this->value(_values);

	std::set<std::pair<size_t, Evented<_primitive>*>> toReturn;
	if (oldValue != newValue) { //Value changed, so change line values and update the queue.
		for (Connecting* output : this->outputs()) {
			Evented<_primitive>* cast = dynamic_cast<Evented<_primitive>*>(output);
			size_t eventLevel = cast->inputLevel();
			toReturn.emplace(
				std::pair<size_t, Evented<_primitive>*>(
					eventLevel, cast
					)
			);
		}
	}
	return toReturn; //May be empty if nothing is added.
}

template <class _primitive>
EventQueue<_primitive>::EventQueue() {
	maxLevel_ = 0;
}

template <class _primitive>
void EventQueue<_primitive>::add(size_t _level, Evented<_primitive> * _event) {
	if (_level > maxLevel_ || queue_.empty() == true) {
		size_t currentM = this->queue_.size();
		for (size_t i = currentM; i < _level; i++)
		{
			this->queue_.push_back(std::unordered_set<Evented<_primitive>*>());
		}
		std::unordered_set<Evented<_primitive>*> soham_event =  std::unordered_set<Evented<_primitive>*>({ _event });
		this->queue_.push_back(soham_event);
		this->maxLevel_ = _level;
	} else {
		this->queue_.at(_level).emplace(_event);
	}
}

template<class _primitive>
void EventQueue<_primitive>::add(std::set<std::pair<size_t, Evented<_primitive>*>> _add) {
	for (std::pair<size_t, Evented<_primitive>*> newEvent : _add) {
		this->add(newEvent.first, newEvent.second);
	}
}

template <class _primitive>
void EventQueue<_primitive>::process() {
	for (size_t currentLevel = 0; currentLevel <= maxLevel_; currentLevel++) {
		std::unordered_set<Evented<_primitive>*> events = this->queue_.at(currentLevel);
		for (Evented<_primitive>* currentEvent : events) {
			std::set<std::pair<size_t, Evented<_primitive>*>> newEvents = currentEvent->go();
			for (std::pair<size_t, Evented<_primitive>*> toAdd : newEvents) {
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

template class Evented<bool>;
template class EventQueue<bool>;