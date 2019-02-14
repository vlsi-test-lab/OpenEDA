/**
 * @file FaultStructure_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-28
 *
 * @copyright Copyright (c) 2018
 *
 */

#include"gtest/gtest.h"
#include"Fault.h"

 //FaultyLine();
TEST(FaultyLine_Constructor_Test, TEST01) {
	EXPECT_NO_THROW(FaultyLine<bool>fl;);
}

//FaultyLine();
TEST(FaultyLine_Constructor_Test, TEST02) {
	FaultyLine<bool> fl;
	std::string name = fl.name();
	EXPECT_EQ("UNDEF", name);
}

//FaultyLine();
TEST(FaultyLine_Constructor_Test, TEST03) {
	FaultyLine<bool> fl("Test_Line");
	std::string name = fl.name();
	EXPECT_EQ("Test_Line", name);
}