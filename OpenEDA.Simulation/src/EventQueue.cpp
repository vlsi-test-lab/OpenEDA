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

 /*
  * One value may have changed to another (for simulation purposes) if
  * 1) One is valid and the other is not, or
  * 2) Both are valid and their magnitude is different.
  */
 template<class _primitive>
 bool changed(Value<_primitive> _a, Value<_primitive> _b) {
	 if (_a.valid() == false && _b.valid() == false) {
		 return false;
	 }
	 if (_a.valid() != _b.valid()) {
		 return true;
	 }
	 if (_a.magnitude() != _b.magnitude()) {
		 return true;
	 }
	 return false;
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
	//DEBUG

	Value<_primitive> oldValue = this->value();
	Value<_primitive> newValue = this->value(_values);

	std::set<std::pair<size_t, Evented<_primitive>*>> toReturn;
	if (changed(oldValue, newValue) == true) { //Value changed, so change line values and update the queue.
//DEBUG		printf("C\t%s\t%d->%d\t%d->%d\n", this->name().c_str(), oldValue.valid(), newValue.valid(), oldValue.magnitude(), newValue.magnitude()); //DEBUG
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
	//DEBUG
	//} else {
	//	printf("NC\t%s\t%d->%d\t%d->%d\n", this->name().c_str(), oldValue.valid(), newValue.valid(), oldValue.magnitude(), newValue.magnitude()); //DEBUG
	//}
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
			this->queue_.push_back(std::vector<Evented<_primitive>*>());
		}
		std::vector<Evented<_primitive>*> soham_event =  std::vector<Evented<_primitive>*>({ _event });
		this->queue_.push_back(soham_event);
		this->maxLevel_ = _level;
	} else {
		this->queue_.at(_level).push_back(_event);
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
	if (this->queue_.size() == 0) {//The loop below does not handle "empty queue" gracefully.
		return;
	}
	
	for (size_t currentLevel = 0; currentLevel <= maxLevel_; currentLevel++) {
		std::vector<Evented<_primitive>*> events = this->queue_.at(currentLevel);
		//for (Evented<_primitive>* currentEvent : events) {
		#pragma omp parallel for
		for (int eventNum = 0; eventNum < events.size(); eventNum++) {
			Evented<_primitive>* currentEvent = events.at(eventNum);
			std::set<std::pair<size_t, Evented<_primitive>*>> newEvents = currentEvent->go();
			for (std::pair<size_t, Evented<_primitive>*> toAdd : newEvents) {
				if (toAdd.first <= currentLevel) {
					throw "EventQueue can only add events during processing 'in order'.";
				}
				#pragma omp critical 
				this->add(toAdd.first, toAdd.second);
			}
		}
	}
	this->queue_.clear();
	this->maxLevel_ = 0;
}

template class Evented<bool>;
template class EventQueue<bool>;