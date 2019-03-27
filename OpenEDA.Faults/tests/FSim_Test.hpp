#pragma once
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
#include"FaultSimulator.h"
#include"FaultGenerator.h"
#include"Parser.h"

class FSimTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	Value<bool> val0 = new Value<bool>(0);
	Value<bool> val1 = new Value<bool>(1);
	Parser parser;
	Parser andparser;
	Circuit* c = parser.Parse("c17.bench");
	//Circuit* ands = andparser.Parse("and.bench");
	std::vector<Value<bool>> invalid = { val0,val0 };
	std::vector<Value<bool>> invals0 = { val0,val0,val0,val0,val0 };
	std::vector<Value<bool>> invals1 = { val1,val1,val1,val1,val1 };
	std::vector<Value<bool>> outvals = { };
	std::vector<Value<bool>> zero_check = { val0, val1 };
	FaultSimulator<bool>* fsim;
	FaultGenerator<bool>* fgen;
	std::unordered_set<Fault<bool>*> faults = fgen->allFaults(c);
	//std::unordered_set<Fault<bool>*> andfaults = fgen->allFaults(ands);
	void TearDown()
	{
		delete fsim;
		delete fgen;
	}
};

TEST(FaultSimTests, ApplyStimulus01) {
	Parser parser;
	Value<bool> val0 = new Value<bool>(0);
	Value<bool> val1 = new Value<bool>(1);
	std::vector<Value<bool>> invalid = { val0,val0 };
	Circuit* c = parser.Parse("c17.bench");
	FaultSimulator<bool>* fsim;
	EXPECT_ANY_THROW(fsim->applyStimulus(c, invalid););
}