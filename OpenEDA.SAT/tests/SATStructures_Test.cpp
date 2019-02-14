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

 //SatisfiableNode(Function<_primitive>* _function, std::unordered_set<SimulationLine<_primitive>*> _inputs, std::unordered_set<SimulationLine<_primitive>*> _outputs)
TEST(SATNode_Constructor_Test, TEST01) {
	TraceLine<bool>* sl1 = new TraceLine<bool>("Test_Line_1");
	TraceLine<bool>* sl2 = new TraceLine<bool>("Test_Line_2");
	TraceLine<bool>* sl3 = new TraceLine<bool>("Test_Line_3");
	std::unordered_set<TraceLine<bool>*> sat_in = { sl1, sl2 };
	std::unordered_set<TraceLine<bool>*> sat_out = { sl3};
	Function<bool>* func = new BooleanFunction("nand");
	EXPECT_NO_THROW(SatisfiableNode<bool> sat(func, sat_in, sat_out););
}

//std::unordered_set<Combination<_primitive>*> populateAllCombinations()
TEST(Pop_Test, TEST02) {
	TraceLine<bool>* sl1 = new TraceLine<bool>("Test_Line_1");
	TraceLine<bool>* sl2 = new TraceLine<bool>("Test_Line_2");
	TraceLine<bool>* sl3 = new TraceLine<bool>("Test_Line_3");
	std::unordered_set<TraceLine<bool>*> sat_in = { sl1, sl2 };
	std::unordered_set<TraceLine<bool>*> sat_out = { sl3 };
	Function<bool>* func = new BooleanFunction("nand");
	SatisfiableNode<bool> sat(func, sat_in, sat_out);
	std::unordered_set<Combination<bool>*> combo = sat.populateAllCombinations();
	EXPECT_EQ(4,combo.size());
}

//std::unordered_set<Combination<_primitive>*> populateAllCombinations()
TEST(Pop_Test, TEST03) {
	TraceLine<bool>* sl1 = new TraceLine<bool>("Test_Line_1");
	TraceLine<bool>* sl2 = new TraceLine<bool>("Test_Line_2");
	TraceLine<bool>* sl3 = new TraceLine<bool>("Test_Line_3");
	TraceLine<bool>* sl4 = new TraceLine<bool>("Test_Line_4");
	std::unordered_set<TraceLine<bool>*> sat_in = { sl1, sl2, sl3 };
	std::unordered_set<TraceLine<bool>*> sat_out = { sl4 };
	Function<bool>* func = new BooleanFunction("nand");
	SatisfiableNode<bool> sat(func, sat_in, sat_out);
	std::unordered_set<Combination<bool>*> combo = sat.populateAllCombinations();
	EXPECT_EQ(8, combo.size());
}

//SatisfiableNode(Function<_primitive>* _function, std::unordered_set<SimulationLine<_primitive>*> _inputs, std::unordered_set<SimulationLine<_primitive>*> _outputs)
TEST(Go_Test, TEST01) {
	TraceLine<bool>* sl1 = new TraceLine<bool>("Test_Line_1");
	TraceLine<bool>* sl2 = new TraceLine<bool>("Test_Line_2");
	TraceLine<bool>* sl3 = new TraceLine<bool>("Test_Line_3");
	TraceLine<bool>* sl4 = new TraceLine<bool>("Test_Line_4");
	std::unordered_set<TraceLine<bool>*> sat_in = { sl1, sl2, sl3 };
	std::unordered_set<TraceLine<bool>*> sat_out = { sl4 };
	Function<bool>* func = new BooleanFunction("nand");
	SatisfiableNode<bool> sat(func, sat_in, sat_out);
	std::set<std::pair<size_t, Evented<bool>*>> events = sat.go();
	EXPECT_EQ(0,events);
}

//SatisfiableNode(Function<_primitive>* _function, std::unordered_set<SimulationLine<_primitive>*> _inputs, std::unordered_set<SimulationLine<_primitive>*> _outputs)
TEST(Go_Test, TEST02) {
	TraceLine<bool>* sl1 = new TraceLine<bool>("Test_Line_1");
	TraceLine<bool>* sl2 = new TraceLine<bool>("Test_Line_2");
	TraceLine<bool>* sl3 = new TraceLine<bool>("Test_Line_3");
	TraceLine<bool>* sl4 = new TraceLine<bool>("Test_Line_4");
	TraceLine<bool>* sl5 = new TraceLine<bool>("Test_Line_5");
	std::unordered_set<TraceLine<bool>*> sat_in = { sl1, sl2 };
	std::unordered_set<TraceLine<bool>*> sat_out = { sl3 };
	std::unordered_set<TraceLine<bool>*> sat1_in = { sl3, sl4 };
	std::unordered_set<TraceLine<bool>*> sat1_out = { sl5 };
	Function<bool>* func = new BooleanFunction("nand");
	SatisfiableNode<bool> sat(func, sat_in, sat_out);
	SatisfiableNode<bool> sat_1(func, sat1_in, sat1_out);
	std::set<std::pair<size_t, Evented<bool>*>> events = sat.go();
	EXPECT_EQ(1, events);
}