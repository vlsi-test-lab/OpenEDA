/**
 * @file COPStructures.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-04
 *
 * @copyright Copyright (c) 2019
 *
 */


#ifndef COPSTructures_h
#define COPSTructures_h

#include "SimulationStructures.hpp"

/*
 * Controllability and observability information.
 *
 * It is presumed that all input and output connections are of the COP type.
 *
 * This is a pure vitrual class. Inheriting objects must designate how
 * controllability and obserability are calculated.
 */
class COP : public virtual Connecting {
public:
	/*
	 * Create a COP object.
	 *
	 * @bool (optional) Does this object always calculate on call? (default no)
	 */
	COP(bool _calculateAlways = true);

	/*
	 * Return the controllablity of the object (and calculate it if necessary).
	 *
	 * Will throw an exception if the value cannot be calculated (no objects to
	 * calculate from, failure to calculate).
	 *
	 * @return The controllability of the object.
	 */
	float controllability();

	/*
	 * Manually set the controllability of the object.
	 *
	 * @param The controllability value to set to.
	 * @return The controllability of the object (after setting).
	 */
	float controllability(float _controllability);

	/*
	 * Return the observability of the object (and calculate it if necessary).
	 *
	 * Since the observability calculation for an object can depend on the object
	 * being calcualted for (the "fan out problem"), the calling object may be 
	 * required. This is because an object may not have a "single observability".
	 * A nullptr may be acceptable if a deterministic observability value is
	 * possible.
	 *
	 * Will throw an execption if the value cannot be calculated.
	 *
	 * If the COP object was created as "always calculate", then the observability
	 * will always be recalculated unless a valid observability was manually set.
	 *
	 * @param (optional) The object calling to calculate observability.
	 * @return The observability of the object.
	 */
	float observability(COP* _calling);

	/*
	 * Manually set the observability of the object.
	 *
	 * @param The observability value to set to.
	 * @return The observability of the object (after setting).
	 */
	float observability(float _observability);
	
protected:

	/*
	 * Call this object to calculate its controllability.
	 *
	 * This function is implicitly meant to be overwritten by the inherited 
	 * object.
	 *
	 * @return The controllability calculated.
	 */
	virtual float calculateControllability() = 0;

	/*
	 * Call this object to calculate the calling's observability.
	 *
	 * This function is implicitly meant to be overwritten by the inherited
	 * object.
	 *
	 * @param The calling object to calculate the observability for.
	 * @return The controllability calculated.
	 */
	virtual float calculateObservability(COP* _calling = nullptr) = 0;

private:

	/*
	 * The current controllability value of this object (negative = undefined).
	 */
	float controllability_;

	/*
	 * The current observability value of this object (negative = undefined).
	 */
	float observability_;

	/*
	 * Does this COP object always calculate when called?
	 */
	bool calculateAlways_;
};

/*
 * A Line which holds information necessary to perform COP.
 *
 * Note that no template parameter exists since COP is only defined for binary
 * circuits.
 */
class COPLine : public virtual SimulationLine<bool> , public COP {
public:
	
	/*
	 * Create a COPLine with a "UNDEF" name.
	 */
	COPLine();

	/*
	 * Create a Line with a given name
	 *
	 * @param _name The name of the Line
	 */
	COPLine(std::string _name);

protected:

	/*
	 * Call this Line to calculate its controllability.
	 *
	 * For a Line, the controllability is equal to the controllability of the
	 * driving object (whether it's a Node or a Line).
	 *
	 * @return The controllability calculated.
	 */
	virtual float calculateControllability();

	/*
	 * Call this object to calculate the calling's observability.
	 *
	 * For a Line, the observability is equal to the maximum of all output
	 * observabilities, regardless of what they're from (Nodes or Lines).
	 *
	 * The parameter (calling object) will be ignored.
	 *
	 * @param The calling object (Line) to calculate the observability for.
	 * @return The controllability calculated.
	 */
	virtual float calculateObservability(COP* _calling = nullptr);

};

/*
 * A Node which holds information necessary to perform COP.
 *
 * Note that no template parameter exists since COP is only defined for binary
 * circuits.
 */
class COPNode : public virtual SimulationNode<bool>, COP {
public:
	/*
	 * Create a node with no inputs, no outputs, and a "copy" function.
	 */
	COPNode() : SimulationNode<bool>() , COP(true) {
		
	}

	/*
	 * Create a Boolean node.
	 *
	 * @param _function The function of this node.
	 * @param _inputs Input lines to the given node.
	 * @param _outputs Output lines to the given node.
	 * @param _pi (optional) Is the Node a PI (optional, default = false).
	 * @param _po (optional) Is the node a PO (optional, default = false).
	 */
	COPNode(Function<bool>* _function, 
			std::unordered_set<COPLine*> _inputs, 
			std::unordered_set<COPLine*> _outputs
	) :
		SimulationNode(
			_function, 
			std::unordered_set<SimulationLine<bool>*>(_inputs.begin(), _inputs.end()), 
			std::unordered_set<SimulationLine<bool>*>(_outputs.begin(), _outputs.end())
		),
		COP(true) 
	{
	}


protected:

	/*
	 * Call this Node to calculate its controllability.
	 *
	 * For a Node, the controllability is calculated using the input Lines and
	 * the Node's function.
	 *
	 * @return The controllability calculated.
	 */
	virtual float calculateControllability();

	/*
	 * Call this object to calculate the calling's observability.
	 *
	 * For a Node, the observability is calculated
	 *
	 * The parameter (calling object) will be ignored.
	 *
	 * @param The calling object (Line) to calculate the observability for.
	 * @return The controllability calculated.
	 */
	virtual float calculateObservability(COP* _calling = nullptr);
};

#endif