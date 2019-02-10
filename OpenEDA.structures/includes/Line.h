/**
 * @file Line.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2018-12-22
 *
 * @copyright Copyright (c) 2018
 *
 */

#ifndef Line_h
#define Line_h

#include <string>
#include <unordered_set>

#include "Level.h"
#include "Node.h"

class Node;

/**
 * This class models a line (not a net) in a circuit.
 *
 * A line represents the input or output of any gate (Node) in a circuit. This
 * is in contrast to a "Net" which is a collection of lines which are driven by
 * a common source and contain the same value (presuming normal circuit
 * operation.
 *
 * Depending on the context in which a lien is used, the input/output can be
 * one or more Lines or Nodes. All types are listed below:
 * 1) Node-Node: the line is driven by a Node and drives a Node. This is 
 *    representitive of a "non-fanout net".
 * 2) Node-Lines: the line is driven by a node and drives multiple lines.
 *    (i.e., the "fan-out Lines"). There should never be a case where a single
 *    line is driven (otherwise, they would be the same line).
 * 3) Line-Node: the Line is a fan-out of another Line and drives a Node.
 *
 * These are the only valid combinations. Non-driven and non-driving lines are
 * not valid. They can be created, though, but trying to access the inputs &
 * outputs of a not-fully-defined Line will throw an exception.
 *
 * Besides input/output Connections, the only other information a Line holds is
 * the "name" of a line. Line names need not be unique. The use of the default 
 * name implies the Line was never named.
 *
 * The "Levelized" feature functions will return the max input/output Level of
 * input/output Nodes.
 */
class Line : public Levelized {
public:
	/*
	 * Create a Line with given input Node/Line, output Node/Lines, and name.
	 *
	 * For this constructor, some elements may be "undefined", which depending 
	 * oncontext can be empty containers or nullptrs.
	 *
	 * @param _inNode The input Node (or nullptr if not existent)
	 * @param _outNode The output Node (or nullptr if not existent)
	 * @param _inLine The input Line (or nullptr if not existent)
	 * @param _outLines Output Lines (or empty container if not existent)
	 * @param _name The (optional) name of the Line.
	 */
	Line(Node* _inNode, Node* _outNode, Line* _inLine, std::unordered_set<Line*> _outLines, std::string _name = "");

	/*
	 * Returns true if the Line is driven by a Node.
	 *
	 * @return True if this Line is driven by a Node.
	 */
	bool isInputNode() const;

	/*
	 * Returns true if the Line drives a Node.
	 *
	 * @return True if this Line drives a Node.
	 */
	bool isOutputNode() const;

	/*
	 * Set/clear the input of this Line as the given Node.
	 * 
	 * If the input is a nullptr, the output of this Line will be cleared.
	 *
	 * @param _node The new input of this Line.
	 */
	void setInputNode( Node* _node );

	/*
	 * Set/clear the output of this Line as the given Node.
	 * 
	 * If the input is a nullptr, the output of this Line will be cleared.
	 *
	 * @param _node The new output of this Line.
	 */
	void setOutputNode(Node* _node);

	/*
	 * Returns the name of the Line.
	 *
	 * @return The name of the Line.
	 */
	virtual std::string name() const;




private:
	///*
	// * This holds the type of the Line. See Line class description.
	// */
	//Line::LineType type_;

	/*
	 * Is the input of this Line a Node.
	 */
	bool isInputNode_;

	/*
	 * Is the output of this Line a Node.
	 */
	bool isOutputNode_;

	/*
	 * The name of the line.
	 */
	std::string name_;


	/*
	 * Based on a vector of given level values, return the Level of this object.
	 *
	 * @param _levels Level values to calculated based on.
	 * @return The calculated level value.
	 */
	virtual int levelCalculation(std::vector<int> _levels);

	
};

#endif