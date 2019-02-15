/**
 * @file FaultGenerator.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-23
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "FaultGenerator.h"

	 template<class _primitive>
 std::set<Fault<_primitive>> FaultGenerator<_primitive>::allFaults(Circuit * _circuit) {
	 std::set<Fault<_primitive>> toReturn;
	 for (Levelized* node : _circuit->nodes()) {
		 SimulationNode<_primitive>* cast = dynamic_cast<SimulationNode<_primitive>*>(node);
		 std::set<Fault<_primitive>> toAdd = allFaults(cast);
		 toReturn.insert(toAdd.begin(), toAdd.end());
	 }
	 return toReturn;
 }

 template<class _primitive>
std::set<Fault<_primitive>> FaultGenerator<_primitive>::allFaults(SimulationNode<_primitive>* _node) {
	//Is this an XOR gate?
	std::set<Fault<_primitive>> toReturn;
	BooleanFunction* func = dynamic_cast<BooleanFunction*>( _node->function() );
	if (func->string() == "xor" || func->string() == "xnor") {//yes: generate faults on each input and output.
		for (Connecting* input : _node->inputs()) {
			FaultyLine<_primitive>* line = dynamic_cast<FaultyLine<_primitive>*>(input);
			toReturn.emplace(Fault<_primitive>(line, Value<_primitive>(0)));
			toReturn.emplace(Fault<_primitive>(line, Value<_primitive>(1)));
		}
		FaultyLine<_primitive>* line = dynamic_cast<FaultyLine<_primitive>*>(*(_node->outputs().begin()));
		toReturn.emplace(Fault<_primitive>(line, Value<_primitive>(0)));
		toReturn.emplace(Fault<_primitive>(line, Value<_primitive>(1)));
		return toReturn;
	}

	//no
	for (Connecting* input : _node->inputs()) {
		FaultyLine<_primitive>* line = dynamic_cast<FaultyLine<_primitive>*>(input);
		std::set<Fault<_primitive>> toAdd = this->allFaults(line);
		toReturn.insert(toAdd.begin(), toAdd.end());
	}
	for (Connecting* output : _node->inputs()) {
		FaultyLine<_primitive>* line = dynamic_cast<FaultyLine<_primitive>*>(output);
		std::set<Fault<_primitive>> toAdd = this->allFaults(line);
		toReturn.insert(toAdd.begin(), toAdd.end());
	}
	return std::set<Fault<_primitive>>();
}

template<class _primitive>
std::set<Fault<_primitive>> FaultGenerator<_primitive>::allFaults(FaultyLine<_primitive>* _line) {
	std::set<Fault<_primitive>> toReturn;
	Connecting* input = *(_line->inputs().begin());
	//Is it a pi / constant (no driver)?
	if (input->inputs().size() == 0) { //yes
		toReturn.emplace(Fault<_primitive>(_line, Value<_primitive>(0)));
		toReturn.emplace(Fault<_primitive>(_line, Value<_primitive>(1)));
		return toReturn;
	} //no

	//Is this a fan-out?
	if (input->outputs().size() > 1) { //yes
		toReturn.emplace(Fault<_primitive>(_line, Value<_primitive>(0)));
		toReturn.emplace(Fault<_primitive>(_line, Value<_primitive>(1)));
		return toReturn;
	}

	return toReturn; //no faults.
}

template class FaultGenerator<bool>;