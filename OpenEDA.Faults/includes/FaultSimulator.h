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
	 * Create the fautl simulator.
	 *
	 * The parameter is set to true if the faults given should be interpreted
	 * as TDFs. By default, faults given are presumed to be SAFs.
	 *
	 * @param (optional) _tdfEnable Make this simulator a TDF simulator.
	 */
	FaultSimulator(bool _tdfEnable = false);

	/*
	 * On destruction, clear (delete) the fault lists.
	 */
	virtual ~FaultSimulator();

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
	std::vector<Value<_primitive>> applyStimulus(
		Circuit * _circuit, 
		std::vector<Value<_primitive>> _stimulus,
		EventQueue<_primitive> _simulationQueue = EventQueue<_primitive>(),
		std::vector<SimulationNode<_primitive>*> _inputs = std::vector<SimulationNode<_primitive>*>(),
		std::vector<SimulationNode<_primitive>*> _outputs = std::vector<SimulationNode<_primitive>*>(),
		std::vector<bool> _observe = std::vector<bool>()
	);

	/*
	 * Set the fault list to simulate.
	 *
	 * @param _faults The set of faults.
	 */
	void setFaults(std::unordered_set<Fault<_primitive>*> _faults);
	/*
	 * reSet the fault list to simulate.
	 *
	 * @param _faults The set of faults.
	 */
	void resetFaults();

	/*
	 * Return the list of detected faults.
	 *
	 * @return The detected faults.
	 */
	std::unordered_set<Fault<_primitive>*> detectedFaults();

	/*
	 * Return the fault coverage.
	 *
	 * @return the fault coverage.
	 */

	float faultcoverage();


protected:
	/*
	 * All undetected faults.
	 */
	std::unordered_set<Fault<_primitive>*> undetectedFaults_;

	/*
	 * All detected faults.
	 */
	std::unordered_set<Fault<_primitive>*> detectedFaults_;

	/*
	 * Is the Fault worth simulating, i.e., can it have an impact?
	 *
	 * @param The Fault which may (not) have an impact when activated.
	 * @return True if the fault will have an impact when activated.
	 */
	virtual bool hasImpact(Fault<_primitive>* _fault);

	/*
	 * Will a Fault NOT be excited.
	 *
	 * This is not the same as !hasImpact, since the line which the Fault is on
	 * must have a valid value.
	 *
	 * NOTE: This is used for TDF simulation (i.e., "will the first vector NOT
	 *       excite the fault, and therefore the second might).
	 *
	 * @param _fault The fault which may (not) have an impact when activated.
	 * @return True if the fault will not be effected with its current value.
	 */
	virtual bool notExcited(Fault<_primitive>* _fault);

private:
	/*
	 * Clean all fault lists: delete all faults.
	 */
	void clearFaults();

	/*
	 * Is this a TDF simulator?
	 */
	bool tdfEnable_;
};

#endif