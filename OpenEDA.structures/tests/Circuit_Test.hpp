/**
 * @file Circuit_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-12-27
 *
 * @copyright Copyright (c) 2018
 *
 */

#include"gtest/gtest.h"
#include"Circuit.h"
#include<unordered_set>


//Circuit(std::unordered_set<Levelized*> _nodes, std::unordered_set <Levelized*> _inputs, std::unordered_set<Levelized*> _outputs);
//std::unordered_set<Levelized*> nodes() const;
//std::unordered_set<Levelized*> pis() const;
//std::unordered_set<Levelized*> pos() const;
TEST(Circuit_Constructor_Test, TEST01) {
	std::unordered_set<Levelized*> empty = {};
	Levelized* l1 = new Levelized();
	Levelized* l2 = new Levelized();
	Levelized* l3 = new Levelized();
	Levelized* l4 = new Levelized();
	Levelized* l5 = new Levelized();
	Levelized* l6 = new Levelized();
	Levelized* l7 = new Levelized();
	std::unordered_set<Levelized*> n1_in = {l1,l2};
	std::unordered_set<Levelized*> n1_out = { l3 };
	std::unordered_set<Levelized*> n2_in = { l3,l4 };
	std::unordered_set<Levelized*> n2_out = { l5 };
	std::unordered_set<Levelized*> n3_in = { l5,l6 };
	std::unordered_set<Levelized*> n3_out = { l7 };
	Levelized* n1 = new Levelized(n1_in,n1_out);
	Levelized* n2 = new Levelized(n2_in, n2_out);
	Levelized* n3 = new Levelized(n3_in, n3_out);
	std::unordered_set<Levelized*> nodes = { n1 };
	std::unordered_set<Levelized*> pis = { n2 };
	std::unordered_set<Levelized*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	EXPECT_TRUE(std::is_permutation(nodes.begin(),nodes.end(),c->nodes().begin()));
	EXPECT_TRUE(std::is_permutation(pis.begin(), pis.end(), c->pis().begin()));
	EXPECT_TRUE(std::is_permutation(pos.begin(), pos.end(), c->pos().begin()));
}

//Circuit(std::unordered_set<Levelized*> _nodes, std::unordered_set <Levelized*> _inputs, std::unordered_set<Levelized*> _outputs);
//std::unordered_set<Levelized*> nodes() const;
//std::unordered_set<Levelized*> pis() const;
//std::unordered_set<Levelized*> pos() const;
TEST(Circuit_Constructor_Test, TEST02) {
	std::unordered_set<Levelized*> empty = {};
	Levelized* l1 = new Levelized();
	Levelized* l2 = new Levelized();
	Levelized* l3 = new Levelized();
	Levelized* l4 = new Levelized();
	Levelized* l5 = new Levelized();
	Levelized* l6 = new Levelized();
	Levelized* l7 = new Levelized();
	std::unordered_set<Levelized*> n1_in = { l1,l2 };
	std::unordered_set<Levelized*> n1_out = { l3 };
	std::unordered_set<Levelized*> n2_in = { l3,l4 };
	std::unordered_set<Levelized*> n2_out = { l5 };
	std::unordered_set<Levelized*> n3_in = { l5,l6 };
	std::unordered_set<Levelized*> n3_out = { l7 };
	Levelized* n1 = new Levelized(n1_in, n1_out);
	Levelized* n2 = new Levelized(n2_in, n2_out);
	Levelized* n3 = new Levelized(n3_in, n3_out);
	std::unordered_set<Levelized*> nodes = { n1 };
	std::unordered_set<Levelized*> pis = { n2 };
	std::unordered_set<Levelized*> pos = { n3 };
	std::unordered_set<Levelized*> check = { n1,n2,n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	std::unordered_set<Levelized*> real = c->nodes();
	EXPECT_TRUE(std::is_permutation(real.begin(),real.end(),check.begin()));
}

//void addNode(Levelized* _node);
TEST(Circuit_AddNode_Test, TEST01) {
	std::unordered_set<Levelized*> empty = {};
	Levelized* l1 = new Levelized();
	Levelized* l2 = new Levelized();
	Levelized* l3 = new Levelized();
	Levelized* l4 = new Levelized();
	Levelized* l5 = new Levelized();
	Levelized* l6 = new Levelized();
	Levelized* l7 = new Levelized();
	Levelized* l8 = new Levelized();
	Levelized* l9 = new Levelized();
	std::unordered_set<Levelized*> n1_in = { l1,l2 };
	std::unordered_set<Levelized*> n1_out = { l3 };
	std::unordered_set<Levelized*> n2_in = { l3,l4 };
	std::unordered_set<Levelized*> n2_out = { l5 };
	std::unordered_set<Levelized*> n3_in = { l5,l6 };
	std::unordered_set<Levelized*> n3_out = { l7 };
	std::unordered_set<Levelized*> n4_in = { l8,l9 };
	std::unordered_set<Levelized*> n4_out = { l4 };
	Levelized* n1 = new Levelized(n1_in, n1_out);
	Levelized* n2 = new Levelized(n2_in, n2_out);
	Levelized* n3 = new Levelized(n3_in, n3_out);
	Levelized* n4 = new Levelized(n4_in, n4_out);
	std::unordered_set<Levelized*> nodes = { n1 };
	std::unordered_set<Levelized*> pis = { n2 };
	std::unordered_set<Levelized*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	c->addNode(n4);
	std::unordered_set<Levelized*> check = { n4,n1 };
	EXPECT_TRUE(std::is_permutation(check.begin(), check.end(), c->nodes().begin()));
}

//Levelized* removeNode(Levelized* _node);
TEST(Circuit_removeNode_Test, TEST01) {
	std::unordered_set<Levelized*> empty = {};
	Levelized* l1 = new Levelized();
	Levelized* l2 = new Levelized();
	Levelized* l3 = new Levelized();
	Levelized* l4 = new Levelized();
	Levelized* l5 = new Levelized();
	Levelized* l6 = new Levelized();
	Levelized* l7 = new Levelized();
	Levelized* l8 = new Levelized();
	Levelized* l9 = new Levelized();
	std::unordered_set<Levelized*> n1_in = { l1,l2 };
	std::unordered_set<Levelized*> n1_out = { l3 };
	std::unordered_set<Levelized*> n2_in = { l3,l4 };
	std::unordered_set<Levelized*> n2_out = { l5 };
	std::unordered_set<Levelized*> n3_in = { l5,l6 };
	std::unordered_set<Levelized*> n3_out = { l7 };
	std::unordered_set<Levelized*> n4_in = { l8,l9 };
	std::unordered_set<Levelized*> n4_out = { l4 };
	Levelized* n1 = new Levelized(n1_in, n1_out);
	Levelized* n2 = new Levelized(n2_in, n2_out);
	Levelized* n3 = new Levelized(n3_in, n3_out);
	Levelized* n4 = new Levelized(n4_in, n4_out);
	std::unordered_set<Levelized*> nodes = { n1 };
	std::unordered_set<Levelized*> pis = { n2 };
	std::unordered_set<Levelized*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	EXPECT_ANY_THROW(c->removeNode(n4););
}

//Levelized* removeNode(Levelized* _node);
TEST(Circuit_removeNode_Test, TEST02) {
	std::unordered_set<Levelized*> empty = {};
	Levelized* l1 = new Levelized();
	Levelized* l2 = new Levelized();
	Levelized* l3 = new Levelized();
	Levelized* l4 = new Levelized();
	Levelized* l5 = new Levelized();
	Levelized* l6 = new Levelized();
	Levelized* l7 = new Levelized();
	Levelized* l8 = new Levelized();
	Levelized* l9 = new Levelized();
	std::unordered_set<Levelized*> n1_in = { l1,l2 };
	std::unordered_set<Levelized*> n1_out = { l3 };
	std::unordered_set<Levelized*> n2_in = { l3,l4 };
	std::unordered_set<Levelized*> n2_out = { l5 };
	std::unordered_set<Levelized*> n3_in = { l5,l6 };
	std::unordered_set<Levelized*> n3_out = { l7 };
	std::unordered_set<Levelized*> n4_in = { l8,l9 };
	std::unordered_set<Levelized*> n4_out = { l4 };
	Levelized* n1 = new Levelized(n1_in, n1_out);
	Levelized* n2 = new Levelized(n2_in, n2_out);
	Levelized* n3 = new Levelized(n3_in, n3_out);
	Levelized* n4 = new Levelized(n4_in, n4_out);
	std::unordered_set<Levelized*> nodes = { n1 };
	std::unordered_set<Levelized*> pis = { n2 };
	std::unordered_set<Levelized*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	c->removeNode(n1);
	EXPECT_TRUE(c->nodes().empty());
}

//void addPI(Levelized* _node);
TEST(Circuit_addPI_Test, TEST01) {
	std::unordered_set<Levelized*> empty = {};
	Levelized* l1 = new Levelized();
	Levelized* l2 = new Levelized();
	Levelized* l3 = new Levelized();
	Levelized* l4 = new Levelized();
	Levelized* l5 = new Levelized();
	Levelized* l6 = new Levelized();
	Levelized* l7 = new Levelized();
	Levelized* l8 = new Levelized();
	Levelized* l9 = new Levelized();
	std::unordered_set<Levelized*> n1_in = { l1,l2 };
	std::unordered_set<Levelized*> n1_out = { l3 };
	std::unordered_set<Levelized*> n2_in = { l3,l4 };
	std::unordered_set<Levelized*> n2_out = { l5 };
	std::unordered_set<Levelized*> n3_in = { l5,l6 };
	std::unordered_set<Levelized*> n3_out = { l7 };
	std::unordered_set<Levelized*> n4_in = { l8,l9 };
	std::unordered_set<Levelized*> n4_out = { l4 };
	Levelized* n1 = new Levelized(n1_in, n1_out);
	Levelized* n2 = new Levelized(n2_in, n2_out);
	Levelized* n3 = new Levelized(n3_in, n3_out);
	Levelized* n4 = new Levelized(n4_in, n4_out);
	std::unordered_set<Levelized*> nodes = { n1 };
	std::unordered_set<Levelized*> pis = { n2 };
	std::unordered_set<Levelized*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	c->addPI(n4);
	std::unordered_set<Levelized*> check = { n4,n2 };
	EXPECT_TRUE(std::is_permutation(check.begin(), check.end(), c->pis().begin()));
}

//void addPO(Levelized* _node);
TEST(Circuit_addPO_Test, TEST01) {
	std::unordered_set<Levelized*> empty = {};
	Levelized* l1 = new Levelized();
	Levelized* l2 = new Levelized();
	Levelized* l3 = new Levelized();
	Levelized* l4 = new Levelized();
	Levelized* l5 = new Levelized();
	Levelized* l6 = new Levelized();
	Levelized* l7 = new Levelized();
	Levelized* l8 = new Levelized();
	Levelized* l9 = new Levelized();
	std::unordered_set<Levelized*> n1_in = { l1,l2 };
	std::unordered_set<Levelized*> n1_out = { l3 };
	std::unordered_set<Levelized*> n2_in = { l3,l4 };
	std::unordered_set<Levelized*> n2_out = { l5 };
	std::unordered_set<Levelized*> n3_in = { l5,l6 };
	std::unordered_set<Levelized*> n3_out = { l7 };
	std::unordered_set<Levelized*> n4_in = { l8,l9 };
	std::unordered_set<Levelized*> n4_out = { l4 };
	Levelized* n1 = new Levelized(n1_in, n1_out);
	Levelized* n2 = new Levelized(n2_in, n2_out);
	Levelized* n3 = new Levelized(n3_in, n3_out);
	Levelized* n4 = new Levelized(n4_in, n4_out);
	std::unordered_set<Levelized*> nodes = { n1 };
	std::unordered_set<Levelized*> pis = { n2 };
	std::unordered_set<Levelized*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	c->addPO(n4);
	std::unordered_set<Levelized*> check = { n4,n3 };
	EXPECT_TRUE(std::is_permutation(check.begin(), check.end(), c->pos().begin()));
}

//Levelized* removePI(Levelized* _node);
TEST(Circuit_removePI_Test, TEST01) {
	std::unordered_set<Levelized*> empty = {};
	Levelized* l1 = new Levelized();
	Levelized* l2 = new Levelized();
	Levelized* l3 = new Levelized();
	Levelized* l4 = new Levelized();
	Levelized* l5 = new Levelized();
	Levelized* l6 = new Levelized();
	Levelized* l7 = new Levelized();
	Levelized* l8 = new Levelized();
	Levelized* l9 = new Levelized();
	std::unordered_set<Levelized*> n1_in = { l1,l2 };
	std::unordered_set<Levelized*> n1_out = { l3 };
	std::unordered_set<Levelized*> n2_in = { l3,l4 };
	std::unordered_set<Levelized*> n2_out = { l5 };
	std::unordered_set<Levelized*> n3_in = { l5,l6 };
	std::unordered_set<Levelized*> n3_out = { l7 };
	std::unordered_set<Levelized*> n4_in = { l8,l9 };
	std::unordered_set<Levelized*> n4_out = { l4 };
	Levelized* n1 = new Levelized(n1_in, n1_out);
	Levelized* n2 = new Levelized(n2_in, n2_out);
	Levelized* n3 = new Levelized(n3_in, n3_out);
	Levelized* n4 = new Levelized(n4_in, n4_out);
	std::unordered_set<Levelized*> nodes = { n1 };
	std::unordered_set<Levelized*> pis = { n2 };
	std::unordered_set<Levelized*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	ASSERT_NO_THROW(c->removePI(n2););
	EXPECT_TRUE(c->pis().empty());
}

//Levelized* removePI(Levelized* _node);
TEST(Circuit_removePI_Test, TEST02) {
	std::unordered_set<Levelized*> empty = {};
	Levelized* l1 = new Levelized();
	Levelized* l2 = new Levelized();
	Levelized* l3 = new Levelized();
	Levelized* l4 = new Levelized();
	Levelized* l5 = new Levelized();
	Levelized* l6 = new Levelized();
	Levelized* l7 = new Levelized();
	Levelized* l8 = new Levelized();
	Levelized* l9 = new Levelized();
	std::unordered_set<Levelized*> n1_in = { l1,l2 };
	std::unordered_set<Levelized*> n1_out = { l3 };
	std::unordered_set<Levelized*> n2_in = { l3,l4 };
	std::unordered_set<Levelized*> n2_out = { l5 };
	std::unordered_set<Levelized*> n3_in = { l5,l6 };
	std::unordered_set<Levelized*> n3_out = { l7 };
	std::unordered_set<Levelized*> n4_in = { l8,l9 };
	std::unordered_set<Levelized*> n4_out = { l4 };
	Levelized* n1 = new Levelized(n1_in, n1_out);
	Levelized* n2 = new Levelized(n2_in, n2_out);
	Levelized* n3 = new Levelized(n3_in, n3_out);
	Levelized* n4 = new Levelized(n4_in, n4_out);
	std::unordered_set<Levelized*> nodes = { n1 };
	std::unordered_set<Levelized*> pis = { n2 };
	std::unordered_set<Levelized*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	EXPECT_ANY_THROW(c->removePI(n4););
}

//Levelized* removePI(Levelized* _node);
TEST(Circuit_removePI_Test, TEST03) {
	std::unordered_set<Levelized*> empty = {};
	Levelized* l1 = new Levelized();
	Levelized* l2 = new Levelized();
	Levelized* l3 = new Levelized();
	Levelized* l4 = new Levelized();
	Levelized* l5 = new Levelized();
	Levelized* l6 = new Levelized();
	Levelized* l7 = new Levelized();
	Levelized* l8 = new Levelized();
	Levelized* l9 = new Levelized();
	std::unordered_set<Levelized*> n1_in = { l1,l2 };
	std::unordered_set<Levelized*> n1_out = { l3 };
	std::unordered_set<Levelized*> n2_in = { l3,l4 };
	std::unordered_set<Levelized*> n2_out = { l5 };
	std::unordered_set<Levelized*> n3_in = { l5,l6 };
	std::unordered_set<Levelized*> n3_out = { l7 };
	std::unordered_set<Levelized*> n4_in = { l8,l9 };
	std::unordered_set<Levelized*> n4_out = { l4 };
	Levelized* n1 = new Levelized(n1_in, n1_out);
	Levelized* n2 = new Levelized(n2_in, n2_out);
	Levelized* n3 = new Levelized(n3_in, n3_out);
	Levelized* n4 = new Levelized(n4_in, n4_out);
	std::unordered_set<Levelized*> nodes = { n1 };
	std::unordered_set<Levelized*> pis = { n2 };
	std::unordered_set<Levelized*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	EXPECT_ANY_THROW(c->removePI(n1););
}

//Levelized* removePO(Levelized* _node);
TEST(Circuit_removePO_Test, TEST01) {
	std::unordered_set<Levelized*> empty = {};
	Levelized* l1 = new Levelized();
	Levelized* l2 = new Levelized();
	Levelized* l3 = new Levelized();
	Levelized* l4 = new Levelized();
	Levelized* l5 = new Levelized();
	Levelized* l6 = new Levelized();
	Levelized* l7 = new Levelized();
	Levelized* l8 = new Levelized();
	Levelized* l9 = new Levelized();
	std::unordered_set<Levelized*> n1_in = { l1,l2 };
	std::unordered_set<Levelized*> n1_out = { l3 };
	std::unordered_set<Levelized*> n2_in = { l3,l4 };
	std::unordered_set<Levelized*> n2_out = { l5 };
	std::unordered_set<Levelized*> n3_in = { l5,l6 };
	std::unordered_set<Levelized*> n3_out = { l7 };
	std::unordered_set<Levelized*> n4_in = { l8,l9 };
	std::unordered_set<Levelized*> n4_out = { l4 };
	Levelized* n1 = new Levelized(n1_in, n1_out);
	Levelized* n2 = new Levelized(n2_in, n2_out);
	Levelized* n3 = new Levelized(n3_in, n3_out);
	Levelized* n4 = new Levelized(n4_in, n4_out);
	std::unordered_set<Levelized*> nodes = { n1 };
	std::unordered_set<Levelized*> pis = { n2 };
	std::unordered_set<Levelized*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	ASSERT_NO_THROW(c->removePO(n3););
	EXPECT_TRUE(c->pos().empty());
}

//Levelized* removePO(Levelized* _node);
TEST(Circuit_removePO_Test, TEST02) {
	std::unordered_set<Levelized*> empty = {};
	Levelized* l1 = new Levelized();
	Levelized* l2 = new Levelized();
	Levelized* l3 = new Levelized();
	Levelized* l4 = new Levelized();
	Levelized* l5 = new Levelized();
	Levelized* l6 = new Levelized();
	Levelized* l7 = new Levelized();
	Levelized* l8 = new Levelized();
	Levelized* l9 = new Levelized();
	std::unordered_set<Levelized*> n1_in = { l1,l2 };
	std::unordered_set<Levelized*> n1_out = { l3 };
	std::unordered_set<Levelized*> n2_in = { l3,l4 };
	std::unordered_set<Levelized*> n2_out = { l5 };
	std::unordered_set<Levelized*> n3_in = { l5,l6 };
	std::unordered_set<Levelized*> n3_out = { l7 };
	std::unordered_set<Levelized*> n4_in = { l8,l9 };
	std::unordered_set<Levelized*> n4_out = { l4 };
	Levelized* n1 = new Levelized(n1_in, n1_out);
	Levelized* n2 = new Levelized(n2_in, n2_out);
	Levelized* n3 = new Levelized(n3_in, n3_out);
	Levelized* n4 = new Levelized(n4_in, n4_out);
	std::unordered_set<Levelized*> nodes = { n1 };
	std::unordered_set<Levelized*> pis = { n2 };
	std::unordered_set<Levelized*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	EXPECT_ANY_THROW(c->removePO(n4););
}

//Levelized* removePO(Levelized* _node);
TEST(Circuit_removePO_Test, TEST03) {
	std::unordered_set<Levelized*> empty = {};
	Levelized* l1 = new Levelized();
	Levelized* l2 = new Levelized();
	Levelized* l3 = new Levelized();
	Levelized* l4 = new Levelized();
	Levelized* l5 = new Levelized();
	Levelized* l6 = new Levelized();
	Levelized* l7 = new Levelized();
	Levelized* l8 = new Levelized();
	Levelized* l9 = new Levelized();
	std::unordered_set<Levelized*> n1_in = { l1,l2 };
	std::unordered_set<Levelized*> n1_out = { l3 };
	std::unordered_set<Levelized*> n2_in = { l3,l4 };
	std::unordered_set<Levelized*> n2_out = { l5 };
	std::unordered_set<Levelized*> n3_in = { l5,l6 };
	std::unordered_set<Levelized*> n3_out = { l7 };
	std::unordered_set<Levelized*> n4_in = { l8,l9 };
	std::unordered_set<Levelized*> n4_out = { l4 };
	Levelized* n1 = new Levelized(n1_in, n1_out);
	Levelized* n2 = new Levelized(n2_in, n2_out);
	Levelized* n3 = new Levelized(n3_in, n3_out);
	Levelized* n4 = new Levelized(n4_in, n4_out);
	std::unordered_set<Levelized*> nodes = { n1 };
	std::unordered_set<Levelized*> pis = { n2 };
	std::unordered_set<Levelized*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	EXPECT_ANY_THROW(c->removePO(n2););
}
    

