/**
 * @file Circuit.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2018-12-24
 *
 * @copyright Copyright (c) 2018
 *
 */

#ifndef Circuit_h
#define Circuit_h

#include <unordered_set>

#include "Level.h"

/*
 * A representation of a Circuit.
 *
 * A Circuit represent an independent circuit. 
 *
 * Circuits have knowledge of their Nodes but not their Lines. Knowledge of 
 * Lines is unnecessary, since every Line is accessable through the output of
 * Nodes.
 *
 * The inputs and outputs of a Circuit are Nodes. When requesting inputs() and 
 * outputs, the PI and PO nodes of the circuit will be returned.
 */
class Circuit {
public:
	/*
	 * Create a Circuit which consists a given set of Nodes, a set of
	 * inputs, and a set of outputs of the circuit.
	 *
	 * The inputs and output Nodes need not be a subset of the Nodes given, as 
	 * will be added to the same set of nodes if not already done so.
	 *
	 * @param _nodes The nodes to be contained in the circuit.
	 * @param _inputs The input Nodes of the circuit.
	 * @param _outputs The output Nodes of the circuit.
	 */
	Circuit(std::unordered_set<Levelized*> _nodes, std::unordered_set <Levelized*> _inputs, std::unordered_set<Levelized*> _outputs);

	/*
	 * Return all Nodes in the circuit
	 *
	 * @return The set of all nodes in the Circuit.
	 */
	std::unordered_set<Levelized*> nodes() const;

	/*
	 * Return all PIs in the circuit
	 *
	 * @return The set of all PIs in the Circuit.
	 */
	std::unordered_set<Levelized*> pis() const;

	/*
	 * Return all POs in the circuit.
	 *
	 * @return The set of all POs in the Circuit.
	 */
	std::unordered_set<Levelized*> pos() const;

	/*
	 * Add a Node to the circuit.
	 *
	 * @param _node The Node to add to the circuit.
	 */
	void addNode(Levelized* _node);

	/*
	 * Remove a Node from the circuit.
	 * 
	 * The removed Node will not be deleted.
	 *
	 * An exception will be thrown if the Node does not exist.
	 *
	 * @param The node to remove.
	 * @return The removed Node.
	 */
	Levelized* removeNode(Levelized* _node);

	/*
	 * Add the given node as a PI.
	 *
	 * If the Node is not already part of the circuit, it will be added, i.e.,
	 * calling both this function and "addNode" is redundant.
	 *
	 * @param _pi PI Node to add.
	 */
	void addPI(Levelized* _pi);

	/*
	 * Remove a PI Node from the circuit.
	 *
	 * The removed Node will not be deleted.
	 *
	 * An exception will be thrown if the Node does not exist or is not a PI.
	 *
	 * @param The PI (and Node) to remvoe.
	 * @return The removed PI Node.
	 */
	Levelized* removePI(Levelized* _pi);

	/*
	 * Add the given node as a PO.
	 *
	 * If the Node is not already part of the circuit, it will be added, i.e.,
	 * calling both this function and "addNode" is redundant.
	 *
	 * @param _po PO Node to add.
	 */
	void addPO(Levelized* _po);

	/*
	 * Remove a PO Node from the circuit.
	 *
	 * The removed Node will not be deleted.
	 *
	 * An exception will be thrown if the Node does not exist or is not a PO.
	 *
	 * @param The PO (and Node) to remvoe.
	 * @return The removed PO Node.
	 */
	Levelized* removePO(Levelized* _po);




private:
	/*
	 * The set of Nodes in this Circuit.
	 */
	std::unordered_set<Levelized*> nodes_;

	/*
	 * The set of PI nodes in this circuit.
	 */
	std::unordered_set<Levelized*> pis_;

	/*
	 * The set of PO nodes in this circuit.
	 */
	std::unordered_set<Levelized*> pos_;

};

#endif