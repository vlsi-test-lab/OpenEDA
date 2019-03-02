/**
 * @file COPStructures_Tests.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-03-01
 *
 * @copyright Copyright (c) 2019
 *
 */

#include"gtest/gtest.h"
#include"COPStructures.h"
#include"SimulationStructures.hpp"

class COPTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	COP* cop;
	std::unordered_set<SimulationLine<bool>*> empty = {};
	SimulationLine<bool>* l1 = new SimulationLine<bool>("l1");
	SimulationLine<bool>* l2 = new SimulationLine<bool>("l2");
	SimulationLine<bool>* l3 = new SimulationLine<bool>("l3");
	std::unordered_set<SimulationLine<bool>*> in_l_n1 = { l1,l2 };
	std::unordered_set<SimulationLine<bool>*> o_l_n1 = { l3 };
	Function<bool>* func = new BooleanFunction("nand");
	SimulationNode<bool>* sn = new SimulationNode<bool>(func, in_l_n1, o_l_n1);
	COPLine *cl1 = dynamic_cast<COPLine*>(l1);
	COPLine *cl2 = dynamic_cast<COPLine*>(l2);
	COPLine *cl3 = dynamic_cast<COPLine*>(l3);
	COPNode *cnode = dynamic_cast<COPNode*>(sn);
	std::unordered_set<COPLine*> inputs = {cl1,cl2};
	std::unordered_set<COPLine*> outputs = { cl3 };
};

TEST_F(COPTest, COPLine01) {
	EXPECT_NO_THROW(COPLine *cline;);
	COPLine *cline = new COPLine;
	EXPECT_EQ("UNDEF",cline->name());
}

TEST_F(COPTest, COPLine02) {
	EXPECT_NO_THROW(COPLine *cline = new COPLine("COPLine"););
	COPLine *cline = new COPLine("COPLine");
	EXPECT_EQ("COPLine",cline->name());
}

TEST_F(COPTest, SetControllabilitiesTest) {
	cl1->controllability(0.5);
	cl2->controllability(0.5);
	EXPECT_EQ(0.5,cl1->controllability());
	EXPECT_EQ(0.5, cl2->controllability());
}

TEST_F(COPTest, InputControllabilitiesTest) {
	EXPECT_EQ(0.5, cl1->controllability());
	EXPECT_EQ(0.5, cl2->controllability());
}

TEST_F(COPTest, CalculateControllabilitiesTest) {
	cl1->controllability(0.5);
	cl2->controllability(0.5);
	EXPECT_EQ(0.75, cl3->controllability());
}

TEST_F(COPTest, SetObservabilitiesTest) {
	cl3->observability(1.0);
	EXPECT_EQ(1.0, cl3->observability());
}

TEST_F(COPTest, OutputObservabilityTest) {
	EXPECT_EQ(1.0, cl3->observability());
}

TEST_F(COPTest, CalculateObservabilitiesTest) {
	cl3->observability(1.0);
	cl1->controllability(0.5);
	cl2->controllability(0.5);
	EXPECT_EQ(0.5, cl1->observability());
	EXPECT_EQ(0.5, cl2->observability());
}

TEST_F(COPTest, COPNodeTest01) {
	EXPECT_NO_THROW(COPNode* copnode;);
}

TEST_F(COPTest, COPNodeTest02) {
	EXPECT_NO_THROW(COPNode* copnode = new COPNode(func,inputs,outputs););
}

