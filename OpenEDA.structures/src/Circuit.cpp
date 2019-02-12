/**
 * @file Circuit.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2018-12-24
 *
 * @copyright Copyright (c) 2018
 *
 */

#include "Circuit.h"

Circuit::Circuit(std::unordered_set<Levelized*> _nodes, std::unordered_set<Levelized*> _inputs, std::unordered_set<Levelized*> _outputs) {
	nodes_ = _nodes;
	pis_ = _inputs;
	pos_ = _outputs;
	for (Levelized* pi : pis_) {
		pi->inputLevelZero();
		nodes_.emplace(pi);
	}
	for (Levelized* po : pos_) {
		po->outputLevelZero();
		nodes_.emplace(po);
	}
	
}

std::unordered_set<Levelized*> Circuit::nodes() const {
	return this->nodes_;
}

std::unordered_set<Levelized*> Circuit::pis() const {
	return this->pis_;
}

std::unordered_set<Levelized*> Circuit::pos() const {
	return this->pos_;
}

void Circuit::addNode(Levelized* _node) {
	this->nodes_.emplace(_node);
}

Levelized* Circuit::removeNode(Levelized* _node) {
	auto iterator = this->nodes_.find(_node);
	if (iterator == this->nodes_.end()) {
		throw "Cannot remove node, it does not exist in the circuit.";
	}
	this->nodes_.erase(iterator);
	return _node;
}

void Circuit::addPI(Levelized* _pi) {
	this->nodes_.emplace(_pi);
	this->pis_.emplace(_pi);
	_pi->inputLevelZero();
}

Levelized* Circuit::removePI(Levelized* _pi) {
	auto iterator = this->nodes_.find(_pi);
	if (iterator == this->nodes_.end()) {
		throw "Cannot remove PI, it does not exist in the circuit.";
	}
	iterator = this->pis_.find(_pi);
	if (iterator == this->pis_.end()) {
		throw "Cannot remove PI, it is not a PI.";
	}
	this->pis_.erase(iterator);	
	return _pi;
}

void Circuit::addPO(Levelized* _po) {
	this->nodes_.emplace(_po);
	this->pos_.emplace(_po);
	_po->outputLevelZero();
}

Levelized* Circuit::removePO(Levelized* _po) {
	auto iterator = this->nodes_.find(_po);
	if (iterator == this->nodes_.end()) {
		throw "Cannot remove PO, it does not exist in the circuit.";
	}
	iterator = this->pos_.find(_po);
	if (iterator == this->pos_.end()) {
		throw "Cannot remove PO, it is not a PO.";
	}
	this->pos_.erase(iterator);
	return _po;
}