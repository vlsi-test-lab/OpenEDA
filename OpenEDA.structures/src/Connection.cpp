#pragma once

/**
 * @file Connection.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2018-12-21
 *
 * @copyright Copyright (c) 2018
 */

#include "Connection.h"

Connection::Connection() {
  throw "Invalid Connection. Must have a valid input and output.";
}

Connection::Connection(Connecting * _input, Connecting * _output) {
  if (_input == nullptr || _output == nullptr) { throw "Invalid Connection. Must have a valid input and output."; }
  input_ = _input;
  output_ = _output;
  input_->addOutput(this);
  output_->addInput(this);
}

Connection::~Connection() { 
	input_->removeOutput(this); 
	output_->removeInput(this);
}

Connecting* Connection::input() const { return this->input_; }

Connecting* Connection::output() const { return this->output_; }

Connecting::Connecting() {
	this->name_ = "";
}

Connecting::Connecting(std::unordered_set<Connecting*> _inputs,
                       std::unordered_set<Connecting*> _outputs,
					   std::string _name) {
  for (Connecting* input : _inputs){
    new Connection(input, this); //TODO See next comment.
  }
  for (Connecting* output : _outputs){
    new Connection(this, output); //TODO Can a object currently under construction be modified by another object? If not, then this statement is most likely not valid.
	//change the position of "output" and "this"
  }
  this->name_ = _name;
}

Connecting::~Connecting() { 
	//A copy of inputs/outputs must be created before deleting, since deleting will change the list.
	std::unordered_set<Connection*> inputs = this->inputs_;
	std::unordered_set<Connection*> outputs = this->outputs_;
	for (Connection* input : inputs){
		delete input;
	}
	for (Connection* output : outputs) {
		delete output;
	}
}

std::unordered_set<Connecting*> Connecting::inputs() const {
	std::unordered_set < Connecting* > ret;
	for (Connection* input : this->inputs_) {
		ret.emplace(input->input());
	}
	return ret;
}

std::unordered_set<Connecting*> Connecting::inputs(std::unordered_set<Connecting*> _inputs) {
	std::unordered_set<Connection*> inputsCopy = this->inputs_;
	for (Connection* input : inputsCopy) {
		delete input;
	}
	for (Connecting* input : _inputs) {
		this->addInput(input);
	}
	return _inputs;
}

std::unordered_set<Connecting*> Connecting::outputs() const {
	std::unordered_set < Connecting* > ret;
	for (Connection* output : this->outputs_) {
		ret.emplace(output->output());
	}
	return ret;
}

std::unordered_set<Connecting*> Connecting::outputs(std::unordered_set<Connecting*> _outputs) {
	std::unordered_set<Connection*> outputsCopy = this->outputs_;
	for (Connection* output : outputsCopy) {
		delete output;
	}
	for (Connecting* output : _outputs) {
		this->addOutput(output);
	}
	return _outputs;
}

void Connecting::removeInput(Connecting * _rmv) {
	for (Connection* input : this->inputs_) {
		if (input->input() == _rmv) {
			delete input;
			return;
		}
	}
	throw "Input connection cannot be removed: it does not exist.";
}

void Connecting::removeOutput(Connecting * _rmv) {
	for (Connection* output : this->outputs_) {
		if (output->output() == _rmv) {
			delete output;
			return;
		}
	}
	throw "Output connection cannot be removed: it does not exist.";
}

void Connecting::addInput(Connecting * _add) {
	new Connection(_add, this);
}

void Connecting::addOutput(Connecting * _add) {
	new Connection(this, _add);
}

std::string Connecting::name() const {
	return this->name_;
}

void Connecting::removeInput(Connection * _rmv) {
	if (this->inputs_.find(_rmv) == this->inputs_.end()) {
		throw "Cannot remove connection which does not exist";
	}
	this->inputs_.erase(_rmv);
}

void Connecting::removeOutput(Connection * _rmv) {
	if (this->outputs_.find(_rmv) == this->outputs_.end()) {
		throw "Cannot remove connection which does not exist";
	}
	this->outputs_.erase(_rmv);
}

void Connecting::addInput(Connection * _add) {
	this->inputs_.emplace(_add);
}

void Connecting::addOutput(Connection * _add) {
	this->outputs_.emplace(_add);
}
