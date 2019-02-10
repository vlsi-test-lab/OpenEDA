/**
 * @file FaultSimulator.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-17
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef FaultSimulator_h
#define FaultSimulator_h

#include <unordered_set>

#include "Fault.h"
#include "Simulator.h"

/*
 * A Simulator capible of performing fault simulation.
 *
 * FaultSimulator builds upon existing event-based Simulators to apply
 * stimulus and measure the respons of circuits, except the same stimulus will 
 * be applied multiple times: one for each Fault (plus once for the original
 * circuit).
 *
 * @param _primitive The data primitive implemented by Values
 */
template <class _primitive>
class FaultSimulator : public Simulator<_primitive> {
public:
	/*
	 * Apply a given vector of input values to the Circuit.
	 *
	 * The number of values provided must be equal the number of inputs
	 * provided, else an exception will be thrown.
	 *
	 * If no input Nodes are applied, a vectorised version of Circuit input
	 * Nodes will be generated. If this is done, there is no set order of input
	 * values to be applied.
	 *
	 * Detected faults will be stored internally.
	 *
	 * @param _stimulus The input vector of Values to apply to the Circuit.
	 * @param (optional) _queue The simulation queue to use. If none is given
	 *        (which is typical), a blank quueue will be used.
	 * @param (optional) _inputs Which circuit inputs to apply stimulus to. If not
	 *        given, it will be presumed each input value in "_stimulus"
	 *        represents a Circuit input.
	 * @return The Circuit output Values created by this stimulus.
	 */
	std::vector<Value<_primitive>> applyStimulus(Circuit * _circuit,
										std::vector<Value<_primitive>> _stimulus,
										EventQueue _simulationQueue = _simulationQueue(),
										std::vector<SimulationNode<_primitive>*> _inputs = std::vector<SimulationNode<_primitive>*>());

protected:
	/*
	 * All undetected faults.
	 */
	std::unordered_set<Fault<_primitive>> undetectedFaults_;

	/*
	 * All detected faults.
	 */
	std::unordered_set<Fault<_primitive>> detectedFaults_;

	/*
	 * Is the Fault worth simulating, i.e., can it have an impact?
	 *
	 * @param The Fault which may (not) have an impact when activated.
	 * @return True if the fault will have an impact when activated.
	 */
	virtual bool hasImpact(Fault<_primitive> _fault);

};

#endif