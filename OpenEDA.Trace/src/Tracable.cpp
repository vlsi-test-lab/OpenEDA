/**
 * @file Tracable.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-08
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "Tracable.h"

Tracable::Tracable(
	std::unordered_set<Tracable*> _inputs, 
	std::unordered_set<Tracable*> _outputs,
	bool _stop, 
	std::string _name) :
	Connecting(
		std::unordered_set<Connecting*>(_inputs.begin(), _inputs.end()),
		std::unordered_set<Connecting*>(_outputs.begin(), _outputs.end()),
		_name
	)
{
	this->stop_ = _stop;
}

std::unordered_set<Tracable*> Tracable::backwards(
	std::unordered_set<Tracable*>& _flagged,
	size_t _levels) {
	std::unordered_set<Tracable*> toReturn;
	//Quick returns.
	if (_levels == 0) { //Don't go any further: depth reached.
		return toReturn;
	}

	bool top = (_flagged.size() == 0);
	if (this->flag(true) == true) { //Already visited.
		return toReturn;
	}
	_flagged.emplace(this);

	//Computation.
	for (Connecting* input : this->inputs()) {
		Tracable* cast = dynamic_cast<Tracable*>(input);
		std::unordered_set<Tracable*> toAdd = cast->backwards(_flagged, _levels - 1);
		toReturn.insert(toAdd.begin(), toAdd.end());
	}

	//Clean up an return.
	if (top == true) {
		for (Tracable* flagged : _flagged) {
			flagged->flag(false);
		}
	}
	return toReturn;
	
}
