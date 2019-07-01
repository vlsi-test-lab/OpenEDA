/**
 * @file Parser_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-15
 *
 * @copyright Copyright (c) 2018
 *
 */

#include "gtest/gtest.h"
#include "Parser.hpp"
#include "SimulationStructures.hpp"
#include "Circuit.h"
#include <unordered_set>

class ParserTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	Parser<SimulationLine<bool>, SimulationNode<bool>, bool> parse;
	Circuit* c = parse.Parse("c17.bench");
	std::unordered_set<Levelized*> nodes = c->nodes();
	std::unordered_set<Levelized*> pis = c->pis();
	std::unordered_set<Levelized*> pos = c->pos();
};
//Circuit* Parse(std::string _filePath);
TEST_F(ParserTest, TEST01) {
	
	EXPECT_ANY_THROW(Circuit* c = parse.Parse("c18.bench"););
}

//Circuit* Parse(std::string _filePath);
TEST_F(ParserTest, TEST02) {
	
	EXPECT_NO_THROW(Circuit* c = parse.Parse("c17.bench"););
}

//Circuit* Parse(std::string _filePath);
TEST_F(ParserTest, TEST03) {

	EXPECT_EQ(13,nodes.size());
}

//Circuit* Parse(std::string _filePath);
TEST_F(ParserTest, TEST04) {

	EXPECT_EQ(5, pis.size());
}

//Circuit* Parse(std::string _filePath);
TEST_F(ParserTest, TEST05) {

	EXPECT_EQ(2, pos.size());
}

//Check c17's correctness
TEST_F(ParserTest, C17TEST) {
	//1 Each PI should have ONE output and no inputs.
	for (Levelized* pi : c->pis()) {
		size_t numInputs = pi->inputs().size();
		size_t numOutputs = pi->outputs().size();
		EXPECT_EQ(numInputs, 0);
		EXPECT_EQ(numOutputs, 1);
	}

	//2 Each PO has ONE input and NO outputs
	for (Levelized* po : c->pos()) {
		EXPECT_EQ(po->inputs().size(), 1);
		EXPECT_EQ(po->outputs().size(), 0);
	}

	//3 Each NODE has at MOST ONE output.
	for (Levelized* node : c->nodes()) {
		EXPECT_LE(node->outputs().size(), 1);
	}
}