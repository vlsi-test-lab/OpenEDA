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

class SimNode_Test : public ::testing::Test {
public:
	void SetUp() override {

	}
	std::unordered_set<SimulationLine<bool>*> empty = {};
	SimulationLine<bool>* l1 = new SimulationLine<bool>("l1");
	SimulationLine<bool>* l2 = new SimulationLine<bool>("l2");
	std::unordered_set<SimulationLine<bool>*> in_l_n1 = { l1 };
	std::unordered_set<SimulationLine<bool>*> o_l_n1 = { l2 };
	Function<bool>* func = new BooleanFunction("nand");
	SimulationNode<bool>* sn = new SimulationNode<bool>(func, in_l_n1, o_l_n1);
	Value<bool> val1 = new Value<bool>(1);
	Value<bool> val2 = new Value<bool>(0);
	Value<bool> val3 = new Value<bool>(1);
	Value<bool> val4 = new Value<bool>(1);
	Value<bool> val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
};
//SimulationNode()
TEST_F(SimNode_Test, TEST01) {

	EXPECT_EQ(val1.magnitude() , sn->function()->evaluate(vec_val).magnitude());
}

//SimulationNode()
TEST_F(SimNode_Test, TEST02) {

	std::set<std::pair<size_t, Evented<bool>*>> event_queue = sn->go();
	EXPECT_TRUE(event_queue.empty());
}

//SimulationNode()
TEST_F(SimNode_Test, TEST03) {

	EXPECT_NO_THROW(  sn->go(); );
}