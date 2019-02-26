/**
 * @file FaultSimulator_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-02-18
 *
 * @copyright Copyright (c) 2019
 *
 */

#include"gtest/gtest.h"
#include"FaultSimulator.h"
#include"FaultGenerator.h"
#include"Parser.h"
#include"Value.h"

class ApplyStimulusTest : public ::testing::Test {
public:
	
protected:
	void SetUp()  {
		
		
	}
	Value<bool> val0 = new Value<bool>(0);
	Value<bool> val1 = new Value<bool>(1);
	Parser parser;
	FaultSimulator<bool> fsim;
	Circuit* c = parser.Parse("c17.bench");
	std::vector<Value<bool>> invals0 = { val0,val0,val0,val0,val0 };
	std::vector<Value<bool>> invals1 = { val1,val1,val1,val1,val1 };
	
	

};

//applyStimulus()
TEST_F(ApplyStimulusTest, TEST01) {
	
	std::vector<Value<bool>> outvals = fsim.applyStimulus(c, invals0);
	
}

