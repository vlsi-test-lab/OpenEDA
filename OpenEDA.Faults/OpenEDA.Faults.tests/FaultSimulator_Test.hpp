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
#include"Parser.h"


class FaultSimTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	Value<bool> val0 = new Value<bool>(0);
	Value<bool> val1 = new Value<bool>(1);
	Parser parser;
	Circuit* c = parser.Parse("and.bench");
	std::vector<Value<bool>> invals0 = { val0,val0,val0,val0,val0 };
	std::vector<Value<bool>> invals1 = { val1,val1,val1,val1,val1 };
};

TEST_F(FaultSimTest, ApplyStimulus01) {
	FaultSimulator<bool> fsim;
	EXPECT_ANY_THROW(fsim.applyStimulus(c, invals0););
}