/**
 * @file Combination_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-26
 *
 * @copyright Copyright (c) 2019
 *
 */

#include"gtest/gtest.h"
#include"Combination.h"

class CombinationTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	Value<bool> val0 = new Value<bool>(0);
	Value<bool> val1 = new Value<bool>(1);
	std::vector<Value<bool>> vals0 = { val0 };
	std::vector<Value<bool>> vals1 = { val1 };
	std::vector<Value<bool>> val01 = { val0,val1 };
	TraceLine<bool>* sl = new TraceLine<bool>("Test_Line");
	TraceLine<bool>* sl1 = new TraceLine<bool>("Test_Line_1");
	TraceLine<bool>* sl2 = new TraceLine<bool>("Test_Line_2");
	std::unordered_set<TraceLine<bool>*> simline = { sl };
	std::unordered_set<TraceLine<bool>*> simlines = { sl1,sl2 };
	Combination<bool>* comb0 = new Combination<bool>(simline, vals0);
	Combination<bool>* comb1 = new Combination<bool>(simline, vals1);
	Combination<bool>* comb01 = new Combination<bool>(simline, val01);
	Combination<bool>* comb0t = new Combination<bool>(simline, vals0, true);

};

//Combination(std::unordered_set<TraceLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST_F(CombinationTest, ConstructorTEST01) {
	EXPECT_NO_THROW(Combination<bool> comb;);
}

//Combination(std::unordered_set<TraceLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST_F(CombinationTest, ConstructorTEST02) {

	EXPECT_NO_THROW(Combination<bool> comb(simline, vals0););
}

//Combination(std::unordered_set<TraceLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST_F(CombinationTest, ConstructorTEST03) {

	EXPECT_ANY_THROW(Combination<bool> comb(simline, val01););
}

//Combination(std::unordered_set<TraceLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST_F(CombinationTest, ConstructorTEST04) {
	EXPECT_ANY_THROW(Combination<bool> comb(simlines, vals0););
}

//Combination(std::unordered_set<TraceLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST_F(CombinationTest, SeenTEST01) {

	EXPECT_FALSE(comb0->seen());
}

//Combination(std::unordered_set<TraceLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST_F(CombinationTest, SeenTEST02) {
	EXPECT_TRUE(comb0t->seen());
}

//Combination(std::unordered_set<TraceLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST_F(CombinationTest, TargetValuesTEST01) {

	std::vector<Value<bool>> val_check = comb0->targetValues();
	EXPECT_TRUE(std::is_permutation(val_check.begin(),val_check.end(),vals1.begin()));
}

//Combination(std::unordered_set<TraceLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST_F(CombinationTest, CurrentValuesTEST01) {
	sl->value(std::vector<Value<bool>>(1, val1));
	std::vector<Value<bool>> val_check = comb0->currentValues();
	EXPECT_TRUE(std::is_permutation(val_check.begin(), val_check.end(), vals1.begin()));
}

//Combination(std::unordered_set<TraceLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST_F(CombinationTest, LinesTEST01) {
	std::unordered_set<TraceLine<bool>*> line_check = comb0->lines();
	EXPECT_TRUE(std::is_permutation(line_check.begin(), line_check.end(), simline.begin()));
}

//Combination(std::unordered_set<TraceLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST_F(CombinationTest, LinesTEST02) {
	std::unordered_set<TraceLine<bool>*> line_check = comb01->lines();
	EXPECT_ANY_THROW(comb01->value(vals0););
}

//Combination(std::unordered_set<TraceLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST_F(CombinationTest, LinesTEST03) {
	std::unordered_set<TraceLine<bool>*> line_check = comb01->lines();
	EXPECT_NO_THROW(comb01->value(val01););
}