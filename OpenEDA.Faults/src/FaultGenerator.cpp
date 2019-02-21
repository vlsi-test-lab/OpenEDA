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
	std::set<Fault<_primitive>> toReturn;
	Function<_primitive>* func = _node->function();
	std::string name = func->string();

	//SA0 on inputs?
	if (
		name == "xor" || 
		name == "xnor" ||
		name == "or" ||
		name == "nor" ||
		name == "not" ||
		name == "buf" ||
		name == "buff" ||
		name == "po"
		) {//yes: generate faults on each input and output.
		for (Connecting* input : _node->inputs()) {
			FaultyLine<_primitive>* line = dynamic_cast<FaultyLine<_primitive>*>(input);
			toReturn.emplace(Fault<_primitive>(line, Value<_primitive>(0)));
		}
	}

	//SA1 on inputs?
	if (
		name == "xor" ||
		name == "xnor" ||
		name == "and" ||
		name == "nand" ||
		name == "po" 
		) {//yes: generate faults on each input and output.
		for (Connecting* input : _node->inputs()) {
			FaultyLine<_primitive>* line = dynamic_cast<FaultyLine<_primitive>*>(input);
			toReturn.emplace(Fault<_primitive>(line, Value<_primitive>(1)));
		}
	}

	//SA0 on output?
	if (
		name == "xor" ||
		name == "xnor" ||
		name == "and" ||
		name == "nor" ||
		name == "not" ||
		name == "pi"
		) {//yes: generate faults on each input and output.
		for (Connecting* output : _node->outputs()) {
			FaultyLine<_primitive>* line = dynamic_cast<FaultyLine<_primitive>*>(output);
			toReturn.emplace(Fault<_primitive>(line, Value<_primitive>(0)));
		}
	}

	//SA1 on output?
	if (
		name == "xor" ||
		name == "xnor" ||
		name == "nand" ||
		name == "or" ||
		name == "buf" ||
		name == "buff" ||
		name == "pi"
		) {//yes: generate faults on each input and output.
		for (Connecting* output : _node->outputs()) {
			FaultyLine<_primitive>* line = dynamic_cast<FaultyLine<_primitive>*>(output);
			Fault<_primitive> fault = Fault<_primitive>(line, Value<_primitive>(1));
			toReturn.emplace(fault);
		}
	}

	return toReturn;
}

template class FaultGenerator<bool>;