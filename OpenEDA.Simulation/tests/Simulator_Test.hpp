/**
 * @file SimulationStructure_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-10
 *
 * @copyright Copyright (c) 2018
 *
 */

#include"gtest/gtest.h"
#include "SimulationStructures.hpp"
#include"Simulator.h"

//std::vector<Value<T>> applyStimulus(Circuit * _circuit, std::vector<Value<T>> _stimulus, std::vector<SimulationNode<T>*> _inputs = std::vector<SimulationNode<T>*>());
TEST(SimulatorTest, TEST01) {
	std::unordered_set<SimulationLine<bool>*> empty = {};
	SimulationLine<bool>* l1 = new SimulationLine<bool>("l1");
	SimulationLine<bool>* l2 = new SimulationLine<bool>("l2");
	SimulationLine<bool>* l3 = new SimulationLine<bool>("l3");
	SimulationLine<bool>* l4 = new SimulationLine<bool>();
	SimulationLine<bool>* l5 = new SimulationLine<bool>();
	SimulationLine<bool>* l6 = new SimulationLine<bool>();
	SimulationLine<bool>* l7 = new SimulationLine<bool>();
	std::unordered_set<SimulationLine<bool>*> n1_in = { l1,l2 };
	std::unordered_set<SimulationLine<bool>*> n1_out = { l3 };
	std::unordered_set<SimulationLine<bool>*> n2_in = { l3,l4 };
	std::unordered_set<SimulationLine<bool>*> n2_out = { l5 };
	std::unordered_set<SimulationLine<bool>*> n3_in = { l5,l6 };
	std::unordered_set<SimulationLine<bool>*> n3_out = { l7 };
	BooleanFunction* bfunc = new BooleanFunction("and");
	BooleanFunction* copy = new BooleanFunction("copy");
	std::unordered_set<SimulationLine<bool>*> inputs = { l1,l2 };
	std::unordered_set<SimulationLine<bool>*> outputs = { l3 };
	SimulationNode<bool>* sn = new SimulationNode<bool>(bfunc, inputs, outputs);
	SimulationNode<bool>* sn1 = new SimulationNode<bool>(bfunc,n1_in, n1_out);
	SimulationNode<bool>* sn2 = new SimulationNode<bool>(bfunc, n2_in, n2_out);
	SimulationNode<bool>* sn3 = new SimulationNode<bool>(bfunc, n3_in, n3_out);
	SimulationNode<bool>* n1 = new SimulationNode<bool>(copy, n1_in, n1_out);
	SimulationNode<bool>* n2 = new SimulationNode<bool>(copy, n2_in, n2_out);
	SimulationNode<bool>* n3 = new SimulationNode<bool>(copy, n3_in, n3_out);
	std::unordered_set<SimulationNode<bool>*> nodes = { sn1 };
	std::unordered_set<SimulationNode<bool>*> pis = { sn2 };
	std::unordered_set<SimulationNode<bool>*> pos = { sn3 };
	std::vector<SimulationNode<bool>*> spis = { sn2 };
	Value<bool> val1(1), val2(0), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	std::vector<Value<bool>>check = { 0 };
	Circuit* c = new Circuit(
		std::unordered_set<Levelized*>(nodes.begin(), nodes.end()), 
		std::unordered_set<Levelized*>(pis.begin(), pis.end()),
		std::unordered_set<Levelized*>(pos.begin(), pos.end())
	);
	Simulator<bool> sim;
	EventQueue<bool> simulationQueue;
	EXPECT_NO_THROW(
		std::vector<Value<bool>> outs = sim.applyStimulus(
			c, 
			vec_val, 
			simulationQueue, 
			spis)
	);
}