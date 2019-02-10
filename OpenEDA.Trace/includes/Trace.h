/**
 * @file Trace.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-08
 *
 * @copyright Copyright (c) 2019
 *
 */


#ifndef Trace_h
#define Trace_h

#include <set>

#include "Circuit.h"
#include "Line.h"
#include "Node.h"
#include "TraceStructures.hpp"
#include "Flagged.hpp"

/*
 * Trace through a circuit.
 *
 * A Trace object is able to trace forwards/backwards in a circuit made of 
 * Lines and Nodes. It's functions can translate Line(s) and Nodes(s) to the 
 * Line(s) and Node(s) related to them.
 *
 * All methods are static, as they are ment to be used without creating a Trace
 * object.
 *
 * @param _primitive The data primitive to represent values.
 */
template <class _primitive>
class Trace {
public:
	/*
	 * For a given Node, return all circuit PIs which have a path to the given Node.
	 *
	 * @param _circuit The circuit which has PIs which drive the Node.
	 * @param _node The Node to fine PIs for.
	 * @param _flagged A set of already visited Nodes. It can be an empty set, and the post-function value can be used to find the "cone of influence".
	 * @return The set of PIs (Nodes) which have paths to the Node.
	 */
	static std::unordered_set<TraceNode<_primitive>*> pis(Circuit* _circuit, TraceNode<_primitive>* _node, std::unordered_set<TraceNode<_primitive>*> & _flagged);

	/*
	 * For a given Line, return all circuit PIs which have a path to the given Line.
	 *
	 * @param _circuit The circuit which has PIs which drive the Line.
	 * @param _line The Line to fine PIs for.
	 * @param _flagged A set of already visited Nodes. It can be an empty set, and the post-function value can be used to find the "cone of influence".
	 * @return The set of PIs (Nodes) which have paths to the Line.
	 */
	static std::unordered_set<TraceNode<_primitive>*> pis(Circuit* _circuit, Line* _line, std::unordered_set<TraceNode<_primitive>*> & _flagged);

	/*
	 * For a given set of Lines, return all circuit PIs which have a path to the given set of Lines.
	 *
	 * @param _circuit The circuit which has PIs which drive the set of Lines.
	 * @param _lines The set of Lines to fine PIs for.
	 * @param _flagged A set of already visited Nodes. It can be an empty set, and the post-function value can be used to find the "cone of influence".
	 * @return The set of PIs (Nodes) which have paths to the set of Lines.
	 */
	static std::unordered_set<TraceNode<_primitive>*> pis(Circuit* _circuit, std::unordered_set<Line*> _lines, std::unordered_set<TraceNode<_primitive>*> & _flagged);
};



#endif