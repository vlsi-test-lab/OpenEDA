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
	SimulationLine<bool>* sl1 = new SimulationLine<bool>("Test_Line_1");
	SimulationLine<bool>* sl2 = new SimulationLine<bool>("Test_Line_2");
	SimulationLine<bool>* sl3 = new SimulationLine<bool>("Test_Line_3");
	std::unordered_set<SimulationLine<bool>*> sat_in = { sl1, sl2 };
	std::unordered_set<SimulationLine<bool>*> sat_out = { sl3};
	Function<bool>* func = new BooleanFunction("nand");
	EXPECT_NO_THROW(SatisfiableNode<bool> sat(func, sat_in, sat_out););
}

//SatisfiableNode(Function<_primitive>* _function, std::unordered_set<SimulationLine<_primitive>*> _inputs, std::unordered_set<SimulationLine<_primitive>*> _outputs)
TEST(SATNode_Constructor_Test, TEST02) {
	SimulationLine<bool>* sl1 = new SimulationLine<bool>("Test_Line_1");
	SimulationLine<bool>* sl2 = new SimulationLine<bool>("Test_Line_2");
	SimulationLine<bool>* sl3 = new SimulationLine<bool>("Test_Line_3");
	std::unordered_set<SimulationLine<bool>*> sat_in = { sl1, sl2 };
	std::unordered_set<SimulationLine<bool>*> sat_out = { sl3 };
	Function<bool>* func = new BooleanFunction("nand");
	SatisfiableNode<bool> sat(func, sat_in, sat_out);
}