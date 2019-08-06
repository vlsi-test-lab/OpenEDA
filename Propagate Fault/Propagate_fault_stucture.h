#pragma once
#include"Fault.h"
#include <vector>
#include<iostream>
#include<algorithm>
#include"FaultStructures.hpp"
#include"COPStructures.h"
#include"Function.h"
#include"SimulationStructures.hpp"
#include"COPFaulty.hpp"

/*
*propagate fault information


*/


template <class _primitive>
class Propagate_fault : virtual public Levelized {
public:
	/*
	*creat a Propagate_fault object.

	*@bool (optional) Does this object always calculate on call? (default no)

	*/

	Propagate_fault(bool _calculateAlways = true);

	/*
	*return propagate faults set of the object

	*@return propagat faults set of the object

	*/

	int propagate_faults();
protected:
	/*
	 * Call this object to calculate its propagate faults.
	 *
	 * This function is implicitly meant to be overwritten by the inherited
	 * object.
	 *
	 * @return The propagate faults.
	 */


	virtual int calculate_propagate_faults() = 0;

private:


	/*
	 * The current Propagate faults  of this object .
	 */
	int Propagate_faults_;
	
};


/*
 * A Line which holds information necessary to perform Propagate_fault.
 *
 * .
 */

template <class _primitive>
class Propagate_faultLine : public virtual  FaultyLine<_primitive>, public virtual  COPLine<_primitive>, public Propagate_fault<_primitive> {
public:


	/*
	 * Create a Propagate_faultLine with a "UNDEF" name.
	 */

	Propagate_faultLine();

	/*
 * Create a Line with a given name
 *
 * @param _name The name of the Line
 */

	Propagate_faultLine(std::string _name);
protected:

	/*
	 * Call this Line to calculate its propagate faults.
	 *
	 * For a Line x, if it is a fanout,the propagate faults is equal to the propagate faults of the
	 * driving line times line x observability divided by the sum of
     *observabilities associated with all stem’s branches. 
	 *if it is not a fanout the propagate faults is equal to the propagate faults of the driving node
	 *
	 * @return The propagate faults calculated.
	 */

	virtual int calculate_propagate_faults();

};


/*
 * A Node which holds information necessary to perform propagate_faults.
 *
 * 
 */

template <class _primitive>
class Propagate_faultNode : virtual public FaultyNode<_primitive>, public Propagate_fault<_primitive> {
public:

	/*
	 * Create a node with no inputs, no outputs, and a "copy" function.
	 */

	Propagate_faultNode() : 
		FaultyNode<_primitive>(),
		Propagate_fault<_primitive>(true),
		Connecting()
    {

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
	Propagate_faultNode(Function<_primitive>* _function,
			std::unordered_set<Propagate_faultLine<_primitive>*> _inputs = std::unordered_set<Propagate_faultLine<_primitive>*>(),
			std::unordered_set<Propagate_faultLine<_primitive>*> _outputs = std::unordered_set<Propagate_faultLine<_primitive>*>()):
		FaultyNode<_primitive>(
			_function,
			std::unordered_set<FaultyLine<_primitive>*>(_inputs.begin(), _inputs.end()),
			std::unordered_set<FaultyLine<_primitive>*>(_outputs.begin(), _outputs.end())
			),
		Propagate_fault<_primitive>(true),
		Connecting(
			std::unordered_set<Connecting*>(_inputs.begin(), _inputs.end()),
			std::unordered_set<Connecting*>(_outputs.begin(), _outputs.end())
		)
	{
	}
protected:

	/*
	 * Call this node to calculate its propagate faults.
	 *
	 * For a node x,  propagate faults is equal to the propagate faults of the sum of 
	 * all the input propagate faults
	 
	 * @return The propagate faults calculated.
	 */


	virtual int calculate_propagate_faults();

};