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
#include"Parser.hpp"

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
	Circuit* c = parser.Parse("c17.bench");

};

TEST_F(TPCOPTest, ConstructorTEST01) {
	EXPECT_NO_THROW(TPI_COP* tpi = new TPI_COP(c););
}