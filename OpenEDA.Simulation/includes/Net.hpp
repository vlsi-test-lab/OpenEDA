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

#include "Level.h"

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

/*
 * Find the "root" of a net from a given "Line".
 */
template <class _lineType>
_lineType* root(_lineType* _line) {
	for (Connecting* input : _line->inputs()) {
		_lineType* cast = dynamic_cast<_lineType*>(input);
		if (cast != nullptr) {
			return root<_lineType>(cast);
		}
	}
	return _line;
}

/*
 * Find the "fanouts" of a net from a given "Line" (root)
 */
template <class _lineType>
std::unordered_set<_lineType*> fanouts(_lineType* _line) {
	std::unordered_set <_lineType*> toReturn;
	for (Connecting* output : _line->outputs()) {
		_lineType* cast = dynamic_cast<_lineType*>(output);
		if (cast != nullptr) {
			std::unordered_set <_lineType*> toAdd = fanouts<_lineType>(cast);
			toReturn.insert(toAdd.begin(), toAdd.end());
		}
	}
	return toReturn;
}

template <class _lineType, class _nodeType>
inline Net<_lineType, _nodeType>::Net(_lineType * _line) {
	//Get the root.
	this->root_ = root<_lineType>(_line);
	fanouts_ = fanouts(this->root_);
}

template<class _lineType, class _nodeType>
inline std::unordered_set<_lineType*> Net<_lineType, _nodeType>::addFanout(_nodeType * _node) {
	_lineType* newLine = new _lineType();
	newLine->addOutput(_node);
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
	if (this->root_->outputs().size()!=0)
	{
		newLine->addOutput(dynamic_cast<_nodeType*>(*(this->root_->outputs().begin())));
	}
	
	newLine->addInput(this->root_);
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
		_nodeType* remainingNode = nullptr;
		for (_lineType* fanout : fanouts_) {
			if (fanout != _line) {//keep this fanout's output Node.
				remainingNode = static_cast<_nodeType*>(*(fanout->outputs().begin()));
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
	for (_lineType* fanout : this->fanouts_) {
		toReturn.emplace(dynamic_cast<_nodeType*>(*(fanout->outputs().begin())));
	}
	return toReturn;
}


#endif

