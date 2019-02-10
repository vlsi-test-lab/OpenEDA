/**
 * @file SimulationStructures.hpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-02
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef SimulationStructures_h
#define SimulationStructures_h

#include "Value.h"
#include "Line.h"
#include "Function.h"
#include "Node.h"
#include "EventQueue.h"
#include "SimulationNet.hpp"

#include <string>

/*
 * A Line which can be used for basic binary Simulation.
 *
 * A BinaryLine is capible of holding a Value.
 *
 * @param _T The underlying primitive to implement in Simulation (bool, char, etc.)
 */
template <class _T>
class SimulationLine : public Valued<_T>, public virtual Line {
public:
	/*
	 * Create a simulation line with a "UNDEF" name.
	 */
	SimulationLine() : Line(nullptr, nullptr, nullptr, std::unordered_set<Line*>(), "UNDEF") {
	};

	/*
	 * Create a Line with a given name
	 *
	 * @param _name The name of the Line
	 */
	SimulationLine( std::string _name) : Line(nullptr, nullptr, nullptr, std::unordered_set<Line*>(), _name) {
	};
};


/*
 * A Node which contains all parts needed for event-based simulation.

 * @param _T The underlying primitive to implement in Simulation (bool, char, etc.)
 */
template <class _T>
class SimulationNode : virtual public Functioned<_T>, virtual public Node, public Evented {
public:
	/*
	 * Create a node with no inputs, no outputs, and a "copy" function.
	 */
	SimulationNode() : Node() {
		this->function_ = new BooleanFunction("copy");
	}

	/*
	 * Create a Simulation node.
	 *
	 * @param _function The function of this node.
	 * @param _inputs Input lines to the given node.
	 * @param _outputs Output lines to the given node.
	 */
	SimulationNode(Function<_T>* _function, std::unordered_set<Line*> _inputs, std::unordered_set<Line*> _outputs) : Node(_inputs, _outputs) {
		this->function(_function);
	}

	/*
	 * Evaulate this Node's output value and return new simulation events.
	 *
	 * If the Node's new output value is different than it was before (i.e., if 
	 * the output Line's value is different than the Node's evaluated Value), 
	 * the output Line (and all Lines driven by the Line) will have its Value
	 * updated. All nodes which need to be re-evaluated (all nodes driven by this
	 * node) and their level will be returned.
	 *
	 * If the value does not change, then an empty list will be returned.
	 *
	 * @return New events (and their priority) created by activating this event.
	 */
	virtual std::set<std::pair<size_t, Evented*>> go() {
		SimulationLine<_T>* outputLine = dynamic_cast<SimulationLine<_T>*>(*(this->Levelized::outputs().begin())); //NOTE: do I NEED the "Levelized"?
		Value<_T> oldValue = outputLine->value();
		Value<_T> newValue = this->evaluate();
		std::set<std::pair<size_t, Evented*>> toReturn;
		if (Value<_T>::different(oldValue, newValue)) { //Value changed, so change line values and update the queue.
			SimulationNet<_T> net(outputLine);
			net.value(newValue);
			for (SimulationNode<_T>* fanoutNode : net.fanoutNodes()) {
				toReturn.emplace(
					std::pair<size_t, SimulationNode<_T>*>(
						fanoutNode->inputLevelConst(), fanoutNode
					)
				);
			}
		}
		return toReturn; //May be empty if nothing is added.
	}

};


#endif