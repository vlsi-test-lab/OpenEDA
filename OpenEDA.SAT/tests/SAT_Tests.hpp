#pragma once
/**
 * @file Combination_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-26
 *
 * @copyright Copyright (c) 2019
 *
 */

#include"gtest/gtest.h"
#include"SAT.h"
#include"Parser.h"

class SATTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	Parser parser;
	int time = 10;
	Value<bool> val0 = new Value<bool>(0);
	Value<bool> val1 = new Value<bool>(1);
	std::vector<Value<bool>> vals0 = { val0 };
	std::vector<Value<bool>> vals1 = { val1 };
	std::vector<Value<bool>> val01 = { val0,val1 };
	std::vector<Value<bool>> val11 = { val1,val1 };
	TraceLine<bool>* sl = new TraceLine<bool>("Test_Line");
	TraceLine<bool>* sl1 = new TraceLine<bool>("Test_Line_1");
	TraceLine<bool>* sl2 = new TraceLine<bool>("Test_Line_2");
	std::unordered_set<TraceLine<bool>*> simline = { sl };
	std::unordered_set<TraceLine<bool>*> simlines = { sl1,sl2 };
	Combination<bool>* comb0 = new Combination<bool>(simline, vals0);
	Combination<bool>* comb1 = new Combination<bool>(simline, vals1);
	Combination<bool>* comb01 = new Combination<bool>(simline, val01);
	Combination<bool>* comb0t = new Combination<bool>(simline, vals0, true);
	RestrictedSimulator<bool> rsim;
	TraceLine<bool>* sl3 = new TraceLine<bool>("Test_Line_3");
	std::unordered_set<TraceLine<bool>*> sat_in = { sl1, sl2 };
	std::unordered_set<TraceLine<bool>*> sat_out = { sl3 };
	Function<bool>* func = new BooleanFunction("nand");
	SatisfiableNode<bool>* sat = new SatisfiableNode<bool>(func, sat_in, sat_out);
	std::unordered_set<Combination<bool>*> combs = {};
	std::unordered_set<SatisfiableNode<bool>*> satnodes = {sat};
	SAT<bool>* obj = new SAT<bool>(time);
	std::unordered_set<SimulationLine<bool>*> empty = {};
	SimulationLine<bool>* l1 = new TraceLine<bool>("l1");
	SimulationLine<bool>* l2 = new TraceLine<bool>("l2");
	SimulationLine<bool>* l3 = new TraceLine<bool>("l3");
	SimulationLine<bool>* l4 = new TraceLine<bool>();
	SimulationLine<bool>* l5 = new TraceLine<bool>();
	SimulationLine<bool>* l6 = new TraceLine<bool>();
	SimulationLine<bool>* l7 = new TraceLine<bool>();
	std::unordered_set<SimulationLine<bool>*> n1_in = { l1,l2 };
	std::unordered_set<SimulationLine<bool>*> n1_out = { l3 };
	std::unordered_set<SimulationLine<bool>*> n2_in = { l3,l4 };
	std::unordered_set<SimulationLine<bool>*> n2_out = { l5 };
	std::unordered_set<SimulationLine<bool>*> n3_in = { l5,l6 };
	std::unordered_set<SimulationLine<bool>*> n3_out = { l7 };
	BooleanFunction* bfunc = new BooleanFunction("and");
	std::unordered_set<SimulationLine<bool>*> inputs = { l1,l2 };
	std::unordered_set<SimulationLine<bool>*> outputs = { l3 };
	SimulationNode<bool>* sn = new SimulationNode<bool>(bfunc, inputs, outputs);
	SimulationNode<bool>* sn1 = new SimulationNode<bool>(bfunc, n1_in, n1_out);
	SimulationNode<bool>* sn2 = new SimulationNode<bool>(bfunc, n2_in, n2_out);
	SimulationNode<bool>* sn3 = new SimulationNode<bool>(bfunc, n3_in, n3_out);
	std::unordered_set<SimulationNode<bool>*> nodes = { sn1 };
	std::unordered_set<SimulationNode<bool>*> pis = { sn1 };
	std::unordered_set<SimulationNode<bool>*> pos = { sn1 };

	std::vector<Value<bool>>vec_val = { val1,val0 };
	std::vector<Value<bool>>check = { 0 };
	Circuit* c = new Circuit(
		std::unordered_set<Levelized*>(nodes.begin(), nodes.end()),
		std::unordered_set<Levelized*>(pis.begin(), pis.end()),
		std::unordered_set<Levelized*>(pos.begin(), pos.end())
	);
	Circuit* ckt = parser.Parse("c17.bench");
	std::unordered_set<TraceLine<bool>*> csimlines = { l1,l2 };
	Combination<bool>* combo01 = new Combination<bool>(csimlines, val01);
	Combination<bool>* combo11 = new Combination<bool>(csimlines, val11);
	std::unordered_set<Combination<bool>*> combos = {combo01, combo11};
	
};


//TEST_F(SATTest, ConstructorTEST01) {
//	EXPECT_NO_THROW(RestrictedSimulator<bool> rsim;);
//}
//
//TEST_F(SATTest, setActiveTest) {
//	EXPECT_NO_THROW(rsim.setActiveSimulationNodes(satnodes););
//}
//
//TEST_F(SATTest, unssetActiveTest) {
//	rsim.setActiveSimulationNodes(satnodes);
//	EXPECT_NO_THROW(rsim.unssetActiveSimulationNodes(satnodes));
//}
//
//TEST_F(SATTest, SATTEST02) {
//	EXPECT_NO_THROW(obj->satisfy(c,combo01););
//}
//
//TEST_F(SATTest, SATTEST03) {
//	EXPECT_NO_THROW(obj->satisfy(c, combos););
//}