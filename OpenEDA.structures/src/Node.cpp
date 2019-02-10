/**
 * @file Node.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2018-12-23
 *
 * @copyright Copyright (c) 2018
 *
 */

#include "Node.h"

	 Node::Node() {
 }

 Node::Node(std::unordered_set<Line*> _inputs, std::unordered_set<Line*> _outputs)  {
	for (Line* input : _inputs) {
		input->setOutputNode(this);
	}
	for (Line* output : _outputs) {
		output->setInputNode(this);
	}
}
