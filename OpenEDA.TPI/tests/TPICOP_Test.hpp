#pragma once
#pragma once
/**
 * @file Testpoint_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-26
 *
 * @copyright Copyright (c) 2019
 *
 */

#include"gtest/gtest.h"
#include"TPI_COP.h"
#include"Parser.h"

class TPCOPTest : public ::testing::Test {
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
	TPI_COP* tpi = new TPI_COP(and);
};

TEST_F(TPCOPTest, ConstructorTEST01) {
	EXPECT_NO_THROW(TPI_COP* tpi = new TPI_COP(and););
}