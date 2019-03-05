/**
 * @file Level_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2018-12-28
 *
 * @copyright Copyright (c) 2018
 *
 */

#include"gtest/gtest.h"
#include"Level.h"


class LevelTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	Levelized*a = new Levelized; Levelized*b = new Levelized;
	Levelized*e = new Levelized; Levelized*f = new Levelized;
	std::unordered_set<Levelized*> a1 = { a };
	std::unordered_set<Levelized*> b1 = { b };
	std::unordered_set<Levelized*> e1 = { e };
	std::unordered_set<Levelized*> f1 = { f };
	Levelized* l = new Levelized{ a1,b1 };
	Levelized* c = new Levelized(e1, f1);

	void TearDown()
	{
		delete l;
		delete a;
	}
};


//int inputLevelConst(void* _obj) const;
TEST_F(LevelTest, TEST01) {
	EXPECT_ANY_THROW(int ilevel = l->inputLevelConst(););
}

//int inputLevelConst(void* _obj) const;
//void inputLevelZero(void* _obj);
TEST_F(LevelTest, TEST02) {
	l->inputLevelZero();
	EXPECT_NO_THROW(int ilevel = l->inputLevelConst(););
}

//int inputLevelConst(void* _obj) const;
//void inputLevelZero(void* _obj);
//void inputLevelClear(void* _obj);
TEST_F(LevelTest, TEST03) {
	l->inputLevelZero();
	l->inputLevelClear();
	EXPECT_ANY_THROW(int ilevel = l->inputLevelConst(););
}

//int outputLevelConst(void* _obj) const;
TEST_F(LevelTest, Levelized_outputLevelConst_Test01) {

	EXPECT_ANY_THROW(int ilevel = l->outputLevelConst(););
}

//int outputLevelConst(void* _obj) const;
//void outputLevelZero(void* _obj);
TEST_F(LevelTest, Levelized_outputLevelConst_Test02) {

	EXPECT_NO_THROW(int ilevel = l->outputLevelConst(););
}

//int outputLevel(void* _obj);
TEST_F(LevelTest, Levelized_outputLevel_Test) {

	EXPECT_ANY_THROW(int ilevel = c->outputLevelConst(););
}


//int inputLevel(void* _obj);
TEST_F(LevelTest, Levelized_inputLevel_Test) {

	EXPECT_ANY_THROW(int ilevel = c->inputLevelConst(););
}