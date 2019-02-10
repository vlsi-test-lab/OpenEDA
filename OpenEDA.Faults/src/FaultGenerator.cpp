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
std::unordered_set<Fault<_primitive>> FaultGenerator<_primitive>::allFaults(SimulationNode<_primitive>* _node) {
	//Is this an XOR gate?
	std::unordered_set<Fault<_primitive>> toReturn;
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
		std::unordered_set<Fault<_primitive>> toAdd = this->allFaults(line);
		toReturn.insert(toAdd.begin(), toAdd.end());
	}
	for (Connecting* output : _node->inputs()) {
		FaultyLine<_primitive>* line = dynamic_cast<FaultyLine<_primitive>*>(output);
		std::unordered_set<Fault<_primitive>> toAdd = this->allFaults(line);
		toReturn.insert(toAdd.begin(), toAdd.end());
	}
	return std::unordered_set<Fault<_primitive>>();
}

template<class _primitive>
std::unordered_set<Fault<_primitive>> FaultGenerator<_primitive>::allFaults(FaultyLine<_primitive>* _line) {
	std::unordered_set<Fault<_primitive>> toReturn;
	if (_line->Line::isInputNode() == true) {
		SimulationNode<_primitive>* input = dynamic_cast<SimulationNode<_primitive>*>(*(_line->Line::inputs().begin()));
		if (input->inputLevel() == 0 || _line->Line::isOutputNode() == true) {
			toReturn.emplace(Fault<_primitive>(_line, Value<_primitive>(0)));
			toReturn.emplace(Fault<_primitive>(_line, Value<_primitive>(1)));
		}
	}
	return toReturn;
}
