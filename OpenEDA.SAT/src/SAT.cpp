/**
 * @file SAT.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-15
 *
 * @copyright Copyright (c) 2019
 *
 */

#include <ctime>

#include "Simulator.h"
#include "SAT.h"
#include "Trace.h"
#include "Value.h"
#include "ValueVectorFunctions.hpp"

//TODO: "active" should be the one which sets values to "default"
template<class _primitive>
void RestrictedSimulator<_primitive>::setActiveSimulationNodes(std::unordered_set<SatisfiableNode<_primitive>*> _nodes)
{
	for (SimulationNode<_primitive>* node : _nodes) {
		TraceNode<_primitive>* cast = dynamic_cast<TraceNode<_primitive>*>(node);
		cast->flag(false);
	}
}

template<class _primitive>
void RestrictedSimulator<_primitive>::unssetActiveSimulationNodes(std::unordered_set<SatisfiableNode<_primitive>*> _nodes) {
	for (SatisfiableNode<_primitive>* node : _nodes) {
		SimulationLine<_primitive>* output = dynamic_cast<SimulationLine<_primitive>*>(*(node->Node::outputs().begin()));
		output->value(Value<_primitive>());
		TraceNode<_primitive>* cast = dynamic_cast<TraceNode<_primitive>*>(node);
		cast->flag(true);
	}
}

template class RestrictedSimulator<bool>;

/*
 * Return all the values currently on the output of given Nodes.
 */
template<class T>
std::vector<Value<T>> nodesToValues(std::unordered_set<SatisfiableNode<T>*> _nodes) {
	std::vector<Value<T>> toReturn;
	for (SimulationNode<T>* node : _nodes) {
		SimulationLine<T>* output = dynamic_cast<SimulationLine<T>*>(*(node->Node::outputs().begin()));
		toReturn.push_back(output->value());
	}
	return toReturn;
}

template<class _primitive>
SAT<_primitive>::SAT(int _limit) {
	this->limit_ = _limit * CLOCKS_PER_SEC;
}

template<class _primitive>
Combination<_primitive> SAT<_primitive>::satisfy(Circuit * _circuit, Combination<_primitive>* _combination) {
	this->prepare(_circuit);
	std::unordered_set<SatisfiableNode<_primitive>*> pis;
	std::unordered_set<SatisfiableNode<_primitive>*> coi;
	Combination<_primitive> toReturn = this->satisfy(_circuit, _combination, pis, coi);
	this->release(_circuit);
	return toReturn;
}

/*
 * Convert a set of tracable nodes to satisfiabile nodes.
 */
template<class T>
std::unordered_set<SatisfiableNode<T>*> convert(std::unordered_set<TraceNode<T>*> _nodes) {
	std::unordered_set<SatisfiableNode<T>*> toReturn;
	for (TraceNode<T>* node : _nodes) {
		toReturn.emplace(dynamic_cast<SatisfiableNode<T>*>(node));
	}
	return toReturn;
}

template<class _primitive>
std::unordered_set<Combination<_primitive>*> SAT<_primitive>::satisfy(
	Circuit * _circuit, 
	std::unordered_set<Combination<_primitive>*> _combinations, 
	std::unordered_set<SatisfiableNode<_primitive>*> _pis, 
	std::unordered_set<SatisfiableNode<_primitive>*> _coi) 
{
	std::unordered_set<Combination<_primitive>*> toReturn;
	for (Combination<_primitive>* combination : _combinations) {
		if ((this->satisfy(_circuit, combination, _pis, _coi)).lines().size() > 0) {
			toReturn.emplace(combination);
		}
	}
	return toReturn;
}

template<class _primitive>
Combination<_primitive> SAT<_primitive>::satisfy(Circuit* _circuit,
												 Combination<_primitive>* _combination,
												 std::unordered_set<SatisfiableNode<_primitive>*>& _pis,
												 std::unordered_set<SatisfiableNode<_primitive>*>& _coi)
{
	if (_pis.empty() || _coi.empty()) {
		std::unordered_set<Line*> lines(_combination->lines().begin(), _combination->lines().end());
		std::unordered_set<TraceNode<_primitive>*> coi;
		std::unordered_set<TraceNode<_primitive>*> pis = Trace<_primitive>::pis(_circuit, lines, coi);
		_pis = convert<_primitive>(pis);// std::unordered_set<SatisfiableNode<_primitive>*>(pis.begin(), pis.end());
		_coi = convert<_primitive>(coi);//std::unordered_set<SatisfiableNode<_primitive>*>(coi.begin(), coi.end());
	}
	std::vector<Value<_primitive>> currentPiValues = std::vector<Value<_primitive>>(_pis.size(), Value<_primitive>());
	std::clock_t startTime = std::clock();
	for (SatisfiableNode<_primitive>* node : _coi) { node->flag(true); } //For simulation COI //simulator_.setActiveSimulationNodes(_coi);
	
	std::vector<SimulationNode<_primitive>*> simulationPis(_pis.begin(), _pis.end());
	while (this->timeLeft(startTime) == true) {
		simulator_.applyStimulus(_circuit, currentPiValues, EventQueue(), simulationPis);
		if (_combination->seen() == true) {
			simulator_.unssetActiveSimulationNodes(_coi); //for (SatisfiableNode<_primitive>* node : _coi) {node->flag(false); } //
			std::unordered_set<SimulationLine<_primitive>*> lines;
			for (SatisfiableNode<_primitive>* pi : _pis) {
				lines.emplace(dynamic_cast<SimulationLine<_primitive>*>(*(pi->Node::outputs().begin())));
			}
			return Combination<_primitive>(lines, nodesToValues(_pis), true) ;
		}
		std::vector<Value<_primitive>> currentCombinationValues = _combination->currentValues();
		if (ValueVectorFunction<_primitive>::mismatch(currentCombinationValues, _combination->targetValues())) {
			if (ValueVectorFunction<_primitive>::backtrack(currentPiValues) == false) {
				//End-of-the-line: no backtracking possible.
				simulator_.unssetActiveSimulationNodes(_coi);//for (SatisfiableNode<_primitive>* node : _coi) { node->flag(false); } 
				return Combination<_primitive>();
			}
		} else {
			if (ValueVectorFunction<_primitive>::forwardtrack(currentPiValues) == false) {
				throw "Forward track error! This should never happen. Ever. Period. Something is seriously wrong with SAT.";
				simulator_.unssetActiveSimulationNodes(_coi);//for (SatisfiableNode<_primitive>* node : _coi) { node->flag(false); } 
				return Combination<_primitive>();
			}
		}
	}
	simulator_.unssetActiveSimulationNodes(_coi);//for (SatisfiableNode<_primitive>* node : _coi) { node->flag(false); } 
	return Combination<_primitive>();

}

template<class _primitive>
void SAT<_primitive>::prepare(Circuit * _circuit) {
	for (Node* node : _circuit->nodes()) {
		SatisfiableNode<_primitive>* cast = dynamic_cast<SatisfiableNode<_primitive>*>(node);
		cast->flag(true);
	}
}

template<class _primitive>
void SAT<_primitive>::release(Circuit * _circuit) {
	for (Node* node : _circuit->nodes()) {
		SatisfiableNode<_primitive>* cast = dynamic_cast<SatisfiableNode<_primitive>*>(node);
		cast->flag(false);
	}
}

template<class _primitive>
bool SAT<_primitive>::timeLeft(clock_t _time) {
	if ((clock() - _time) < this->limit_) {
		return true;
	}
	return false;
}

template class SAT<bool>;