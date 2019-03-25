/**
 * @file Fault_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-28
 *
 * @copyright Copyright (c) 2019
 *
 */

#include"gtest/gtest.h"
#include"Fault.h"

class FaultTest : public ::testing::Test {
protected:
	void SetUp() override {
		Parser parser;
		Circuit* c = parser.Parse("c17.bench");
		FaultGenerator<bool> fgen;
		std::unordered_set<Fault<bool>*> faults = fgen.allFaults(c);
		faultUnderTest = *(faults.begin());

	}
	
	FaultyLine<bool>* fl1 = new FaultyLine<bool>("Faulty Line 1");
	FaultyLine<bool>* fl2 = new FaultyLine<bool>("Faulty Line 2");
	Value<bool> val0 = Value<bool>(0);;
	Value<bool> val1 = Value<bool>(1);;
	Fault<bool>* faultUnderTest;
	Fault<bool> f1 = Fault<bool>(fl1, val0);
	int flag = 0;
};

TEST_F(FaultTest, Constructors) {
	//FaultyLine<bool> fl;
	//Value<bool> val(0);
	EXPECT_NO_THROW(Fault<bool> f());
	EXPECT_NO_THROW(Fault<bool> f(fl1, val0));
	Fault<bool> f2(f1);
	EXPECT_EQ(f1.value(), f2.value()); //Copy constructor

}

TEST_F(FaultTest, Overwritten_Operators) {
	Fault<bool>f2 = f1;
	EXPECT_EQ(f1.value(), f2.value()); //Assign (copy) constructor
	EXPECT_EQ(f1,f2); //Equal constructor
	f2 = Fault<bool>(fl1, val1);
	EXPECT_NE(f1, f2);  //Not equal constructor
}

//value();
TEST_F(FaultTest, value) {
	EXPECT_EQ(f1.value(), val0);
}

//go() const;
TEST_F(FaultTest, go) {
	EXPECT_NO_THROW(faultUnderTest->go());
}

class FaultyTest : public ::testing::Test {
protected:
	void SetUp() override {
	}

	FaultyLine<bool>* fl = new FaultyLine<bool>("Faulty Line 1");
	Fault<bool>* f = new Fault<bool>(fl, Value<bool>(0));
};


//Faulty();
TEST_F(FaultyTest, ConstructorsTests) {
	EXPECT_NO_THROW(Faulty<bool> fauly);
}

//Private Functions cannot be tested
//bool isFaultActive(Fault<_primitive> _fault);
//TEST_F(FaultyTest, activate_deactivate) {
//	fl->activate(f);
//	EXPECT_TRUE(fl->isFaultActive(f));
//	fl->deactivate(f);
//	EXPECT_FALSE(fl->isFaultActive(f));
//}
