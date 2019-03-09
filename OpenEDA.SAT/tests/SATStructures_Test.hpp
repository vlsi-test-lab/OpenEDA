/**
 * @file SATStructures_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-26
 *
 * @copyright Copyright (c) 2019
 *
 */

#include"gtest/gtest.h"
#include"SATStructures.hpp"

class SATNodeTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	TraceLine<bool>* sl1 = new TraceLine<bool>("Test_Line_1");
	TraceLine<bool>* sl2 = new TraceLine<bool>("Test_Line_2");
	TraceLine<bool>* sl3 = new TraceLine<bool>("Test_Line_3");
	std::unordered_set<TraceLine<bool>*> sat_in = { sl1, sl2 };
	std::unordered_set<TraceLine<bool>*> sat_out = { sl3 };
	Function<bool>* func = new BooleanFunction("nand");
	SatisfiableNode<bool>* sat = new SatisfiableNode<bool>(func, sat_in, sat_out);
	std::unordered_set<Combination<bool>*> combs = {};

};

 //SatisfiableNode(Function<_primitive>* _function, std::unordered_set<TraceLine<_primitive>*> _inputs, std::unordered_set<TraceLine<_primitive>*> _outputs)
TEST_F(SATNodeTest, ConstructorTEST01) {
	EXPECT_NO_THROW(SatisfiableNode<bool> sat(func, sat_in, sat_out););
}

//SatisfiableNode(Function<_primitive>* _function, std::unordered_set<TraceLine<_primitive>*> _inputs, std::unordered_set<TraceLine<_primitive>*> _outputs)
TEST_F(SATNodeTest, ConstructorTEST02) {
	combs = sat->populateAllCombinations();
	EXPECT_EQ(4,combs.size());
}