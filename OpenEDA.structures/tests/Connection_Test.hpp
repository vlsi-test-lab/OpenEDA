/**
 * @file Connection_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2018-12-20
 *
 * @copyright Copyright (c) 2018
 *
 */

#include"gtest/gtest.h"
#include"Connection.h"
#include<vector>
#include<algorithm>
#include <unordered_set>


//Connecting()
TEST(Connecting_Test_Constructor, Connecting_Test_Constructor_01) {
	EXPECT_NO_THROW(Connecting a;);
}

// Connecting(std::unordered_set<Connecting*> _inputs,std::unordered_set<Connecting*> _outputs)
TEST(Connecting_Test_Constructor, Connecting_Test_Constructor_02) {
	Connecting* c1 = new Connecting;
	Connecting* c2 = new Connecting;
	std::unordered_set<Connecting*> a, b;
	a = { c1 };
	b = { c2 };
	EXPECT_NO_THROW(Connecting* p = new Connecting(a, b););
}

//virtual std::unordered_set<Connecting*> inputs() const;
TEST(Connecting_Test_IO, Connecting_Test_INPUTS_01) {
	Connecting* c1 = new Connecting;
	Connecting* c2 = new Connecting;
	std::unordered_set<Connecting*> a, b, a_check;
	a = { c1 };
	b = { c2 };
	Connecting* p = new Connecting(a, b);
	a_check = p->inputs();
	EXPECT_TRUE(std::is_permutation(a.begin(), a.end(), a_check.begin()));
}

//virtual std::unordered_set<Connecting*> outputs() const;
TEST(Connecting_Test_IO, Connecting_Test_OUTPUTS_01) {
	Connecting* c1 = new Connecting;
	Connecting* c2 = new Connecting;
	std::unordered_set<Connecting*> a, b, b_check;
	a = { c1 };
	b = { c2 };
	Connecting* p = new Connecting(a, b);
	b_check = p->outputs();
	EXPECT_TRUE(std::is_permutation(b_check.begin(), b_check.end(), b.begin()));

}

//void Connecting::removeInput(Connecting * _rmv)
TEST(Connecting_Test_IO, Connecting_Test_REMOVEIP_01) {
	Connecting* c1 = new Connecting;
	Connecting* c2 = new Connecting;
	std::unordered_set<Connecting*> a, b, a_check;
	a = { c1 };
	b = { c2 };
	Connecting* p = new Connecting(a, b);
	EXPECT_NO_THROW(p->removeInput(c1););

}

//void Connecting::removeInput(Connecting * _rmv)
TEST(Connecting_Test_IO, Connecting_Test_REMOVEIP_02) {
	Connecting* c1 = new Connecting;
	Connecting* c2 = new Connecting;
	std::unordered_set<Connecting*> a, b, a_check;
	a = { c1 };
	b = { c2 };
	Connecting* p = new Connecting(a, b);
	p->removeInput(c1);
	a_check = p->inputs();
	EXPECT_NE(a_check,a);

}

//void Connecting::removeInput(Connecting * _rmv)
TEST(Connecting_Test_IO, Connecting_Test_REMOVEIP_03) {
	Connecting* c1 = new Connecting;
	Connecting* c2 = new Connecting;
	Connecting* c3 = new Connecting;
	std::unordered_set<Connecting*> a, b, a_check;
	a = { c1 };
	b = { c2 };
	Connecting* p = new Connecting(a, b);
	EXPECT_ANY_THROW(p->removeInput(c3););

}

//void Connecting::removeOutput(Connecting * _rmv)
TEST(Connecting_Test_IO, Connecting_Test_REMOVEOP_01) {
	Connecting* c1 = new Connecting;
	Connecting* c2 = new Connecting;
	std::unordered_set<Connecting*> a, b, a_check;
	a = { c1 };
	b = { c2 };
	Connecting* p = new Connecting(a, b);
	EXPECT_NO_THROW(p->removeOutput(c2););

}

//void Connecting::removeOutput(Connecting * _rmv)
TEST(Connecting_Test_IO, Connecting_Test_REMOVEOP_02) {
	Connecting* c1 = new Connecting;
	Connecting* c2 = new Connecting;
	std::unordered_set<Connecting*> a, b, a_check;
	a = { c1 };
	b = { c2 };
	Connecting* p = new Connecting(a, b);
	p->removeOutput(c2);
	a_check = p->outputs();
	EXPECT_NE(b,a_check);
}

//void Connecting::removeOutput(Connecting * _rmv)
TEST(Connecting_Test_IO, Connecting_Test_REMOVEOP_03) {
	Connecting* c1 = new Connecting;
	Connecting* c2 = new Connecting;
	Connecting* c3 = new Connecting;
	std::unordered_set<Connecting*> a, b, a_check;
	a = { c1 };
	b = { c2 };
	Connecting* p = new Connecting(a, b);
	EXPECT_ANY_THROW(p->removeOutput(c3););

}

//virtual void addOutput(Connecting* _add);
TEST(Connecting_Test_IO, Connecting_Test_ADDOP_01) {
	Connecting* c1 = new Connecting;
	Connecting* c2 = new Connecting;
	Connecting* c3 = new Connecting;
	std::unordered_set<Connecting*> a, b, c, b_check;
	a = { c1 };
	b = { c2 };
	c = { c2, c3 };
	Connecting* p = new Connecting(a, b);
	p->addOutput(c3);
	b_check = p->outputs();
	ASSERT_TRUE(std::is_permutation(b_check.begin(), b_check.end(), c.begin()));
}

//virtual void addInput(Connecting* _add);
TEST(Connecting_Test_IO, Connecting_Test_ADDIP_01) {
	Connecting* c1 = new Connecting;
	Connecting* c2 = new Connecting;
	Connecting* c3 = new Connecting;
	std::unordered_set<Connecting*> a, b, c, a_check;
	a = { c1 };
	b = { c2 };
	c = { c1,c3 };
	Connecting* p = new Connecting(a, b);
	p->addInput(c3);
	a_check = p->inputs();
	EXPECT_TRUE(std::is_permutation(c.begin(), c.end(), a_check.begin()));
}

//Connection();
TEST(Connection_Test_Constructor, Connection_Test_Constructor_01) {
	EXPECT_ANY_THROW(Connection a;);
}

//Connection(Connecting * _input, Connecting * _output);
TEST(Connection_Test_Constructor, Connection_Test_Constructor_02) {
	EXPECT_ANY_THROW(Connection* a = new Connection(nullptr, nullptr););
}

//Connection(Connecting * _input, Connecting * _output);
TEST(Connection_Test_Constructor, Connection_Test_Constructor_03) {
	Connecting* c1 = new Connecting;
	Connecting* c2 = new Connecting;
	EXPECT_NO_THROW(Connection* a = new Connection(c1, c2););
}

//Connection(Connecting * _input, Connecting * _output);
//Connecting* input() const;
//Connecting* output() const;
TEST(Connection_Test_Constructor, Connection_Test_Constructor_04) {
	Connecting* c1 = new Connecting;
	Connecting* c2 = new Connecting;
	Connection* a = new Connection(c1, c2);
	EXPECT_EQ(c1, a->input());
	EXPECT_EQ(c2, a->output());
}
