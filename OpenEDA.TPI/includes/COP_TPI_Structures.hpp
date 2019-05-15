/**
 * @file FaultStructures.hpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-05-12
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef COP_TPI_Structures_h
#define COP_TPI_Structures_h

#include "FaultStructures.hpp"
#include "COPStructures.h"

 //Forward declaration
template <class T>
class Faulty;

/*
 * A line which can be used for cop-based TPI and fault simulation.
 *
 * NOTE: This structure has no added functionallity.
 *
 * NOTE: There is no "_primitive" parameter since COP is "bool-only".
 */
class COP_TPI_Line : virtual public COPLine, virtual public FaultyLine<bool> {
public:
	/*
	 * Create a with a "UNDEF" name.
	 */
	COP_TPI_Line() : COPLine(), FaultyLine<bool>(), Connecting("UNDEF") {
	};

	/*
	 * Create a Line with a given name
	 *
	 * @param _name The name of the Line
	 */
	COP_TPI_Line(std::string _name) :
		COPLine(_name),
		FaultyLine<bool>(_name),
		Connecting(_name) {
	};
};

/*
 * A node which can accept FaultyLines as inputs and outputs.
 *
 * NOTE: This structure has no added functionallity.
 *
 * NOTE: There is no "_primitive" parameter since COP is "bool-only".
 */
class COP_TPI_Node : public virtual COPNode, virtual public FaultyNode<bool>{
public:
	/*
	 * Create a node with no inputs, no outputs, and a "copy" function.
	 */
	COP_TPI_Node() : COPNode(), FaultyNode<bool>() {

	}

	/*
	 * Create a Boolean node.
	 *
	 * @param _function The function of this node.
	 * @param _inputs Input lines to the given node.
	 * @param _outputs Output lines to the given node.
	 */
	COP_TPI_Node(Function<bool>* _function,
			   std::unordered_set<COP_TPI_Line*> _inputs = std::unordered_set<COP_TPI_Line*>(),
			   std::unordered_set<COP_TPI_Line*> _outputs = std::unordered_set<COP_TPI_Line*>()
	) :
		COPNode(
			_function,
			std::unordered_set<COPLine*>(_inputs.begin(), _inputs.end()),
			std::unordered_set<COPLine*>(_outputs.begin(), _outputs.end())
			),
		FaultyNode<bool>(
			_function,
			std::unordered_set<FaultyLine<bool>*>(_inputs.begin(), _inputs.end()),
			std::unordered_set<FaultyLine<bool>*>(_outputs.begin(), _outputs.end())
		),
		SimulationNode<bool>(
			_function,
			std::unordered_set<SimulationLine<bool>*>(_inputs.begin(), _inputs.end()),
			std::unordered_set<SimulationLine<bool>*>(_outputs.begin(), _outputs.end())
			),
		Connecting(
			std::unordered_set<Connecting*>(_inputs.begin(), _inputs.end()),
			std::unordered_set<Connecting*>(_outputs.begin(), _outputs.end())
		) {
	}


};

#endif //COP_TPI_Structures_h