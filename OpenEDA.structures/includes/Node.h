/**
 * @file Node.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2018-12-23
 *
 * @copyright Copyright (c) 2018
 *
 */

#ifndef Node_h
#define Node_h

#include <unordered_set>

#include "Level.h"
#include "Line.h"

class Line;

/*
 * A Node is a structrual representation of a virtex in a directed graph. A 
 * zero or more inputs and zero or more outputs. Boyond, this, a node has no
 * other identifying information, except for the inputs and outputs of a node
 * must be Lines.
 * 
 * A node can be a PI or a PI.
 *
 * NOTE: For most practial purposes, a Node will have only one output (or none)
 *
 */
class Node : public Levelized {
public:
	/*
	 * Create a Node with no Connections.
	 */
	Node();

	/*
	 * Create a node with a given list of input and output Lines. Optionally, a
	 * Node can be designated as a PI or a PO (a point of control or point of
	 * control or observation).
	 *
	 * @param _inputs Input lines to the given node.
	 * @param _outputs Output lines to the given node.
	 * @param _pi (optional) Is the Node a PI (optional, default = false).
	 * @param _po (optional) Is the node a PO (optional, default = false).
	 */
	Node(std::unordered_set<Line*> _inputs, std::unordered_set<Line*> _outputs);



private:
};


#endif