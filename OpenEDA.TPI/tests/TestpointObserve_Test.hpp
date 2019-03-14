#pragma once
/**
 * @file TestpointObserve_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-26
 *
 * @copyright Copyright (c) 2019
 *
 */

#include"gtest/gtest.h"
#include"Testpoint_observe.h"
#include"Parser.h"

class TPObserveTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	Parser parser;
	Value<bool> val0 = new Value<bool>(0);
	Value<bool> val1 = new Value<bool>(1);
	std::vector<Value<bool>> vals0 = { val0 };
	std::vector<Value<bool>> vals1 = { val1 };
	std::vector<Value<bool>> val01 = { val0,val1 };
	Circuit* and = parser.Parse("and.bench");
	FaultyLine<bool>* loc1 = new FaultyLine<bool>("Fault_Location_1");
	FaultyLine<bool>* loc2 = new FaultyLine<bool>("Fault_Location_2");
	Testpoint_observe<bool>* tpobs0 = new Testpoint_observe<bool>( loc1);
	Testpoint_observe<bool>* tpobs1 = new Testpoint_observe<bool>( loc2);


};

TEST_F(TPObserveTest, ConstructorTEST01) {
	EXPECT_NO_THROW(Testpoint_observe<bool>* tpobs0 = new Testpoint_observe<bool>( loc1););
}

TEST_F(TPObserveTest, ConstructorTEST02) {
	EXPECT_ANY_THROW(Testpoint_observe<bool>* tpobs0;);
}

TEST_F(TPObserveTest, ActivateTest01) {
	EXPECT_NO_THROW(tpobs0->activate());
}

TEST_F(TPObserveTest, ActivateTest02) {
	tpobs1->activate();
	EXPECT_ANY_THROW(tpobs1->activate());
}

TEST_F(TPObserveTest, DeActivateTest01) {
	tpobs1->activate();
	EXPECT_NO_THROW(tpobs1->deactivate());
}
