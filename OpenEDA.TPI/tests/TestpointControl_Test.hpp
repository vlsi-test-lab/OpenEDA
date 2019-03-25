#pragma once
/**
 * @file TestpointControls_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-26
 *
 * @copyright Copyright (c) 2019
 *
 */

#include"gtest/gtest.h"
#include"Testpoint_control.h"
#include"Parser.h"

class TPControlTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	Parser parser;
	Value<bool> val0 = new Value<bool>(0);
	Value<bool> val1 = new Value<bool>(1);
	std::vector<Value<bool>> vals0 = { val0 };
	std::vector<Value<bool>> vals1 = { val1 };
	std::vector<Value<bool>> val01 = { val0,val1 };
	std::vector<Value<bool>> val11 = { val1,val1 };
	std::vector<Value<bool>> val00 = { val0,val0 };
	FaultyLine<bool>* loc1 = new FaultyLine<bool>("Fault_Location_1");
	FaultyLine<bool>* loc2 = new FaultyLine<bool>("Fault_Location_2");
	Testpoint_control<bool>* tpcon0 = new Testpoint_control<bool>(val0,loc1);
	Testpoint_control<bool>* tpcon00 = new Testpoint_control<bool>(val0, loc1);
	Testpoint_control<bool>* tpcon1 = new Testpoint_control<bool>(val1, loc2);
	

};

TEST_F(TPControlTest, ConstructorTEST01) {
	EXPECT_NO_THROW(Testpoint_control<bool>* tpcon0 = new Testpoint_control<bool>(val0, loc1););
}

TEST_F(TPControlTest, ConstructorTEST02) {
	EXPECT_ANY_THROW(Testpoint_control<bool>* tpcon0;);
}

TEST_F(TPControlTest, EQNETest01) {
	EXPECT_NE(tpcon0,tpcon1);
}

TEST_F(TPControlTest, EQNETest02) {
	EXPECT_EQ(tpcon0, tpcon00);
}

TEST_F(TPControlTest, ActivateTest01) {
	EXPECT_NO_THROW(tpcon0->activate());
}

TEST_F(TPControlTest, ActivateTest02) {
	tpcon1->activate();
	EXPECT_ANY_THROW(tpcon1->activate());
}

TEST_F(TPControlTest, DeActivateTest01) {
	tpcon1->activate();
	EXPECT_NO_THROW(tpcon1->deactivate());
}

TEST_F(TPControlTest, ValueTest) {
	EXPECT_EQ(false,tpcon0->value().magnitude());
	EXPECT_EQ(true, tpcon1->value().magnitude());
}