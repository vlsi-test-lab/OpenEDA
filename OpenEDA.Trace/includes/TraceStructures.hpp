/**
 * @file TraceStructures.hpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-09
 *
 * @copyright Copyright (c) 2019
 *
 */


#ifndef TraceStructures_h
#define TraceStructures_h

#include <set>

#include "SimulationStructures.hpp"
#include "Flagged.hpp"

/*
 * A Node which supports tracing, forward and backwards.
 *
 * In effect, this object adds a "Flagged" feature to a Node.
 *
 * @param _primitive The underlying data type to simulate.
 */
template <class _primitive>
class TraceNode : public virtual SimulationNode<_primitive>, public Flagged {
public:
	/*
	 * Create a default TraceNode.
	 */
	TraceNode() : SimulationNode<_primitive>(), Flagged() {

	}

	/*
	 * Create a Trace node.
	 *
	 * @param _function The function of this node.
	 * @param _inputs Input lines to the given node.
	 * @param _outputs Output lines to the given node.
	 */
	TraceNode(
		Function<_primitive>* _function, 
		std::unordered_set<Line*> _inputs, 
		std::unordered_set<Line*> _outputs) : SimulationNode<_primitive>(_function, _inputs, _outputs), Flagged() 
	{
	
	}

private:

};

#endif
