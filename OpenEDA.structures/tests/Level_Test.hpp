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
#include<unordered_set>
#include<limits>

//int inputLevelConst(void* _obj) const;
TEST(Levelized_inputLevelConst_Test, TEST01) {
	Levelized*a = new Levelized; Levelized*b = new Levelized;
	std::unordered_set<Levelized*> a1 = { a };
	std::unordered_set<Levelized*> b1 = { b };
	Levelized* l = new Levelized{ a1,b1 };
	EXPECT_ANY_THROW(int ilevel = l->inputLevelConst(););
}

//int inputLevelConst(void* _obj) const;
//void inputLevelZero(void* _obj);
TEST(Levelized_inputLevelConst_Test, TEST02) {
	Levelized*a = new Levelized; Levelized*b = new Levelized;
	std::unordered_set<Levelized*> a1 = { a };
	std::unordered_set<Levelized*> b1 = { b };
	Levelized* l = new Levelized{ a1,b1 };
	l->inputLevelZero();
	EXPECT_NO_THROW(int ilevel = l->inputLevelConst(););
}

//int inputLevelConst(void* _obj) const;
//void inputLevelZero(void* _obj);
//void inputLevelClear(void* _obj);
TEST(Levelized_inputLevelConst_Test, TEST03) {
	Levelized*a = new Levelized; Levelized*b = new Levelized;
	std::unordered_set<Levelized*> a1 = { a };
	std::unordered_set<Levelized*> b1 = { b };
	Levelized* l = new Levelized{ a1,b1 };
	l->inputLevelZero();
	l->inputLevelClear();
	EXPECT_ANY_THROW(int ilevel = l->inputLevelConst(););
}

//int outputLevelConst(void* _obj) const;
TEST(Levelized_outputLevelConst_Test, TEST01) {
	Levelized*a = new Levelized; Levelized*b = new Levelized;
	std::unordered_set<Levelized*> a1 = { a };
	std::unordered_set<Levelized*> b1 = { b };
	Levelized* c = new Levelized(a1, b1);
	Levelized* l = new Levelized{ a1,b1 };
	EXPECT_ANY_THROW(int ilevel = l->outputLevelConst(););
}

//int outputLevelConst(void* _obj) const;
//void outputLevelZero(void* _obj);
TEST(Levelized_outputLevelConst_Test, TEST02) {
	Levelized*a = new Levelized; Levelized*b = new Levelized;
	std::unordered_set<Levelized*> a1 = { a };
	std::unordered_set<Levelized*> b1 = { b };
	Levelized* l = new Levelized{ a1,b1 };
	l->outputLevelZero();
	EXPECT_NO_THROW(int ilevel = l->outputLevelConst(););
}

//int outputLevel(void* _obj);
TEST(Levelized_outputLevel_Test, TEST01) {
	Levelized*a = new Levelized; Levelized*b = new Levelized;
	Levelized*e = new Levelized; Levelized*f = new Levelized;
	std::unordered_set<Levelized*> a1 = { a };
	std::unordered_set<Levelized*> b1 = { b };
	std::unordered_set<Levelized*> e1 = { e };
	std::unordered_set<Levelized*> f1 = { f };
	Levelized* c = new Levelized(a1, b1);
	Levelized* l = new Levelized{ e1,f1 };
	EXPECT_ANY_THROW(int ilevel = l->outputLevelConst(););
}

//int inputLevel(void* _obj);
TEST(Levelized_inputLevel_Test, TEST01) {
	Levelized*a = new Levelized; Levelized*b = new Levelized;
	Levelized*e = new Levelized; Levelized*f = new Levelized;
	std::unordered_set<Levelized*> a1 = { a };
	std::unordered_set<Levelized*> b1 = { b };
	std::unordered_set<Levelized*> e1 = { e };
	std::unordered_set<Levelized*> f1 = { f };
	Levelized* c = new Levelized(a1, b1);
	Levelized* l = new Levelized{ e1,f1 };
	EXPECT_ANY_THROW(int ilevel = l->inputLevelConst(););
}