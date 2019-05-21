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
	std::string _name) :
	Connecting(
		std::unordered_set<Connecting*>(_inputs.begin(), _inputs.end()),
		std::unordered_set<Connecting*>(_outputs.begin(), _outputs.end()),
		_name
	)
{

}


