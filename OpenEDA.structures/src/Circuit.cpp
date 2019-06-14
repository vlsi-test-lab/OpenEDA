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

#include <map>

 //On a given clonable, levelized object, go both forward and backwards to 
 //create and connect objects until the given stopping points are reached.
 //
 //@returns A new object which is created or a nullptr.
Connecting* spread(
	Connecting* point,
	std::map<Connecting*, Connecting*> & oldToNew,
	std::map<Connecting*, Connecting*> & newToOld,
	bool forwards = true,
	bool backwards = true
) {
	//If we already have seen the point, don't go any further.
	if (
		(forwards == true && backwards == true) &&
		oldToNew.find(point) != oldToNew.end()
		) {
		return nullptr;
	}

	Connecting* newPoint = point;
	if (forwards == true && backwards == true) {
		newPoint = point->clone();
		newToOld[newPoint] = point;
		oldToNew[point] = newPoint;
	}

	//For each input, attempt to spread and connect.
	if (backwards == true) {
		for (Connecting* input : point->inputs()) {
			Connecting* newInputConnection = spread(input, oldToNew, newToOld);
			if (newInputConnection != nullptr) {
				newPoint->addInput(newInputConnection);
				//newPoint->removeInput(newToOld.find(newInputConnection)->second);
			}
		}
	}

	//For each output, attempt to spread and connect.
	if (forwards == true) {
		for (Connecting* output : point->outputs()) {
			Connecting* newOutputConnection = spread(output, oldToNew, newToOld);
			if (newOutputConnection != nullptr) {
				newPoint->addOutput(newOutputConnection);
				//newPoint->removeOutput(newToOld.find(newOutputConnection)->second);
			}
		}
	}

	return newPoint;
}

void Circuit::copy(std::unordered_set<Levelized*> _nodes, std::unordered_set<Levelized*> _pis, std::unordered_set<Levelized*> _pos) {
	std::map<Connecting*, Connecting*> oldToNew;
	std::map<Connecting*, Connecting*> newToOld;

	//First, set all PIs and POs of the circuit.
	for (Levelized* pi : _pis) {
		Levelized* newNode = pi->clone();
		//Not needed //this->addNode(newNode);
		this->addPI(newNode);
		newToOld[newNode] = pi;
		oldToNew[pi] = newNode;
	}
	for (Levelized* po : _pos) {
		Levelized* newNode = po->clone();
		//Not needed //this->addNode(newNode);
		this->addPO(newNode);
		newToOld[newNode] = po;
		oldToNew[po] = newNode;
	}

	//Spread to populate the circuit.
	for (Levelized* pi : _pis) {
		spread(pi, oldToNew, newToOld, true, false);
	}
	for (Levelized* po : _pos) {
		spread(po, oldToNew, newToOld, false, true);
	}


	//Go through old nodes to make this circuit's new nodes.
	for (Levelized* oldNode : _nodes) {
		Levelized* newNode = dynamic_cast<Levelized*>(oldToNew.at(oldNode));
		this->addNode(newNode);
	}


	//Go through old objects to make this circuit's new connections.
	for (auto objs : oldToNew) {
		Connecting* oldObj = objs.first;
		Connecting* newObj = objs.second;
		std::unordered_set<Connecting*> oldInputs = oldObj->inputs();
		std::unordered_set<Connecting*> oldOutputs = oldObj->outputs();
		std::unordered_set<Connecting*> newInputs;
		std::unordered_set<Connecting*> newOutputs;
		for (Connecting* oldInput : oldInputs) {
			Connecting* newInput = oldToNew.at(oldInput);
			newInputs.emplace(newInput);
		}
		for (Connecting* oldOutput : oldOutputs) {
			Connecting* newOutput= oldToNew.at(oldOutput);
			newOutputs.emplace(newOutput);
		}
		newObj->inputs(newInputs);
		newObj->outputs(newOutputs);
	}

}

Circuit::Circuit(
	std::unordered_set<Levelized*> _nodes,
	std::unordered_set<Levelized*> _inputs,
	std::unordered_set<Levelized*> _outputs,
	bool _copy
) {
	if (_copy == false) {
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
	} else {
		this->copy(_nodes, _inputs, _outputs);
	}
}



Circuit::Circuit(const Circuit& _circuit) {
	this->copy(
		_circuit.nodes(),
		_circuit.pis(),
		_circuit.pos()
	);
}

void spread(
	Levelized* point,
	std::unordered_set<Levelized*> & allCircuitObjects
) {
	if (allCircuitObjects.find(point) != allCircuitObjects.end()) {
		return;
	}
	allCircuitObjects.emplace(point);

	for (Connecting* input : point->inputs()) {
		Levelized* cast = dynamic_cast<Levelized*>(input);
		spread(cast, allCircuitObjects);
	}
	for (Connecting* output : point->outputs()) {
		Levelized* cast = dynamic_cast<Levelized*>(output);
		spread(cast, allCircuitObjects);
	}
}

Circuit::~Circuit() {
	std::unordered_set<Levelized*> allCircuitObjects;
	for (Levelized* node : this->nodes_) {
		spread(node, allCircuitObjects);
	}
	for (Levelized* object : allCircuitObjects) {
		delete object;
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
	//DELETE: obsolete
	//auto iterator = this->nodes_.find(_node);
	//if (iterator == this->nodes_.end()) {
	//	throw "Cannot remove node, it does not exist in the circuit.";
	//}
	//this->nodes_.erase(iterator);
	
	bool found = this->nodes_.erase(_node);
	if (found == false) {
		throw "Could not remove node from circuit: it's not part of the circuit.";
	}
	this->pis_.erase(_node);
	this->pos_.erase(_node);
	
	return _node;
}

void Circuit::addPI(Levelized* _pi) {
	this->nodes_.emplace(_pi);
	this->pis_.emplace(_pi);
	_pi->inputLevelZero();
}

//DELETE: obsolete
//Levelized* Circuit::removePI(Levelized* _pi) {
//	auto iterator = this->nodes_.find(_pi);
//	if (iterator == this->nodes_.end()) {
//		throw "Cannot remove PI, it does not exist in the circuit.";
//	}
//	iterator = this->pis_.find(_pi);
//	if (iterator == this->pis_.end()) {
//		throw "Cannot remove PI, it is not a PI.";
//	}
//	this->pis_.erase(iterator);	
//	return _pi;
//}

void Circuit::addPO(Levelized* _po) {
	this->nodes_.emplace(_po);
	this->pos_.emplace(_po);
	_po->outputLevelZero();
}



//DELETE: obsolete
//Levelized* Circuit::removePO(Levelized* _po) {
//	auto iterator = this->nodes_.find(_po);
//	if (iterator == this->nodes_.end()) {
//		throw "Cannot remove PO, it does not exist in the circuit.";
//	}
//	iterator = this->pos_.find(_po);
//	if (iterator == this->pos_.end()) {
//		throw "Cannot remove PO, it is not a PO.";
//	}
//	this->pos_.erase(iterator);
//	return _po;
//}