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
#include"Parser.hpp"



class FaultSimTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	Value<bool> val0 = new Value<bool>(0);
	Value<bool> val1 = new Value<bool>(1);
	Parser<FaultyLine<bool>, FaultyNode<bool>> parser;
	Parser<FaultyLine<bool>, FaultyNode<bool>> andparser;
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
		//delete fsim;
		//delete fgen;
	}
};

TEST_F(FaultSimTest, ApplyStimulus01) {
	
	EXPECT_ANY_THROW( fsim->applyStimulus(c, invalid););
}

TEST_F(FaultSimTest, ApplyStimulus02) {
	//outvals = fsim->applyStimulus(c, invals0);
	//EXPECT_TRUE(outvals.begin(),outvals.end(),zero_check.begin());
}

TEST_F(FaultSimTest, SetFaults01) {

	//EXPECT_NO_THROW(fsim->setFaults(faults));
}

TEST_F(FaultSimTest, SetFaults02) {

	//fsim->setFaults(andfaults);
	//fsim->applyStimulus(and,invalid);
	//EXPECT_EQ(2,fsim->detectedFaults().size());
}