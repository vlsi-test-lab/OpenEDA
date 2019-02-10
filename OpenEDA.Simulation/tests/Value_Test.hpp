/**
 * @file Value_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-09
 *
 * @copyright Copyright (c) 2018
 *
 */

#include"gtest/gtest.h"
#include "Value.h"

//Value();
//T magnitude() const;
//T min() const;
//T max() const;
TEST(ConstructorTest, TEST01) {
	Value<bool> val;
	ASSERT_FALSE(val.valid());
	EXPECT_EQ(std::numeric_limits<bool>::min(), val.min());
	EXPECT_EQ(std::numeric_limits<bool>::max(), val.max());
}

//	Value(T _magnitude, bool _valid = true, T _min = std::numeric_limits<T>::min(),T _max = std::numeric_limits<T>::max())
//T magnitude() const;
//T min() const;
//T max() const;
TEST(ConstructorTest, TEST02) {
	Value<bool> val(0);
	ASSERT_TRUE(val.valid());
	EXPECT_EQ(0, val.magnitude());
	EXPECT_EQ(std::numeric_limits<bool>::min(), val.min());
	EXPECT_EQ(std::numeric_limits<bool>::max(), val.max());
}

//bool operator == (const Value<T>& _other) const;
TEST(EQTest, TEST01) {
	Value<bool> val1(0),val2(0);
	ASSERT_TRUE(val1.valid());
	ASSERT_TRUE(val2.valid());
	EXPECT_EQ(0, val1.magnitude());
	EXPECT_EQ(0, val2.magnitude());
	EXPECT_TRUE(val1==val2);
}

//bool operator == (const Value<T>& _other) const;
TEST(EQTest, TEST02) {
	Value<bool> val1(1), val2(0);
	ASSERT_TRUE(val1.valid());
	ASSERT_TRUE(val2.valid());
	EXPECT_EQ(1, val1.magnitude());
	EXPECT_EQ(0, val2.magnitude());
	EXPECT_FALSE(val1 == val2);
}

//bool operator == (const Value<T>& _other) const;
TEST(EQTest, TEST03) {
	Value<bool> val1(0,false), val2(0);
	ASSERT_FALSE(val1.valid());
	ASSERT_TRUE(val2.valid());
	EXPECT_EQ(0, val1.magnitude());
	EXPECT_EQ(0, val2.magnitude());
	EXPECT_FALSE(val1 == val2);
}

//bool operator != (const Value<T>& _other) const;
TEST(NETest, TEST01) {
	Value<bool> val1(0), val2(0);
	ASSERT_TRUE(val1.valid());
	ASSERT_TRUE(val2.valid());
	EXPECT_EQ(0, val1.magnitude());
	EXPECT_EQ(0, val2.magnitude());
	EXPECT_FALSE(val1 != val2);
}

//bool operator != (const Value<T>& _other) const;
TEST(NETest, TEST02) {
	Value<bool> val1(1), val2(0);
	ASSERT_TRUE(val1.valid());
	ASSERT_TRUE(val2.valid());
	EXPECT_EQ(1, val1.magnitude());
	EXPECT_EQ(0, val2.magnitude());
	EXPECT_TRUE(val1 != val2);
}

//bool operator != (const Value<T>& _other) const;
TEST(NETest, TEST03) {
	Value<bool> val1(0, false), val2(0);
	ASSERT_FALSE(val1.valid());
	ASSERT_TRUE(val2.valid());
	EXPECT_EQ(0, val1.magnitude());
	EXPECT_EQ(0, val2.magnitude());
	EXPECT_TRUE(val1 != val2);
}

//bool operator < (const Value<T>& _other) const;
TEST(LTTest, TEST01) {
	Value<bool> val1(0), val2(0);
	ASSERT_TRUE(val1.valid());
	ASSERT_TRUE(val2.valid());
	EXPECT_EQ(0, val1.magnitude());
	EXPECT_EQ(0, val2.magnitude());
	EXPECT_FALSE(val1 < val2);
}

//bool operator < (const Value<T>& _other) const;
TEST(LTTest, TEST02) {
	Value<bool> val1(0), val2(1);
	ASSERT_TRUE(val1.valid());
	ASSERT_TRUE(val2.valid());
	EXPECT_EQ(0, val1.magnitude());
	EXPECT_EQ(1, val2.magnitude());
	EXPECT_TRUE(val1 < val2);
}

//bool operator < (const Value<T>& _other) const;
TEST(LTTest, TEST03) {
	Value<bool> val1(0, false), val2(1);
	ASSERT_FALSE(val1.valid());
	ASSERT_TRUE(val2.valid());
	EXPECT_EQ(0, val1.magnitude());
	EXPECT_EQ(1, val2.magnitude());
	EXPECT_FALSE(val1 < val2);
}

//static bool different(const Value<T> _value1, const Value<T> _value2);
TEST(DifferentTest, TEST01) {
	Value<bool> val1(0), val2(0);
	ASSERT_TRUE(val1.valid());
	ASSERT_TRUE(val2.valid());
	EXPECT_EQ(0, val1.magnitude());
	EXPECT_EQ(0, val2.magnitude());
	EXPECT_FALSE(val1.different(val1,val2));
}

//static bool different(const Value<T> _value1, const Value<T> _value2);
TEST(DifferentTest, TEST02) {
	Value<bool> val1(0), val2(1);
	ASSERT_TRUE(val1.valid());
	ASSERT_TRUE(val2.valid());
	EXPECT_EQ(0, val1.magnitude());
	EXPECT_EQ(1, val2.magnitude());
	EXPECT_TRUE(val1.different(val1, val2));
}

//static bool different(const Value<T> _value1, const Value<T> _value2);
TEST(DifferentTest, TEST03) {
	Value<bool> val1(0, false), val2(1);
	ASSERT_FALSE(val1.valid());
	ASSERT_TRUE(val2.valid());
	EXPECT_EQ(0, val1.magnitude());
	EXPECT_EQ(1, val2.magnitude());
	EXPECT_TRUE(val1.different(val1, val2));
}

//T magnitude(T _magnitude) ;
TEST(MagnitudeTest, TEST01) {
	Value<bool> val(1);
	EXPECT_EQ(1, val.magnitude());
	val.magnitude(0);
	EXPECT_EQ(0, val.magnitude());
}

//T magnitude(T _magnitude) ;
TEST(MagnitudeTest, TEST02) {
	Value<bool> val(0);
	EXPECT_EQ(0, val.magnitude());
	val.magnitude(1);
	EXPECT_EQ(1, val.magnitude());
}

//T magnitude(T _magnitude) ;
TEST(MagnitudeTest, TEST03) {
	Value<bool> val(1);
	EXPECT_EQ(1, val.magnitude());
	val.magnitude(1);
	EXPECT_EQ(1, val.magnitude());
}


//bool valid(bool _valid);
TEST(ValidTest, TEST01) {
	Value<bool> val(1,false);
	EXPECT_FALSE(val.valid());
	val.valid(true);
	EXPECT_TRUE(val.valid());
}

//bool valid(bool _valid);
TEST(ValidTest, TEST02) {
	Value<bool> val(0, true);
	EXPECT_TRUE(val.valid());
	val.valid(false);
	EXPECT_FALSE(val.valid());
}

//bool valid(bool _valid);
TEST(ValidTest, TEST03) {
	Value<bool> val(1, false);
	EXPECT_FALSE(val.valid());
	val.valid(false);
	EXPECT_FALSE(val.valid());
}

//bool increment();
TEST(IncrementTest, TEST01) {
	Value<bool> val(1);
	ASSERT_TRUE(val.increment());
	EXPECT_EQ(0,val.magnitude());
}

//bool increment();
TEST(IncrementTest, TEST02) {
	Value<bool> val(0);
	ASSERT_FALSE(val.increment());
	EXPECT_EQ(1, val.magnitude());
}

//unsigned long int cardinality() const;
TEST(CardinalityTest, TEST01) {
	Value<bool> val(0);
	EXPECT_EQ(2, val.cardinality());
}

//Valued();
TEST(ValuedConstructorTest, TEST01) {
	Value<bool> val;
	Valued<bool> valued;
	EXPECT_FALSE(valued.value().valid());
}

//Valued(Value<T> _value);
TEST(ValuedConstructorTest, TEST02) {
	Value<bool> val(1);
	Valued<bool> valued(val);
	EXPECT_TRUE(valued.value().valid());
}

//Valued(Value<T> _value);
TEST(ValuedConstructorTest, TEST03) {
	Value<bool> val(1);
	Valued<bool> valued(val);
	EXPECT_TRUE(valued.value().valid());
	EXPECT_EQ(1,valued.value().magnitude());
}

//Valued(Value<T> _value);
TEST(ValuedConstructorTest, TEST04) {
	Value<bool> val;
	Valued<bool> valued(val);
	EXPECT_FALSE(valued.value().valid());
}