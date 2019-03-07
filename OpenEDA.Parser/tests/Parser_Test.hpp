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
#include"Parser.h"
#include"Circuit.h"
#include <unordered_set>

class ParserTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	Parser parse;
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
