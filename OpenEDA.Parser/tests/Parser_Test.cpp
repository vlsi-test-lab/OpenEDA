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

//Circuit* Parse(std::string _filePath);
TEST(ParserTest, TEST01) {
	Parser parse;
	EXPECT_ANY_THROW(Circuit* c = parse.Parse("c18.bench"););
}

//Circuit* Parse(std::string _filePath);
TEST(ParserTest, TEST02) {
	Parser parse;
	EXPECT_NO_THROW(Circuit* c = parse.Parse("c17.bench"););
}

//Circuit* Parse(std::string _filePath);
TEST(ParserTest, TEST03) {
	Parser parse;
	Circuit* c = parse.Parse("c17.bench");
	std::unordered_set<Levelized*> nodes = c->nodes();
	EXPECT_EQ(13,nodes.size());
}

//Circuit* Parse(std::string _filePath);
TEST(ParserTest, TEST04) {
	Parser parse;
	Circuit* c = parse.Parse("c17.bench");
	std::unordered_set<Levelized*> pis = c->pis();
	EXPECT_EQ(5, pis.size());
}

//Circuit* Parse(std::string _filePath);
TEST(ParserTest, TEST05) {
	Parser parse;
	Circuit* c = parse.Parse("c17.bench");
	std::unordered_set<Levelized*> pos = c->pos();
	EXPECT_EQ(2, pos.size());
}
