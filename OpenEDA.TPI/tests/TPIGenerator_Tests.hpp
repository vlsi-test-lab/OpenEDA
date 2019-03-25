#pragma once
/**
 * @file TPIGenerator_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-26
 *
 * @copyright Copyright (c) 2019
 *
 */

#include"gtest/gtest.h"
#include"TPGenerator.h"
#include"Parser.h"

class TPGenTest : public ::testing::Test {
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
	TPGenerator<bool,bool> tpgen;

};

//allTps is a private function that cannot be tested.
//TEST_F(TPGenTest, ConstructorTEST01) {
//	EXPECT_NO_THROW(tpgen.allTPs(and););
//}