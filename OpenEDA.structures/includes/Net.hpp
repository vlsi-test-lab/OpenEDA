/**
 * @file Net.hpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-15
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef Net_h
#define Net_h

#include <set>

#include "Line.h"

/*
 * A Net is a collection of Lines.
 *
 * For most purposes, a Net should be used solely for editing a collection of
 * Lines, i.e., adding or removing Lines in a consistent manner.
 *
 * @param _lineType The type of Line which will be created if new Lines are
 *        needed. This type must have a default constructor.
 * @param _nodeType The type of Node connected to Lines. This will reduce the
 *        need for dynamic casting.
 */
template <class _lineType, class _nodeType>
class Net {
public:
	/*
	 * Create a Net from a given Line.
	 *
	 * The Line given can be any Line on a Connection of Lines, i.e., the "root"
	 * or any fan-out.
	 *
	 * @param _line The root or fan-out Line of the Net to create.
	 */
	Net(_lineType* _line);

	/*
	 * Add a given Node as an output of this Net.
	 * 
	 * @param _node The new fan-out Node of this Net.
	 * @return A set of new Lines created to accomplish this task.
	 */
	std::unordered_set<_lineType*> addFanout(_nodeType* _node);

	/*
	 * Add a given Line as an output of this Net.
	 *
	 * @param _line The new fan-out Line of this Net.
	 * @return A set of new Lines created to accomplish this task.
	 */
	std::unordered_set<_lineType*> addFanout(_lineType* _line);

	/*
	 * Remove a given Node as an output of this Net.
	 *
	 * An exception will be thrown if the given Node is not an output of the Net.
	 *
	 * @param _node The fanout Node to remove.
	 * @return A set of Lines which were deleted.
	 */
	std::unordered_set<_lineType*> removeFanout(_nodeType* _node);

	/*
	 * Remove a given Line as an output of this Net.
	 *
	 * An exception will be thrown if the given Line is not an output of the Net.
	 *
	 * @param _line The fanout Line to remove.
	 * @return A set of Lines which were deleted.
	 */
	std::unordered_set<_lineType*> removeFanout(_lineType* _line);

	/*
	 * Return all fanout Nodes.
	 *
	 * @return A set of fanout nodes.
	 */
	std::unordered_set<_nodeType*> fanoutNodes();

protected:
	/*
	 * The "root" Line of this Net.
	 */
	_lineType* root_;

	/*
	 * The "fan-out" Lines of this Net.
	 */
	std::unordered_set<_lineType*> fanouts_;
};



template <class _lineType, class _nodeType>
inline Net<_lineType, _nodeType>::Net(_lineType * _line) {
	//Is the Line a root?
	if (_line->isInputNode() == true) {//yes
		root_ = _line;
	}
	//no: This is a fan-out.
	root_ = dynamic_cast<_lineType*>(*(_line->inputs().begin()));
	fanouts_.clear();
	for (Connecting* line : root_->outputs()) {
		fanouts_.emplace(dynamic_cast<_lineType*>(line));
	}//	fanouts_ = convertConnectingToLines(root_->outputs()); // std::unordered_set<Line*>(root_->outputs().begin(), root_->outputs().end()); //May be empty, which implies "sole Line".
}

template<class _lineType, class _nodeType>
inline std::unordered_set<_lineType*> Net<_lineType, _nodeType>::addFanout(_nodeType * _node) {
	_lineType* newLine = new _lineType();
	newLine->setOutputNode(_node);
	return this->addFanout(newLine);
}

template <class _lineType, class _nodeType>
inline std::unordered_set<_lineType*> Net<_lineType, _nodeType>::addFanout(_lineType * _line) {
	std::unordered_set<_lineType*> toReturn;
	//Do we already have fan-outs?
	if (this->fanouts_.size() > 0) {//yes
		this->root_->addOutput(_line);
		this->fanouts_.emplace(_line);
		return toReturn; //No new lines were added.
	}
	//no: One extra output line needs to be created representing the root Line's "current output".
	_lineType* newLine = new _lineType();
	newLine->setOutputNode(static_cast<Node*>(*(this->root_->outputs().begin())));
	newLine->addInput(this->root_);
	this->root_->setOutputNode(nullptr);
	this->root_->outputs(std::unordered_set<Connecting*>({ newLine, _line }));
	this->root_->addOutput(_line);
	this->fanouts_.emplace(newLine); this->fanouts_.emplace(_line);
	return std::unordered_set<_lineType*>({ newLine });
}

template<class _lineType, class _nodeType>
inline std::unordered_set<_lineType*> Net<_lineType, _nodeType>::removeFanout(_nodeType * _node) {
	for (Connecting* nodeInput : _node->Node::inputs()) {
		if (this->fanouts_.find(dynamic_cast<_lineType*>(nodeInput)) != this->fanouts_.end()) {
			return this->removeFanout(dynamic_cast<_lineType*>(nodeInput));
		}
	}
	throw "Could not find fanout Line on Net.";
	return std::unordered_set<_lineType*>();
}

template<class _lineType, class _nodeType>
inline std::unordered_set<_lineType*> Net<_lineType, _nodeType>::removeFanout(_lineType * _line) {
	if (this->fanouts_.find(_line) == this->fanouts_.end()) {
		throw "Cannot remove fannout Line: does not exist as a fanout.";
	}

	//Does removing the fanout require removing multiple Lines?
	if (this->fanouts_.size() == 2) {//yes
		Node* remainingNode = nullptr;
		for (Line* fanout : fanouts_) {
			if (fanout != _line) {//keep this fanout's output Node.
				remainingNode = static_cast<Node*>(*(fanout->outputs().begin()));
			}
			delete fanout;
		}
		std::unordered_set<_lineType*> toReturn = this->fanouts_;
		this->fanouts_ = std::unordered_set<_lineType*>();
		this->root_->setOutputNode(remainingNode);
		return toReturn;
	}
	//no
	this->fanouts_.erase(_line);
	delete _line;
	return std::unordered_set<_lineType*>({ _line });
}

template<class _lineType, class _nodeType>
inline std::unordered_set<_nodeType*> Net<_lineType, _nodeType>::fanoutNodes() {
	if (this->fanouts_.size() == 0) {
		return std::unordered_set<_nodeType*>({ dynamic_cast<_nodeType*>(*(this->root_->outputs().begin())) });
	}
	std::unordered_set<_nodeType*> toReturn;
	for (Line* fanout : this->fanouts_) {
		toReturn.emplace(dynamic_cast<_nodeType*>(*(fanout->outputs().begin())));
	}
	return toReturn;
}


#endif

