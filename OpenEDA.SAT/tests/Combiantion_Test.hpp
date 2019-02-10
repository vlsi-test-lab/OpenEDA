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
#include"Combination.hpp"

//Combination(std::unordered_set<SimulationLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST(Combination_Constructor_Test, TEST01) {
	EXPECT_NO_THROW(Combination<bool> comb;);
}

//Combination(std::unordered_set<SimulationLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST(Combination_Constructor_Test, TEST02) {
	SimulationLine<bool>* sl = new SimulationLine<bool>("Test_Line");
	std::unordered_set<SimulationLine<bool>*> simlines = {sl};
	Value<bool> val1(0);
	std::vector<Value<bool>> values = {val1};
	EXPECT_NO_THROW(Combination<bool> comb(simlines, values););
}

//Combination(std::unordered_set<SimulationLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST(Combination_Constructor_Test, TEST03) {
	SimulationLine<bool>* sl = new SimulationLine<bool>("Test_Line");
	std::unordered_set<SimulationLine<bool>*> simlines = { sl };
	Value<bool> val1(0),val2(1);
	std::vector<Value<bool>> values = { val1,val2 };
	EXPECT_ANY_THROW(Combination<bool> comb(simlines, values););
}

//Combination(std::unordered_set<SimulationLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST(Combination_Constructor_Test, TEST04) {
	SimulationLine<bool>* sl1 = new SimulationLine<bool>("Test_Line_1");
	SimulationLine<bool>* sl2 = new SimulationLine<bool>("Test_Line_2");
	std::unordered_set<SimulationLine<bool>*> simlines = { sl1,sl2};
	Value<bool> val1(0);
	std::vector<Value<bool>> values = { val1 };
	EXPECT_ANY_THROW(Combination<bool> comb(simlines, values););
}

//Combination(std::unordered_set<SimulationLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST(Combination_Constructor_Test, TEST05) {
	SimulationLine<bool>* sl = new SimulationLine<bool>("Test_Line");
	std::unordered_set<SimulationLine<bool>*> simlines = { sl };
	Value<bool> val1(0);
	std::vector<Value<bool>> values = { val1 };
	Combination<bool> comb(simlines, values);
	EXPECT_FALSE(comb.seen());
}

//Combination(std::unordered_set<SimulationLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST(Combination_Seen_Test, TEST01) {
	SimulationLine<bool>* sl = new SimulationLine<bool>("Test_Line");
	std::unordered_set<SimulationLine<bool>*> simlines = { sl };
	Value<bool> val1(0);
	std::vector<Value<bool>> values = { val1 };
	Combination<bool> comb(simlines, values, true);
	EXPECT_TRUE(comb.seen());
}

//Combination(std::unordered_set<SimulationLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST(Combination_Values_Test, TEST01) {
	SimulationLine<bool>* sl = new SimulationLine<bool>("Test_Line");
	std::unordered_set<SimulationLine<bool>*> simlines = { sl };
	Value<bool> val1(0);
	std::vector<Value<bool>> values = { val1 };
	Combination<bool> comb(simlines, values);
	std::vector<Value<bool>> val_check = comb.targetValues();
	EXPECT_TRUE(std::is_permutation(val_check.begin(),val_check.end(),values.begin()));
}

//Combination(std::unordered_set<SimulationLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST(Combination_Values_Test, TEST02) {
	SimulationLine<bool>* sl = new SimulationLine<bool>("Test_Line");
	std::unordered_set<SimulationLine<bool>*> simlines = { sl };
	Value<bool> val1(0),val2(1);
	sl->value(val2);
	std::vector<Value<bool>> values = { val1 };
	std::vector<Value<bool>> values_test = { val2 };
	Combination<bool> comb(simlines, values);
	std::vector<Value<bool>> val_check = comb.currentValues();
	EXPECT_TRUE(std::is_permutation(val_check.begin(), val_check.end(), values_test.begin()));
}

//Combination(std::unordered_set<SimulationLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST(Combination_Lines_Test, TEST01) {
	SimulationLine<bool>* sl = new SimulationLine<bool>("Test_Line");
	std::unordered_set<SimulationLine<bool>*> simlines = { sl };
	Value<bool> val1(0);
	std::vector<Value<bool>> values = { val1 };
	Combination<bool> comb(simlines, values);
	std::unordered_set<SimulationLine<bool>*> line_check = comb.lines();
	EXPECT_TRUE(std::is_permutation(line_check.begin(), line_check.end(), simlines.begin()));
}

//Combination(std::unordered_set<SimulationLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST(Combination_Evaluate_Test, TEST01) {
	SimulationLine<bool>* sl = new SimulationLine<bool>("Test_Line");
	std::unordered_set<SimulationLine<bool>*> simlines = { sl };
	Value<bool> val1(0), val2(1);
	std::vector<Value<bool>> values = { val1 };
	std::vector<Value<bool>> values_given = { val1,val2 };
	Combination<bool> comb(simlines, values_given);
	std::unordered_set<SimulationLine<bool>*> line_check = comb.lines();
	EXPECT_ANY_THROW(comb.evaluate(values););
}

//Combination(std::unordered_set<SimulationLine<_primitive>*> _lines, std::vector<Value<_primitive>> _values, bool _seen = false);
TEST(Combination_Evaluate_Test, TEST02) {
	SimulationLine<bool>* sl = new SimulationLine<bool>("Test_Line");
	std::unordered_set<SimulationLine<bool>*> simlines = { sl };
	Value<bool> val1(0), val2(1);
	std::vector<Value<bool>> values = { val1,val2 };
	std::vector<Value<bool>> values_given = { val1,val2 };
	Combination<bool> comb(simlines, values_given);
	std::unordered_set<SimulationLine<bool>*> line_check = comb.lines();
	EXPECT_NO_THROW(comb.evaluate(values););
}