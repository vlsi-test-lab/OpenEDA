/**
 * @file SimulationStructure_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-28
 *
 * @copyright Copyright (c) 2018
 *
 */

#include"gtest/gtest.h"
#include"SimulationStructures.hpp"
#include "EventQueue.h"
#include"Line.h"
#include"Node.h"

//SimulationLine()
TEST(SimLine_Constructor_Test, TEST01) {
	EXPECT_NO_THROW(SimulationLine<bool> sl;);
}

//SimulationLine()
TEST(SimLine_Constructor_Test, TEST02) {
	SimulationLine<bool> sl;
	EXPECT_EQ("UNDEF",sl.name());
}

//SimulationLine()
TEST(SimLine_Constructor_Test, TEST03) {
	SimulationLine<bool> sl("Test_Line");
	EXPECT_EQ("Test_Line", sl.name());
}

//SimulationNode()
TEST(SimNode_Constructor_Test, TEST01) {
	EXPECT_NO_THROW(SimulationNode<bool> sn;);
}

//SimulationNode()
TEST(SimNode_Constructor_Test, TEST02) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");
	std::unordered_set<Line*> in_l_n1 = { l1 };
	std::unordered_set<Line*> o_l_n1 = { l2 };
	Function<bool>* func = new BooleanFunction("nand");
	SimulationNode<bool> sn(func,in_l_n1,o_l_n1);
	Value<bool> val1(1), val2(1), val3(0), val4(1), val;
	std::vector<Value<bool>>vec_val = { val1,val2};
	EXPECT_EQ(val3,sn.function()->evaluate(vec_val));
}

//SimulationNode()
TEST(Go_Test, TEST01) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");
	std::unordered_set<Line*> in_l_n1 = { l1 };
	std::unordered_set<Line*> o_l_n1 = { l2 };
	Function<bool>* func = new BooleanFunction("nand");
	SimulationNode<bool> sn(func, in_l_n1, o_l_n1);
	Value<bool> val1(1), val2(1), val3(0), val4(1), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	std::set<std::pair<size_t, Evented*>> event_queue = sn.go();
	EXPECT_TRUE(event_queue.empty());
}

//SimulationNode()
TEST(Go_Test, TEST02) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");
	std::unordered_set<Line*> in_l_n1 = { l1 };
	std::unordered_set<Line*> o_l_n1 = { l2 };
	Function<bool>* func = new BooleanFunction("nand");
	SimulationNode<bool> sn(func, in_l_n1, o_l_n1);
	Value<bool> val1(1), val2(1), val3(0), val4(1), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	EXPECT_NO_THROW(  sn.go(); );
}