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


 //Fault();
TEST(Fault_Constructor_Test, TEST01) {
	//FaultyLine<bool> fl;
	//Value<bool> val(0);
	EXPECT_NO_THROW(Fault<bool> f(););
}

//Fault();
TEST(Fault_Constructor_Test, TEST02) {
	FaultyLine<bool>* fl = new FaultyLine<bool>("Faulty Line 1");
	Value<bool> val(0);
	EXPECT_NO_THROW(Fault<bool>f (fl, val););
}

//Fault(const Fault<_primitive>& _fault);
TEST(Fault_Operators_Test, TEST01) {
	FaultyLine<bool>* fl1 = new FaultyLine<bool>("Faulty Line 1");
	FaultyLine<bool>* fl2 = new FaultyLine<bool>("Faulty Line 2");
	Value<bool> val(0);
	Fault<bool>f1 (fl1, val);
	Fault<bool> f2(f1);
	EXPECT_EQ(f1.value(),f2.value());
}

//Fault<_primitive> operator = (const Fault<_primitive> _fault) ;
TEST(Fault_Operators_Test, TEST02) {
	FaultyLine<bool>* fl1 = new FaultyLine<bool>("Faulty Line 1");
	FaultyLine<bool>* fl2 = new FaultyLine<bool>("Faulty Line 2");
	Value<bool> val(0);
	Fault<bool>f1 (fl1, val);
	Fault<bool> f2 = f1;
	EXPECT_EQ(f1.value(), f2.value());
}

//bool operator == (const Fault<_primitive>& _other) const;
TEST(Fault_Operators_Test, TEST03) {
	FaultyLine<bool>* fl1 = new FaultyLine<bool>("Faulty Line 1");
	FaultyLine<bool>* fl2 = new FaultyLine<bool>("Faulty Line 2");
	Value<bool> val(0);
	Fault<bool>f1(fl1, val);
	Fault<bool> f2 = f1;
	int flag = 0;
	if (f1 == f2)
		flag = 1;
	EXPECT_EQ(1, flag);
}

//bool operator != (const Fault<_primitive>& _other) const;
TEST(Fault_Operators_Test, TEST04) {
	FaultyLine<bool>* fl1 = new FaultyLine<bool>("Faulty Line 1");
	FaultyLine<bool>* fl2 = new FaultyLine<bool>("Faulty Line 2");
	Value<bool> val1(0);
	Value<bool> val2(1);
	Fault<bool>f1(fl1, val1);
	Fault<bool> f2 (fl2,val1);
	int flag = 0;
	if (f1 != f2)
		flag = 1;
	EXPECT_EQ(1, flag);
}

//bool operator != (const Fault<_primitive>& _other) const;
TEST(Fault_Operators_Test, TEST05) {
	FaultyLine<bool>* fl1 = new FaultyLine<bool>("Faulty Line 1");
	FaultyLine<bool>* fl2 = new FaultyLine<bool>("Faulty Line 2");
	Value<bool> val1(0);
	Value<bool> val2(1);
	Fault<bool>f1(fl1, val1);
	Fault<bool> f2(fl1, val2);
	int flag = 0;
	if (f1 != f2)
		flag = 1;
	EXPECT_EQ(1, flag);
}

//Value<_primitive> value() const;
TEST(Fault_Operators_Test, TEST06) {
	FaultyLine<bool>* fl = new FaultyLine<bool>("Faulty Line 1");
	Value<bool> val(0);
	Value<bool> val_check(0);
	Fault<bool>f(fl, val);
	EXPECT_EQ(val_check, f.value());
}

//go() const;
TEST(Fault_Go_Test, TEST01) {
	FaultyLine<bool>* fl = new FaultyLine<bool>("Faulty Line 1");
	Value<bool> val(0);
	Fault<bool>f(fl, val);
	EXPECT_TRUE(f.go().empty());
}
//Faulty();
TEST(Faulty_Constructor_Test, TEST01) {

	EXPECT_NO_THROW(Faulty<bool> fauly;);
}

//bool isFaultActive(Fault<_primitive> _fault);
TEST(Faulty_Activate_Test, TEST01) {

	Faulty<bool> faulty;
	FaultyLine<bool>* fl = new FaultyLine<bool>("Faulty Line 1");
	Value<bool> val(0);
	Fault<bool>f(fl, val);
	faulty.activate(f);
	EXPECT_TRUE(faulty.isFaultActive(f));
}

//bool isFaultActive(Fault<_primitive> _fault);
TEST(Faulty_Deactivate_Test, TEST03) {

	Faulty<bool> faulty;
	FaultyLine<bool>* fl = new FaultyLine<bool>("Faulty Line 1");
	Value<bool> val(0);
	Fault<bool>f(fl, val);
	faulty.deactivate(f);
	EXPECT_FALSE(faulty.isFaultActive(f));
}
