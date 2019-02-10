#include "Line.h"



Line::Line(Node * _inNode, Node * _outNode, Line * _inLine, std::unordered_set<Line*> _outLines, std::string _name) {
	if (_inNode != nullptr && _inLine != nullptr) { throw "A Line cannot have both an input Node and Line"; }
	if (_outNode != nullptr && _outLines.empty() == false) { throw "A Line cannot have both an output Node and Line"; }
	if (_outLines.size() == 1) { throw "A Line cannot have one output Line"; }
	isInputNode_ = false;
	if (_inNode != nullptr) {
		this->Connecting::addInput(_inNode);
		isInputNode_ = true;
	} else if (_inLine != nullptr) {
		this->Connecting::addInput(_inLine);
	}

	isOutputNode_ = false;
	if (_outNode != nullptr) {
		this->Connecting::addOutput(_outNode);
		isOutputNode_ = true;
	} else if (_outLines.empty() == false) {
		for (Line* outLine : _outLines) {
			this->Connecting::addOutput(outLine);
		}
	}
	name_ = _name;

}

bool Line::isInputNode() const {
	return this->isInputNode_;
}

bool Line::isOutputNode() const {
	return this->isOutputNode_;
}

void Line::setInputNode( Node* _node ) {
	if (_node == nullptr) {
		this->isInputNode_ = false;
		this->inputs(std::unordered_set<Connecting*>());
	}
	this->isInputNode_ = true;
	this->inputs(std::unordered_set<Connecting*>({ _node }));
}

void Line::setOutputNode(Node * _node) {
	if (_node == nullptr) {
		this->isOutputNode_ = false;
		this->outputs(std::unordered_set<Connecting*>());
	}
	this->isOutputNode_ = true;
	this->outputs(std::unordered_set<Connecting*>({ _node }));
}

std::string Line::name() const {
	return this->name_;
}

int Line::levelCalculation(std::vector<int> _levels) {
	int toReturn = -1;
	for (auto level : _levels) {
		toReturn = toReturn > level ? toReturn : level;
	}
	return toReturn;
}


