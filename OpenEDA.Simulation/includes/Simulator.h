/**
 * @file Simulator.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2018-12-27
 *
 * @copyright Copyright (c) 2018
 *
 */

#ifndef Simulator_h
#define Simulator_h

#include <vector>

#include "Value.h"
#include "Circuit.h"
#include "Function.h"
#include "SimulationStructures.hpp"
#include "EventQueue.h"

/*
 * A simulator which applies stimulus to a circuit and observes outputs.
 *
 * A Simulator is any object which has the ability to apply stimulus to an
 * object.
 *
 * Objects to be simulated must be of the "Circuit" type, and must be able to
 * return a set of input Nodes which can have stimulus applied to them.
 *
 * The default (uninherited) simulator uses a priority queue to evaluate
 * the Circuit.
 *
 * The template parameter refers to the underlying primitive of the data to be
 * simulated.
 */
template <class T>
class Simulator {
public:
	/*
	 * Apply a given vector of input values to the Circuit.
	 *
	 * The number of values provided must be equal the number of inputs
	 * provided, else an exception will be thrown.
	 *
	 * The Circuit will be evalauted based on changed-Value events in a
	 * levelized order. Runtime is between O(1) and O(# Nodes).
	 *
	 * If no input Nodes are applied, a vectorised version of Circuit input
	 * Nodes will be generated. If this is done, there is no set order of input
	 * values to be applied.
	 *
	 * @param _circuit The circuit to perform simulation on.
	 * @param _stimulus The input vector of Values to apply to the Circuit.
	 * @param (optional) _queue The simulation queue to use. If none is given
	 *        (which is typical), a blank quueue will be used.
	 * @param (optional) _inputs Which circuit inputs to apply stimulus to. If not
	 *        given, it will be presumed each input value in "_stimulus"
	 *        represents a Circuit input.
	 * @param (optional) _outputs The outputs to measure. If not given, all
	 *        circuit outputs will be measured.
	 * @param (optional) _observe Which circuit outputs to measure (true =
	 *        measure, false = do not measure). If not given, all outputs will
	 *        be measured.
	 * @return The Circuit output Values created by this stimulus.
	 */
	std::vector<Value<T>> applyStimulus(
		Circuit * _circuit,
		std::vector<Value<T>> _stimulus,
		EventQueue<T> _simulationQueue = EventQueue<T>(),
		std::vector<SimulationNode<T>*> _inputs = std::vector<SimulationNode<T>*>(),
		std::vector<SimulationNode<T>*> _outputs = std::vector<SimulationNode<T>*>(),
		std::vector<bool> _observe = std::vector<bool>()
	);

protected:
	/*
	 * The current outputs of the Circuit.
	 *
	 * @param _circuit The Circuit to probe.
	 * @param _outputs The outputs to measure. If not given, all
	 *        circuit outputs will be measured.
	 * @param _observe Which circuit outputs to measure (true =
	 *        measure, false = do not measure). If not given, all outputs will
	 *        be measured.
	 * @return The current outputs of the Circuit.
	 */
	std::vector<Value<T>> outputs(
		Circuit* _circuit,
		std::vector<SimulationNode<T>*> & _outputs,
		std::vector<bool> & _observe  
		);

};

#endif
