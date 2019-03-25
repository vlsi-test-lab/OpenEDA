#pragma once
#pragma once
#pragma once
/**
 * @file TestpointInvert_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-26
 *
 * @copyright Copyright (c) 2019
 *
 */

#include"gtest/gtest.h"
#include"Testpoint_invert.h"
#include"Parser.h"

class TPInvertTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	Parser parser;
	Value<bool> val0 = new Value<bool>(0);
	Value<bool> val1 = new Value<bool>(1);
	std::vector<Value<bool>> vals0 = { val0 };
	std::vector<Value<bool>> vals1 = { val1 };
	std::vector<Value<bool>> val01 = { val0,val1 };
	FaultyLine<bool>* loc1 = new FaultyLine<bool>("Fault_Location_1");
	FaultyLine<bool>* loc2 = new FaultyLine<bool>("Fault_Location_2");
	Testpoint_invert<bool>* tpobs0 = new Testpoint_invert<bool>(loc1);
	Testpoint_invert<bool>* tpobs1 = new Testpoint_invert<bool>(loc2);


};

TEST_F(TPInvertTest, ConstructorTEST01) {
	EXPECT_NO_THROW(Testpoint_invert<bool>* tpobs0 = new Testpoint_invert<bool>(loc1););
}

TEST_F(TPInvertTest, ConstructorTEST02) {
	EXPECT_ANY_THROW(Testpoint_invert<bool>* tpobs0;);
}

TEST_F(TPInvertTest, ActivateTest01) {
	EXPECT_ANY_THROW(tpobs0->deactivate());
}

