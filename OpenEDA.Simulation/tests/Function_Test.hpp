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

class BFuncTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	Value<bool> val0 =  Value<bool>(0);
	Value<bool> val1 =  Value<bool>(1);
	Value<bool> val;
	std::vector<Value<bool>> val00 = { val0,val0 };
	std::vector<Value<bool>> val01 = { val0,val1 };
	std::vector<Value<bool>> val10 = { val1,val0 };
	std::vector<Value<bool>> val11 = { val1,val1 };
	std::vector<Value<bool>> vals1 = { val1 };
	std::vector<Value<bool>> vals0 = { val0 };
	std::vector<Value<bool>> val_empty = { };
	//BooleanFunction bfunc;
	BooleanFunction* and = new BooleanFunction("and");
	BooleanFunction* nand = new BooleanFunction("nand");
	BooleanFunction* or = new BooleanFunction("or");
	BooleanFunction* nor = new BooleanFunction("nor");
	BooleanFunction* buf = new BooleanFunction("bUf");
	BooleanFunction* xor = new BooleanFunction("XOR");
	BooleanFunction* xnor = new BooleanFunction("xnor");
	BooleanFunction* not = new BooleanFunction("noT");

};


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
TEST_F(BFuncTest, ANDTEST01) {
	EXPECT_EQ(and->string(), "and");
}

//std::string string() const;
TEST_F(BFuncTest, STRINGTEST02) {
	EXPECT_EQ(not->string(), "not");//The string should be completely converted to lowercase.
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTAND01) {
	val = and->evaluate(val11);
	EXPECT_EQ(1,val.magnitude() );
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTAND02) {
	val = and->evaluate(val00);//And is evaluated with an input vector of 0,0.
	EXPECT_EQ(0, val.magnitude());//And with an input vector of 0,0 should return an output of 0.
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTOR01) {
	val = or->evaluate(val10);
	EXPECT_EQ(1, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTOR02) {
	val = or ->evaluate(val00); // Test OR Gate with an input vector 0f 0,0.
	EXPECT_EQ(0, val.magnitude()); //Should return an output of 0.
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTOR03) {
	val = or ->evaluate(val01);
	EXPECT_EQ(1, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTNAND01) {
	val = nand->evaluate(val01); //Evaluate the NAND Gate with an input vector of 0,1.
	EXPECT_EQ(1, val.magnitude()); //The expected output should be 1.
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTNAND02) {
	val = nand->evaluate(val11);
	EXPECT_EQ(0, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTNOR01) {
	val = nor->evaluate(val11);
	EXPECT_EQ(0, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTNOR02) {
	val = nor->evaluate(val10);
	EXPECT_EQ(0, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTNOR03) {
	val = nor->evaluate(val00); //Evaluate the input to the NOR gate with a vector of 0,0.
	EXPECT_EQ(1, val.magnitude()); //The output should be 1.
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTNOT01) {
	val = not->evaluate(vals1);
	EXPECT_EQ(0, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTNOT02) {
	val = not->evaluate(vals0);// Test NOT Gate with an input vector 0f 0.
	EXPECT_EQ(1, val.magnitude());// Expected output should be 1.
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTBUF01) {
	val = buf->evaluate(vals1);
	EXPECT_EQ(1, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTBUF02) {
	val = buf->evaluate(vals0);//Evaluate the Buffer input with a value of zero.
	EXPECT_EQ(0, val.magnitude());//The output should be zero.
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, VALIDITYTEST) {
	EXPECT_ANY_THROW(val = buf->evaluate(val_empty););
	
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTXOR01) {
	val = xor->evaluate(val11);
	EXPECT_EQ(0, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTXOR02) {
	val = xor->evaluate(val10);////Evaluate the XNOR gate with an input vector of 1,0.
	EXPECT_EQ(1, val.magnitude());//Expect an output of 1.
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTXOR03) {
	val = xor->evaluate(val00);
	EXPECT_EQ(0, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTXNOR01) {
	val = xnor->evaluate(val11);
	EXPECT_EQ(1, val.magnitude());
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTXNOR02) {
	val = xnor->evaluate(val10); //Evaluate the XNOR gate with an input vector of 0,1.
	EXPECT_EQ(0, val.magnitude());// Expect an output of 0.
}

//virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;
TEST_F(BFuncTest, TESTXNOR03) {
	val = xnor->evaluate(val00);
	EXPECT_EQ(1, val.magnitude());
}
class FunctionedTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	Functioned<bool>* functed = new Functioned<bool>;

};

//Functioned();
TEST_F(FunctionedTest, TEST01) {
	
	EXPECT_EQ(functed->function(), nullptr);
}

//OBSOLETE
////Functioned();
//TEST(FunctionedConstructorTest, TEST02) {
//	BooleanFunction* bfunc = new BooleanFunction("or");
//	Value<bool> val1(0), val2(0), val;
//	std::vector<Value<bool>>vec_val = { val1,val2 };
//	Connecting* c1 = new Connecting;
//	Connecting* c2 = new Connecting;
//	std::unordered_set<Connecting*>ip = { c1 };
//	std::unordered_set<Connecting*>op = { c2 };
//	Functioned<bool> funced(bfunc,ip,op);
//	Function<bool>* func = funced.function();
//	EXPECT_EQ(func->evaluate(vec_val),0);
//}
//
////Functioned();
////Function<T>* function() const;
//TEST(FunctionedConstructorTest, TEST03) {
//	BooleanFunction* bfunc = new BooleanFunction("or");
//	Value<bool> val1(1), val2(0), val;
//	std::vector<Value<bool>>vec_val = { val1,val2 };
//	Connecting* c1 = new Connecting;
//	Connecting* c2 = new Connecting;
//	std::unordered_set<Connecting*>ip = { c1 };
//	std::unordered_set<Connecting*>op = { c2 };
//	Functioned<bool> funced(bfunc, ip, op);
//	Function<bool>* func = funced.function();
//	EXPECT_EQ(func->evaluate(vec_val), 1);
//}
//
////Functioned();
////Function<T>* function() const;
//TEST(FunctionedConstructorTest, TEST04) {
//	BooleanFunction* bfunc = new BooleanFunction("and");
//	Value<bool> val1(1), val2(0), val;
//	std::vector<Value<bool>>vec_val = { val1,val2 };
//	Connecting* c1 = new Connecting;
//	Connecting* c2 = new Connecting;
//	std::unordered_set<Connecting*>ip = { c1 };
//	std::unordered_set<Connecting*>op = { c2 };
//	Functioned<bool> funced(bfunc, ip, op);
//	Function<bool>* func = funced.function();
//	EXPECT_EQ(func->evaluate(vec_val), 0);
//}
//
////Functioned();
////Function<T>* function() const;
//TEST(FunctionedFunctionTest, TEST01) {
//	BooleanFunction* bfunc = new BooleanFunction("and");
//	BooleanFunction* bfunc1 = new BooleanFunction("or");
//	Value<bool> val1(1), val2(0), val;
//	std::vector<Value<bool>>vec_val = { val1,val2 };
//	Connecting* c1 = new Connecting;
//	Connecting* c2 = new Connecting;
//	std::unordered_set<Connecting*>ip = { c1 };
//	std::unordered_set<Connecting*>op = { c2 };
//	Functioned<bool> funced(bfunc, ip, op);
//	Function<bool>* func = funced.function(bfunc1);
//	EXPECT_EQ(func->evaluate(vec_val), 1);
//}
