/**
 * @file Simulator.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2018-12-27
 *
 * @copyright Copyright (c) 2018
 *
 */

#include <set>
#include <utility> //std::pair

#include "Simulator.h"
#include "EventQueue.h"


template<class T>
std::vector<Value<T>> Simulator<T>::applyStimulus(
	Circuit * _circuit,
	std::vector<Value<T>> _stimulus,
	EventQueue<T> _simulationQueue,
	std::vector<SimulationNode<T>*> _inputs,
	std::vector<SimulationNode<T>*> _outputs,
	std::vector<bool> _observe
) {
	if (_circuit == nullptr) { throw "No circuit given to apply stimulus to."; }
	if (_inputs.size() == 0) {//DEL Cannot convert directly from Node* to SimulationNode<T>* _inputs = std::vector<SimulationNode<T>*>(_circuit->pis().begin(), _circuit->pis().end());
		for (Levelized* input : _circuit->pis()) {
			SimulationNode<T>* cast = dynamic_cast<SimulationNode<T>*>(input); //NOTE: Can this be done wtihout a dynamic_cast? It may require changing the pointer type to be more "strict" or removing virtual inheritence, which in turn may require re-organizing code.
			_inputs.push_back(cast);
		}
	}
	if (_stimulus.size() != _inputs.size()) { 
		throw "When applying stimulus, stimulus and inputs do not match in size."; 
	}

	//Initialize the queue.
	for (size_t i = 0; i < _stimulus.size(); ++i) {
		Value<T> value = _stimulus.at(i);
		std::set<std::pair<size_t, Evented<T>*>> events = _inputs.at(i)->go(
			std::vector<Value<T>>(1, value)
		);
		_simulationQueue.add(events);
	}

	_simulationQueue.process();

	return this->outputs(_circuit, _outputs, _observe);
}


template<class T>
std::vector<Value<T>> Simulator<T>::outputs(
	Circuit * _circuit,
	std::vector<SimulationNode<T>*> & _outputs,
	std::vector<bool> & _observe
) {
	if (_outputs.empty() == true) {
		for (Levelized* output : _circuit->pos()) {
			_outputs.push_back(dynamic_cast<SimulationNode<T>*>(output));
		}
		//DELETE: doesn't work, won't compile. _outputs = std::vector<SimulationNode<T>*>(_circuit->pos().begin(), _circuit->pos().end());
	}
	if (_observe.empty() == true) {
		_observe = std::vector<bool>(_outputs.size(), true);
	} else if(_observe.size() != _outputs.size()) {
		throw "_outputs/_observe size mismach while measuring simulation outputs.";
	}

	std::vector<Value<T>> toReturn;
	for (size_t i = 0; i < _outputs.size(); i++) {
		if (_observe.at(i) == false) {
			continue;
		}
		SimulationNode<T>* output = _outputs.at(i);
		std::unordered_set<Connecting*> lines = output->inputs();
		SimulationLine<T>* outputLine = dynamic_cast<SimulationLine<T>*>(*(lines.begin()));
		toReturn.push_back(outputLine->value());
	}
	return toReturn;
}



template class Simulator<bool>;