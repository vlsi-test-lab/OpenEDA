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
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty, "l3");
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l6 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l7 = new Line(nullptr, nullptr, nullptr, empty);
	std::unordered_set<Line*> n1_in = { l1,l2 };
	std::unordered_set<Line*> n1_out = { l3 };
	std::unordered_set<Line*> n2_in = { l3,l4 };
	std::unordered_set<Line*> n2_out = { l5 };
	std::unordered_set<Line*> n3_in = { l5,l6 };
	std::unordered_set<Line*> n3_out = { l7 };
	BooleanFunction* bfunc = new BooleanFunction("and");
	std::unordered_set<Line*> inputs = { l1,l2 };
	std::unordered_set<Line*> outputs = { l3 };
	SimulationNode<bool>* sn = new SimulationNode<bool>(bfunc, inputs, outputs);
	SimulationNode<bool>* sn1 = new SimulationNode<bool>(bfunc,n1_in, n1_out);
	SimulationNode<bool>* sn2 = new SimulationNode<bool>(bfunc, n2_in, n2_out);
	SimulationNode<bool>* sn3 = new SimulationNode<bool>(bfunc, n3_in, n3_out);
	Node* n1 = new Node(n1_in, n1_out);
	Node* n2 = new Node(n2_in, n2_out);
	Node* n3 = new Node(n3_in, n3_out);
	std::unordered_set<Node*> nodes = { sn1 };
	std::unordered_set<Node*> pis = { sn2 };
	std::unordered_set<Node*> pos = { sn3 };
	std::vector<SimulationNode<bool>*> spis = { sn2 };
	Value<bool> val1(1), val2(0), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	std::vector<Value<bool>>check = { 0 };
	Circuit* c = new Circuit(nodes, pis, pos);
	Simulator<bool> sim;
	EXPECT_NO_THROW(std::vector<Value<bool>> outs = sim.applyStimulus(c, vec_val););
}

TEST(SimulatorTest, TEST02) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty, "l3");
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l6 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l7 = new Line(nullptr, nullptr, nullptr, empty);
	std::unordered_set<Line*> n1_in = { l1,l2 };
	std::unordered_set<Line*> n1_out = { l3 };
	std::unordered_set<Line*> n2_in = { l3,l4 };
	std::unordered_set<Line*> n2_out = { l5 };
	std::unordered_set<Line*> n3_in = { l5,l6 };
	std::unordered_set<Line*> n3_out = { l7 };
	BooleanFunction* bfunc = new BooleanFunction("and");
	std::unordered_set<Line*> inputs = { l1,l2 };
	std::unordered_set<Line*> outputs = { l3 };
	SimulationNode<bool>* sn = new SimulationNode<bool>(bfunc, inputs, outputs);
	SimulationNode<bool>* sn1 = new SimulationNode<bool>(bfunc, n1_in, n1_out);
	SimulationNode<bool>* sn2 = new SimulationNode<bool>(bfunc, n2_in, n2_out);
	SimulationNode<bool>* sn3 = new SimulationNode<bool>(bfunc, n3_in, n3_out);
	Node* n1 = new Node(n1_in, n1_out);
	Node* n2 = new Node(n2_in, n2_out);
	Node* n3 = new Node(n3_in, n3_out);
	std::unordered_set<Node*> nodes = { sn1 };
	std::unordered_set<Node*> pis = { sn2 };
	std::unordered_set<Node*> pos = { sn3 };
	std::vector<SimulationNode<bool>*> spis = { sn2 };
	Value<bool> val1(1), val2(0), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	std::vector<Value<bool>>check = { 0 };
	Circuit* c = new Circuit(nodes, pis, pos);
	EXPECT_NO_THROW(Simulator<bool> sim;);
}

TEST(SimulatorTest, TEST03) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty, "l3");
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l6 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l7 = new Line(nullptr, nullptr, nullptr, empty);
	std::unordered_set<Line*> n1_in = { l1,l2 };
	std::unordered_set<Line*> n1_out = { l3 };
	std::unordered_set<Line*> n2_in = { l3,l4 };
	std::unordered_set<Line*> n2_out = { l5 };
	std::unordered_set<Line*> n3_in = { l5,l6 };
	std::unordered_set<Line*> n3_out = { l7 };
	BooleanFunction* bfunc = new BooleanFunction("and");
	std::unordered_set<Line*> inputs = { l1,l2 };
	std::unordered_set<Line*> outputs = { l3 };
	SimulationNode<bool>* sn = new SimulationNode<bool>(bfunc, inputs, outputs);
	SimulationNode<bool>* sn1 = new SimulationNode<bool>(bfunc, n1_in, n1_out);
	SimulationNode<bool>* sn2 = new SimulationNode<bool>(bfunc, n2_in, n2_out);
	SimulationNode<bool>* sn3 = new SimulationNode<bool>(bfunc, n3_in, n3_out);
	Node* n1 = new Node(n1_in, n1_out);
	Node* n2 = new Node(n2_in, n2_out);
	Node* n3 = new Node(n3_in, n3_out);
	std::unordered_set<Node*> nodes = {sn2 };
	std::unordered_set<Node*> pis = { sn2 };
	std::unordered_set<Node*> pos = { };
	std::vector<SimulationNode<bool>*> spis = { sn2 };
	Value<bool> val1(1), val2(0), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	std::vector<Value<bool>>check = { 0 };
	
	Circuit* c = new Circuit(nodes, pis, pos);
	Simulator<bool> sim;
	std::vector<Value<bool>> outs = sim.applyStimulus(c, vec_val);
	EXPECT_TRUE(std::is_permutation(check.begin(),check.end(),outs.begin()));
}