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

class ValueTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	Value<bool> val0 =  Value<bool>(false,true);
	Value<bool> val1 =  Value<bool>(true,true);
	Value<bool> val0_iv =  Value<bool>(false,false);
	Value<bool> val1_iv =  Value<bool>(true,false);
	Value<bool> val;
	
};

//Value();
//T magnitude() const;
//T min() const;
//T max() const;
TEST_F(ValueTest, ConstructorTest01) {
	
	ASSERT_FALSE(val.valid());
	EXPECT_EQ(std::numeric_limits<bool>::min(), val.min());
	EXPECT_EQ(std::numeric_limits<bool>::max(), val.max());
}

//	Value(T _magnitude, bool _valid = true, T _min = std::numeric_limits<T>::min(),T _max = std::numeric_limits<T>::max())
//T magnitude() const;
//T min() const;
//T max() const;
TEST_F(ValueTest, ConstructorTest02) {
	ASSERT_TRUE(val0.valid());
	EXPECT_EQ(false, val0.magnitude());
	EXPECT_EQ(std::numeric_limits<bool>::min(), val.min());
	EXPECT_EQ(std::numeric_limits<bool>::max(), val.max());
}

//bool operator == (const Value<T>& _other) const;
TEST_F(ValueTest, EQTEST01) {
	
	ASSERT_TRUE(val0.valid());
	EXPECT_EQ(false, val0.magnitude());
	EXPECT_TRUE(val1==val1);
}

//bool operator == (const Value<T>& _other) const;
TEST_F(ValueTest, EQTEST02) {
	ASSERT_TRUE(val1.valid());
	ASSERT_TRUE(val0.valid());
	EXPECT_EQ(true, val1.magnitude());
	EXPECT_EQ(false, val0.magnitude());
	EXPECT_FALSE(val1 == val0);
}

//bool operator == (const Value<T>& _other) const;
TEST_F(ValueTest, EQTEST03) {
	ASSERT_FALSE(val0_iv.valid());
	ASSERT_TRUE(val0.valid());
	EXPECT_EQ(false, val0_iv.magnitude());
	EXPECT_EQ(false, val0.magnitude());
	EXPECT_FALSE(val0_iv == val0);
}

//bool operator != (const Value<T>& _other) const;
TEST_F(ValueTest, NETEST01) {
	ASSERT_TRUE(val0.valid());
	EXPECT_EQ(false, val0.magnitude());
	EXPECT_FALSE(val0 != val0);
}

//bool operator != (const Value<T>& _other) const;
TEST_F(ValueTest, NETEST02) {
	ASSERT_TRUE(val1.valid());
	ASSERT_TRUE(val0.valid());
	EXPECT_EQ(true, val1.magnitude());
	EXPECT_EQ(false, val0.magnitude());
	EXPECT_TRUE(val1 != val0);
}

//bool operator != (const Value<T>& _other) const;
TEST_F(ValueTest, NETEST03) {
	ASSERT_FALSE(val0_iv.valid());
	ASSERT_TRUE(val0.valid());
	EXPECT_EQ(true, val1_iv.magnitude());
	EXPECT_EQ(false, val0.magnitude());
	EXPECT_TRUE(val0_iv != val0);
}

//bool operator < (const Value<T>& _other) const;
TEST_F(ValueTest, LTTEST01) {
	ASSERT_TRUE(val0.valid());
	EXPECT_EQ(false, val0.magnitude());
	EXPECT_FALSE(val0 < val0);
}

//bool operator < (const Value<T>& _other) const;
TEST_F(ValueTest, LTTEST02) {
	ASSERT_TRUE(val0.valid());
	ASSERT_TRUE(val0.valid());
	EXPECT_EQ(false, val0.magnitude());
	EXPECT_EQ(true, val1.magnitude());
	EXPECT_TRUE(val0 < val1);
}

//bool operator < (const Value<T>& _other) const;
TEST_F(ValueTest, LTTEST03) {
	ASSERT_FALSE(val0_iv.valid());
	ASSERT_TRUE(val1.valid());
	EXPECT_EQ(false, val0.magnitude());
	EXPECT_EQ(true, val1.magnitude());
	EXPECT_FALSE(val0_iv < val1);
}

//static bool possiblyDifferent(const Value<T> _value1, const Value<T> _value2);
TEST_F(ValueTest, DIFFERENTTEST01) {
	ASSERT_TRUE(val0.valid());
	EXPECT_EQ(false, val0.magnitude());
	EXPECT_FALSE(val0.possiblyDifferent(val0,val0));
}

//static bool possiblyDifferent(const Value<T> _value1, const Value<T> _value2);
TEST_F(ValueTest, DIFFERENTTEST02) {
	//Value<bool> val1(false), val2(true);
	ASSERT_TRUE(val0.valid());
	ASSERT_TRUE(val1.valid());
	EXPECT_EQ(false, val0.magnitude());
	EXPECT_EQ(true, val1.magnitude());
	EXPECT_TRUE(val0.possiblyDifferent(val0, val1));
}

//static bool possiblyDifferent(const Value<T> _value1, const Value<T> _value2);
TEST_F(ValueTest, DIFFERENTTEST03) {
	//Value<bool> val1(false, false), val2(true);
	ASSERT_FALSE(val0_iv.valid());
	ASSERT_TRUE(val1.valid());
	EXPECT_EQ(false, val0_iv.magnitude());
	EXPECT_EQ(true, val1.magnitude());
	EXPECT_TRUE(val1.possiblyDifferent(val0_iv, val1));
}

//T magnitude(T _magnitude) ;
TEST_F(ValueTest, MagnitudeTEST01) {
	EXPECT_EQ(true, val1.magnitude());
	EXPECT_EQ(false, val0.magnitude());
}

//T magnitude(T _magnitude) ;
TEST_F(ValueTest, MagnitudeTEST02) {
	EXPECT_EQ(false, val0.magnitude());
	val0.magnitude(true);
	EXPECT_EQ(true, val0.magnitude());
}

//T magnitude(T _magnitude) ;
TEST_F(ValueTest, MagnitudeTEST03) {
	EXPECT_EQ(true, val1.magnitude());
	val1.magnitude(false);
	EXPECT_EQ(false, val1.magnitude());
}


//bool valid(bool _valid);
TEST_F(ValueTest, VALIDTEST01) {
	EXPECT_FALSE(val1_iv.valid());
	val1_iv.valid(true);
	EXPECT_TRUE(val1_iv.valid());
}

//bool valid(bool _valid);
TEST_F(ValueTest, VALIDTEST02) {
	EXPECT_TRUE(val0.valid());
	val0.valid(false);
	EXPECT_FALSE(val0.valid());
}

//bool valid(bool _valid);
TEST_F(ValueTest, VALIDTEST03) {
	EXPECT_FALSE(val1_iv.valid());
	val1_iv.valid(false);
	EXPECT_FALSE(val1_iv.valid());
}

//bool increment();
TEST_F(ValueTest, INCREMENTTEST01) {
	ASSERT_TRUE(val1.increment());
	EXPECT_EQ(false,val1.magnitude());
}

//bool increment();
TEST_F(ValueTest, TEST02) {
	ASSERT_FALSE(val0.increment());
	EXPECT_EQ(true, val0.magnitude());
}

//unsigned long int cardinality() const;
TEST_F(ValueTest, CARDINALITYTEST) {
	EXPECT_EQ(2, val0.cardinality());
}
class ValuedTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	Value<bool> val0 = new Value<bool>(0);
	Value<bool> val1 = new Value<bool>(1);
	Value<bool> val;
	Valued<bool> valued;
	Valued<bool> valueded = new Valued<bool>(val);
	Valued<bool> valued1  = new Valued<bool>(val1);
};
//Valued();
TEST_F(ValuedTest, CONTRUCTORTEST01) {

	EXPECT_FALSE(valued.value().valid());
}

//Valued(Value<T> _value);
TEST_F(ValuedTest, CONTRUCTORTEST02) {

	EXPECT_TRUE(valued1.value().valid());
}

//Valued(Value<T> _value);
TEST_F(ValuedTest, CONTRUCTORTEST03) {

	EXPECT_TRUE(valued1.value().valid());
	EXPECT_EQ(1,valued1.value().magnitude());

}
