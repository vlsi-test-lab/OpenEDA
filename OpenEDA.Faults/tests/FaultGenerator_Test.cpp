/**
 * @file FaultGenerator_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-02-18
 *
 * @copyright Copyright (c) 2019
 *
 */

#include"gtest/gtest.h"
#include"FaultGenerator.h"
#include"Parser.h"



//std::set<Fault<_primitive>> allFaults(Circuit* _circuit);
TEST(FaultGeneratorTest, TEST01) {
	Parser parse;
	Circuit* c = parse.Parse("c17.bench");
	EXPECT_NO_THROW(FaultGenerator<bool> fgen;);
}

//std::set<Fault<_primitive>> allFaults(Circuit* _circuit);
TEST(FaultGeneratorTest, TEST02) {
	Parser parse;
	Circuit* c = parse.Parse("c17.bench");
	FaultGenerator<bool> fgen;
	std::set<Fault<bool>> faults = fgen.allFaults(c);
	EXPECT_EQ(28,faults.size());
}