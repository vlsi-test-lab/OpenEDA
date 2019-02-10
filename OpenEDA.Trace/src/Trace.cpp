/*
 * @file Trace.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-09
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "Trace.h"

template <class _primitive>
std::unordered_set<TraceNode<_primitive>*> Trace<_primitive>::pis(Circuit * _circuit, TraceNode<_primitive> * _node, std::unordered_set<TraceNode<_primitive>*>& _flagged) {
	bool top = (_flagged.size() == 0); //Is this the top-level (true == top level)

	std::unordered_set<TraceNode<_primitive>*> toReturn;

	if (_node->flag(true) == true) { //This has already been flagged, so no need to go any further or return anything.
		return toReturn; //To return is empty, so this will return nothing.
	}
	_flagged.emplace(this);

	if (_node->function()->string() == "pi") {
		toReturn.emplace(this);
		return toReturn;
	}

	for (Connecting* input : _node->inputs()) {
		Line* inputLine = static_cast<Line*>(input);
		std::unordered_set<TraceNode<_primitive>*> toAdd = Trace::pis(_circuit, inputLine, _flagged);
		toReturn.insert(toAdd.begin(), toAdd.end());
	}

	if (top == true) { //This is top-level, so clear all flags before returning.
		for (TraceNode<_primitive>* node : _flagged) {
			node->flag(false);
		}
	}
	
	return toReturn;

}

template <class _primitive>
std::unordered_set<TraceNode<_primitive>*> Trace<_primitive>::pis(Circuit * _circuit, Line * _line, std::unordered_set<TraceNode<_primitive>*>& _flagged) {
	bool top = (_flagged.size() == 0); //Is this the top-level (true == top level)
	if ((_line->isOutputNode() == true) && (top == true)) { //We add this Line's output onto the _flagged structure to keep track of who is "top".
		Connecting* output = *(_line->outputs().begin());
		_flagged.emplace(dynamic_cast<TraceNode<_primitive>*>(output));
	}

	if (_line->isInputNode() == true) { //Input is a node, so return the driving Node's call for PIs.
		Connecting* input = *(_line->inputs().begin());
		TraceNode<_primitive>* node = dynamic_cast<TraceNode<_primitive>*>(input);
		return Trace::pis(_circuit, node, _flagged);
	}

	//Else (see previous "if"), find PIs of each driving Node (i.e., each Node driving each driving Line).
	std::unordered_set<TraceNode<_primitive>*> toReturn;
	for (Connecting* input : _line->inputs()) {
		Line* inputLine = static_cast<Line*>(input);
		std::unordered_set<TraceNode<_primitive>*> toAdd = Trace::pis(_circuit, inputLine, _flagged);
		toReturn.insert(toAdd.begin(), toAdd.end());
	}

	if (top == true) { //This is top-level, so clear all flags before returning.
		for (TraceNode<_primitive>* node : _flagged) {
			node->flag(false);
		}
	}

	return toReturn;
}

template <class _primitive>
std::unordered_set<TraceNode<_primitive>*> Trace<_primitive>::pis(Circuit * _circuit, std::unordered_set<Line*> _lines, std::unordered_set<TraceNode<_primitive>*>& _flagged) {
	std::unordered_set<TraceNode<_primitive>*> toReturn;
	if (_lines.size() == 0) {
		return toReturn;
	}

	//To prevent the premature clearing of the _flagged structure, a fake Node
	//will be created and made "top". It will be deleted at the end of this
	//function.
	TraceNode<_primitive>* fakeNode = new TraceNode<_primitive>();
	_flagged.emplace(fakeNode);

	for (Line* line : _lines) {
		std::unordered_set<TraceNode<_primitive>*> toAdd = Trace::pis(_circuit, line, _flagged);
		toReturn.insert(toAdd.begin(), toAdd.end());
	}

	for (TraceNode<_primitive>* node : _flagged) {
		node->flag(false);
	}

	delete fakeNode;
	return toReturn;
}

