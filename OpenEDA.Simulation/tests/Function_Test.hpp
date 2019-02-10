/**
 * @file Function_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-10
 *
 * @copyright Copyright (c) 2018
 *
 */

#include"gtest/gtest.h"
#include"Function.h"


//BooleanFunction(std::string _functionString);
TEST(BFuncConstructorTest, TEST01) {
	EXPECT_ANY_THROW(BooleanFunction bfunc);
}

//BooleanFunction(std::string _functionString);
TEST(BFuncConstructorTest, TEST02) {
	EXPECT_NO_THROW(BooleanFunction bfunc("and"););
	EXPECT_NO_THROW(BooleanFunction bfunc("nand"););
	EXPECT_NO_THROW(BooleanFunction bfunc("or"););
	EXPECT_NO_THROW(BooleanFunction bfunc("nor"););
	EXPECT_NO_THROW(BooleanFunction bfunc("noT"););
	EXPECT_NO_THROW(BooleanFunction bfunc("bUf"););
	EXPECT_NO_THROW(BooleanFunction bfunc("XOR"););
	EXPECT_NO_THROW(BooleanFunction bfunc("xnor"););
}

//BooleanFunction(std::string _functionString);
TEST(BFuncConstructorTest, TEST03) {
	EXPECT_ANY_THROW(BooleanFunction bfunc("for"););
	EXPECT_ANY_THROW(BooleanFunction bfunc("absor"););
}

//std::string string() const;
TEST(StringTest, TEST01) {
	BooleanFunction bfunc("and");
	EXPECT_EQ(bfunc.string(), "and");
}

//std::string string() const;
TEST(StringTest, TEST02) {
	BooleanFunction bfunc("AND");
	EXPECT_EQ(bfunc.string(), "and");
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTAND01) {
	Value<bool> val1(1), val2(1), val3(1), val4(1),val;
	std::vector<Value<bool>>vec_val = {val1,val2,val3,val4};
	BooleanFunction bfunc("AND");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(1,val.magnitude() );
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTAND02) {
	Value<bool> val1(1), val2(0), val3(1), val4(1), val;
	std::vector<Value<bool>>vec_val = { val1,val2,val3,val4 };
	BooleanFunction bfunc("AND");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(0, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTOR01) {
	Value<bool> val1(1), val2(0), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	BooleanFunction bfunc("or");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(1, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTOR02) {
	Value<bool> val1(0), val2(0), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	BooleanFunction bfunc("or");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(0, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTOR03) {
	Value<bool> val1(0), val2(1), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	BooleanFunction bfunc("or");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(1, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTNAND01) {
	Value<bool> val1(0), val2(1), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	BooleanFunction bfunc("nand");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(1, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTNAND02) {
	Value<bool> val1(1), val2(1), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	BooleanFunction bfunc("nand");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(0, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTNOR01) {
	Value<bool> val1(1), val2(1), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	BooleanFunction bfunc("nor");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(0, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTNOR02) {
	Value<bool> val1(1), val2(0), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	BooleanFunction bfunc("nor");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(0, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTNOR03) {
	Value<bool> val1(0), val2(0), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	BooleanFunction bfunc("nor");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(1, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTNOT01) {
	Value<bool> val1(1), val;
	std::vector<Value<bool>>vec_val = { val1 };
	BooleanFunction bfunc("not");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(0, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTNOT02) {
	Value<bool> val1(0), val;
	std::vector<Value<bool>>vec_val = { val1 };
	BooleanFunction bfunc("not");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(1, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTBUF01) {
	Value<bool> val1(1), val;
	std::vector<Value<bool>>vec_val = { val1 };
	BooleanFunction bfunc("buf");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(1, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTBUF02) {
	Value<bool> val1(0), val;
	std::vector<Value<bool>>vec_val = { val1 };
	BooleanFunction bfunc("buf");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(0, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, VALIDITYTEST) {
	Value<bool> val1(0), val;
	std::vector<Value<bool>>vec_val = { };
	BooleanFunction bfunc("buf");
	EXPECT_ANY_THROW(val = bfunc.evaluate(vec_val););
	
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTXOR01) {
	Value<bool> val1(1), val2(1), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	BooleanFunction bfunc("xor");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(0, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTXOR02) {
	Value<bool> val1(1), val2(0), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	BooleanFunction bfunc("xor");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(1, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTXOR03) {
	Value<bool> val1(0), val2(0), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	BooleanFunction bfunc("xor");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(0, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTXNOR01) {
	Value<bool> val1(1), val2(1), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	BooleanFunction bfunc("xnor");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(1, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTXNOR02) {
	Value<bool> val1(1), val2(0), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	BooleanFunction bfunc("xnor");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(0, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST(BFuncEvalTest, TESTXNOR03) {
	Value<bool> val1(0), val2(0), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	BooleanFunction bfunc("xnor");
	val = bfunc.evaluate(vec_val);
	EXPECT_EQ(1, val.magnitude());
}

//Functioned();
TEST(FunctionedConstructorTest, TEST01) {
	Functioned<bool>* functed = new Functioned<bool>;
	EXPECT_EQ(functed->function(), nullptr);
}

//Functioned();
TEST(FunctionedConstructorTest, TEST02) {
	BooleanFunction* bfunc = new BooleanFunction("or");
	Value<bool> val1(0), val2(0), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	Connecting* c1 = new Connecting;
	Connecting* c2 = new Connecting;
	std::unordered_set<Connecting*>ip = { c1 };
	std::unordered_set<Connecting*>op = { c2 };
	Functioned<bool> funced(bfunc,ip,op);
	Function<bool>* func = funced.function();
	EXPECT_EQ(func->evaluate(vec_val),0);
}

//Functioned();
//Function<T>* function() const;
TEST(FunctionedConstructorTest, TEST03) {
	BooleanFunction* bfunc = new BooleanFunction("or");
	Value<bool> val1(1), val2(0), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	Connecting* c1 = new Connecting;
	Connecting* c2 = new Connecting;
	std::unordered_set<Connecting*>ip = { c1 };
	std::unordered_set<Connecting*>op = { c2 };
	Functioned<bool> funced(bfunc, ip, op);
	Function<bool>* func = funced.function();
	EXPECT_EQ(func->evaluate(vec_val), 1);
}

//Functioned();
//Function<T>* function() const;
TEST(FunctionedConstructorTest, TEST04) {
	BooleanFunction* bfunc = new BooleanFunction("and");
	Value<bool> val1(1), val2(0), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	Connecting* c1 = new Connecting;
	Connecting* c2 = new Connecting;
	std::unordered_set<Connecting*>ip = { c1 };
	std::unordered_set<Connecting*>op = { c2 };
	Functioned<bool> funced(bfunc, ip, op);
	Function<bool>* func = funced.function();
	EXPECT_EQ(func->evaluate(vec_val), 0);
}

//Functioned();
//Function<T>* function() const;
TEST(FunctionedFunctionTest, TEST01) {
	BooleanFunction* bfunc = new BooleanFunction("and");
	BooleanFunction* bfunc1 = new BooleanFunction("or");
	Value<bool> val1(1), val2(0), val;
	std::vector<Value<bool>>vec_val = { val1,val2 };
	Connecting* c1 = new Connecting;
	Connecting* c2 = new Connecting;
	std::unordered_set<Connecting*>ip = { c1 };
	std::unordered_set<Connecting*>op = { c2 };
	Functioned<bool> funced(bfunc, ip, op);
	Function<bool>* func = funced.function(bfunc1);
	EXPECT_EQ(func->evaluate(vec_val), 1);
}
