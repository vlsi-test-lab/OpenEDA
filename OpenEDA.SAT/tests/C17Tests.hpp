
#pragma once
/**
 * @file Testpoint_Test.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-05-13
 *
 * @copyright Copyright (c) 2019
 *
 */

#include"gtest/gtest.h"

#include "Parser.hpp"
#include "SATStructures.hpp"
#include "SAT.hpp"

class C17Tests : public ::testing::Test {
public:
	void SetUp() override {

	}

	Parser<SATLine<bool>, SATNode<bool>> parser;
	Circuit* c17 = parser.Parse("c17.bench");
	SAT<bool, SATLine<bool>, SATNode<bool>> sat = SAT<bool, SATLine<bool>, SATNode<bool>>(30);
	


	
};

//Every node input combination in this circuit should be posible.
//This test will 1) find all such combinations are possible and 2) confirm that
//the returned vector will in fact create the combination.
TEST_F(C17Tests, AllPossible) {
	for (Levelized* node : c17->nodes()) {
		SATNode<bool>* nodeCast = dynamic_cast<SATNode<bool>*>(node);
		std::unordered_set<Combination<bool, SATLine<bool>, SATNode<bool>>*> nodeCombinations = Combination<bool, SATLine<bool>, SATNode<bool>>::allNodeCombinations(nodeCast);
		std::vector<
			std::pair<
			Combination<bool, SATLine<bool>, SATNode<bool>>*,
			Combination<bool, SATLine<bool>, SATNode<bool>>
			>
		> possible =
			sat.satisfy(
				c17,
				nodeCombinations
				);
		EXPECT_EQ(nodeCombinations.size(), possible.size());
		for(Combination<bool, SATLine<bool>, SATNode<bool>>* combination : nodeCombinations){
			delete combination;
		}
	}
}
