
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

#include <cstdlib> //atoi

#include "Parser.hpp"
#include "SATStructures.hpp"
#include "SAT.hpp"

class C17Tests : public ::testing::Test {
public:
	void SetUp() override {
		impossibleCombinations.push_back(std::pair<
										 std::pair<std::string, std::string>,
										 std::pair<Value<bool>, Value<bool>>
		>(std::pair<std::string, std::string>("1", "10"), std::pair<Value<bool>, Value<bool>>(o, o)));
		impossibleCombinations.push_back(std::pair<
										 std::pair<std::string, std::string>,
										 std::pair<Value<bool>, Value<bool>>
		>(std::pair<std::string, std::string>("2", "16"), std::pair<Value<bool>, Value<bool>>(o, o)));
		impossibleCombinations.push_back(std::pair<
										 std::pair<std::string, std::string>,
										 std::pair<Value<bool>, Value<bool>>
		>(std::pair<std::string, std::string>("3", "10"), std::pair<Value<bool>, Value<bool>>(o, o)));
		impossibleCombinations.push_back(std::pair<
										 std::pair<std::string, std::string>,
										 std::pair<Value<bool>, Value<bool>>
		>(std::pair<std::string, std::string>("3", "11"), std::pair<Value<bool>, Value<bool>>(o, o)));
		impossibleCombinations.push_back(std::pair<
										 std::pair<std::string, std::string>,
										 std::pair<Value<bool>, Value<bool>>
		>(std::pair<std::string, std::string>("6", "11"), std::pair<Value<bool>, Value<bool>>(o, o)));
		impossibleCombinations.push_back(std::pair<
										 std::pair<std::string, std::string>,
										 std::pair<Value<bool>, Value<bool>>
		>(std::pair<std::string, std::string>("7", "19"), std::pair<Value<bool>, Value<bool>>(o, o)));




		impossibleCombinations.push_back(std::pair<
										 std::pair<std::string, std::string>,
										 std::pair<Value<bool>, Value<bool>>
		>(std::pair<std::string, std::string>("10", "22"), std::pair<Value<bool>, Value<bool>>(o, o)));
		impossibleCombinations.push_back(std::pair<
										 std::pair<std::string, std::string>,
										 std::pair<Value<bool>, Value<bool>>
		>(std::pair<std::string, std::string>("11", "16"), std::pair<Value<bool>, Value<bool>>(o, o)));
		impossibleCombinations.push_back(std::pair<
										 std::pair<std::string, std::string>,
										 std::pair<Value<bool>, Value<bool>>
		>(std::pair<std::string, std::string>("11", "19"), std::pair<Value<bool>, Value<bool>>(o, o)));
		impossibleCombinations.push_back(std::pair<
										 std::pair<std::string, std::string>,
										 std::pair<Value<bool>, Value<bool>>
		>(std::pair<std::string, std::string>("11", "23"), std::pair<Value<bool>, Value<bool>>(o, i)));
		impossibleCombinations.push_back(std::pair<
										 std::pair<std::string, std::string>,
										 std::pair<Value<bool>, Value<bool>>
		>(std::pair<std::string, std::string>("16", "22"), std::pair<Value<bool>, Value<bool>>(o, o)));
		impossibleCombinations.push_back(std::pair<
										 std::pair<std::string, std::string>,
										 std::pair<Value<bool>, Value<bool>>
		>(std::pair<std::string, std::string>("16", "23"), std::pair<Value<bool>, Value<bool>>(o, o)));
		impossibleCombinations.push_back(std::pair<
										 std::pair<std::string, std::string>,
										 std::pair<Value<bool>, Value<bool>>
		>(std::pair<std::string, std::string>("19", "23"), std::pair<Value<bool>, Value<bool>>(o, o)));

		initializeAllCombinations();
	}

	Parser<SATLine<bool>, SATNode<bool>> parser;
	Circuit* c17 = parser.Parse("c17.bench");
	SAT<bool, SATLine<bool>, SATNode<bool>> sat = SAT<bool, SATLine<bool>, SATNode<bool>>(3600);
	
	Value<bool> o = Value<bool>(false);
	Value<bool> i = Value<bool>(true);

	//This data structure contains ALL impossible line-pair combinations.
	//The first first part of the pair is the pair of line names (lower number always first).
	//The second part of the pair is the pair of values which is impossible.
	std::vector<
		std::pair<
		std::pair<std::string, std::string>,
		std::pair<Value<bool>, Value<bool>>
		>
	> impossibleCombinations;

	//This data structure contains ALL line combinations in the circuit. It is 
	//initialized using the following function, which is called in "SetUp".
	std::unordered_set< Combination<bool, SATLine<bool>, SATNode<bool>>*> allCombinations;

	void initializeAllCombinations() {
		for (Levelized* firstNode : c17->nodes()) {
			if (firstNode->outputs().size() == 0) { continue; } //Skip POs.
			SATLine<bool>* firstCast = dynamic_cast<SATLine<bool>*>(*(firstNode->outputs().begin()));
			for (Levelized* secondNode : c17->nodes()) {
				if (firstNode == secondNode) { continue; } //Same node (and therefore, same line)
				if (secondNode->outputs().size() == 0) { continue; } //Skip POs.
				SATLine<bool>* secondCast = dynamic_cast<SATLine<bool>*>(*(secondNode->outputs().begin()));
				std::vector<Value<bool>> values = std::vector<Value<bool>>(2, Value<bool>(false));
				do {
					Combination<bool, SATLine<bool>, SATNode<bool>>* combination;
					combination = new Combination<bool, SATLine<bool>, SATNode<bool>>(
						std::vector<SATLine<bool>*>({ firstCast, secondCast }),
						values
						);
					allCombinations.emplace(combination);
				} while (ValueVectorFunction<bool>::increment(values) == true);
			}
			
		}
	}
	
	//Return true if the given line (names) and the given values is impossible
	bool isImpossible(Combination<bool, SATLine<bool>, SATNode<bool>>* combination
		//std::string _line1, std::string _line2, Value<bool> _val1, Value<bool> _val2
	) {
		std::string _line1 = combination->lines().at(0)->name();
		std::string _line2 = combination->lines().at(1)->name();
		Value<bool> _val1 = combination->targetValues().at(0);
		Value<bool> _val2 = combination->targetValues().at(1);
		if (std::atoi(_line1.c_str()) > std::atoi(_line2.c_str())) { //Numerically, _line1 should be before _line2
			std::string tmp = _line1;
			_line1 = _line2;
			_line2 = tmp;
			//Remember: flip the values too.
			Value<bool> tmpVal = _val1;
			_val1 = _val2;
			_val2 = tmpVal;
		}
		for (std::pair<
			 std::pair<std::string, std::string>,
			 std::pair<Value<bool>, Value<bool>>
		> impossibleCombination : impossibleCombinations) {
			if (_line1 != impossibleCombination.first.first || _line2 != impossibleCombination.first.second) {
				continue;
			}
			if (_val1 != impossibleCombination.second.first || _val2 != impossibleCombination.second.second) {
				continue;
			}
			return true;
		}
		return false;
	}
	
};

//Every node input combination in this circuit should be posible.
//This test will 1) find all such combinations are possible and 2) confirm that
//the returned vector will in fact create the combination.
TEST_F(C17Tests, AllNodeCombinations) {
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

//Every line pair combination is NOT possible. This will check all of them. Those which are known to be impossible are set in "SetUp".
TEST_F(C17Tests, AllLinePairCombinations) {
	for (Combination<bool, SATLine<bool>, SATNode<bool>>* combination : allCombinations) {
		std::vector<
			std::pair<
			Combination<bool, SATLine<bool>, SATNode<bool>>*,
			Combination<bool, SATLine<bool>, SATNode<bool>>
			>
		> possible =
			sat.satisfy(
				c17,
				std::unordered_set<Combination<bool, SATLine<bool>, SATNode<bool>>*>({combination})
			);

		bool foundImpossible = (possible.size() == 0);
		bool expectImpossible = isImpossible(combination);
		EXPECT_EQ(foundImpossible, expectImpossible);
	}
}
