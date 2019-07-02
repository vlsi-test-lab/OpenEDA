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
 std::unordered_set<Fault<_primitive>*> FaultGenerator<_primitive>::allFaults(Circuit * _circuit, bool _checkpointReduce) {
	 std::unordered_set<Fault<_primitive>*> toReturn;
	 std::unordered_set<FaultyLine<_primitive>*> circuitCheckpoints; //Lines where faults are generated
	 if (_checkpointReduce == true) {
		 circuitCheckpoints = checkpoints(_circuit);
	 } else {
		 for (Levelized* node : _circuit->nodes()) {
			 for (Connecting* line : node->inputs()) {
				 FaultyLine<_primitive>* cast = dynamic_cast<FaultyLine<_primitive>*>(line);
				 circuitCheckpoints.emplace(cast);
			 }
			 for (Connecting* line : node->outputs()) {
				 FaultyLine<_primitive>* cast = dynamic_cast<FaultyLine<_primitive>*>(line);
				 circuitCheckpoints.emplace(cast);
			 }
		 }
	 }
	 for (FaultyLine<_primitive>* checkpoint : circuitCheckpoints) {
		 Fault<_primitive>* sa0 = new Fault<_primitive>(checkpoint, Value<_primitive>((_primitive)0x0000000000000000));
		 Fault<_primitive>* sa1 = new Fault<_primitive>(checkpoint, Value<_primitive>((_primitive)0xFFFFFFFFFFFFFFFF));
		 toReturn.emplace(sa0);
		 toReturn.emplace(sa1);
	 }
	 return toReturn;

 }

template<class _primitive>
std::unordered_set<FaultyLine<_primitive>*> FaultGenerator<_primitive>::checkpoints(Circuit * _circuit) {
	std::unordered_set<Connecting*> preCastToReturn;

	//Step 1: get all the PI lines and fanout lines.
	std::unordered_map<Connecting*, bool> visited; //Mapps lines to visited. This allows lines to not have the "Tracable" attribute.
	for (Levelized* pi : _circuit->pis()) {
		if (pi->outputs().size() != 1) {
			throw "Problem: a PI in the circuit does not have an output line.";
		}
		Connecting* piLine = *(pi->outputs().begin());
		preCastToReturn.emplace(piLine);
		std::unordered_set<Connecting*> toAdd = fanouts(piLine, visited);
		preCastToReturn.insert(toAdd.begin(), toAdd.end());
	}

	//Step 2: cast all objects to FaultyLines.
	std::unordered_set<FaultyLine<_primitive>*> toReturn;
	for (Connecting* line : preCastToReturn) {
		FaultyLine<_primitive>* cast = dynamic_cast<FaultyLine<_primitive>*>(line);
		if (cast == nullptr) {
			throw "A fanout/PI object in the circuit is not a FaultyLine.";
		}
		toReturn.emplace(cast);
	}

	return toReturn;
}

template<class _primitive>
std::unordered_set<Connecting*> FaultGenerator<_primitive>::fanouts(Connecting * _base, std::unordered_map<Connecting*, bool> & _visited) {
	//Case 0: we've been here before.
	if (_visited.find(_base) != _visited.end()) {
		return std::unordered_set<Connecting*>();
	}
	_visited[_base] = true;

	//Case 1: we reached the end.
	if (_base->outputs().size() == 0) {
		return std::unordered_set<Connecting*>();
	}

	//Case 2: we have a single output
	if (_base->outputs().size() == 1) {
		return fanouts(*(_base->outputs().begin()), _visited);
	}

	//Case 3: we have multiple outputs (and hence outputs)
	std::unordered_set<Connecting*> toReturn = _base->outputs();
	for (Connecting* output : _base->outputs()) {
		std::unordered_set<Connecting*> toAdd = fanouts(output, _visited);
		toReturn.insert(toAdd.begin(), toAdd.end());
	}
	return toReturn;
}

template class FaultGenerator<bool>;
template class FaultGenerator<unsigned long long int>;