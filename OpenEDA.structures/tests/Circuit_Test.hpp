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
#include"Node.h"
#include"Circuit.h"
#include<unordered_set>


//Circuit(std::unordered_set<Node*> _nodes, std::unordered_set <Node*> _inputs, std::unordered_set<Node*> _outputs);
//std::unordered_set<Node*> nodes() const;
//std::unordered_set<Node*> pis() const;
//std::unordered_set<Node*> pos() const;
TEST(Circuit_Constructor_Test, TEST01) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l6 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l7 = new Line(nullptr, nullptr, nullptr, empty);
	std::unordered_set<Line*> n1_in = {l1,l2};
	std::unordered_set<Line*> n1_out = { l3 };
	std::unordered_set<Line*> n2_in = { l3,l4 };
	std::unordered_set<Line*> n2_out = { l5 };
	std::unordered_set<Line*> n3_in = { l5,l6 };
	std::unordered_set<Line*> n3_out = { l7 };
	Node* n1 = new Node(n1_in,n1_out);
	Node* n2 = new Node(n2_in, n2_out);
	Node* n3 = new Node(n3_in, n3_out);
	std::unordered_set<Node*> nodes = { n1 };
	std::unordered_set<Node*> pis = { n2 };
	std::unordered_set<Node*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	EXPECT_TRUE(std::is_permutation(nodes.begin(),nodes.end(),c->nodes().begin()));
	EXPECT_TRUE(std::is_permutation(pis.begin(), pis.end(), c->pis().begin()));
	EXPECT_TRUE(std::is_permutation(pos.begin(), pos.end(), c->pos().begin()));
}

//Circuit(std::unordered_set<Node*> _nodes, std::unordered_set <Node*> _inputs, std::unordered_set<Node*> _outputs);
//std::unordered_set<Node*> nodes() const;
//std::unordered_set<Node*> pis() const;
//std::unordered_set<Node*> pos() const;
TEST(Circuit_Constructor_Test, TEST02) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l6 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l7 = new Line(nullptr, nullptr, nullptr, empty);
	std::unordered_set<Line*> n1_in = { l1,l2 };
	std::unordered_set<Line*> n1_out = { l3 };
	std::unordered_set<Line*> n2_in = { l3,l4 };
	std::unordered_set<Line*> n2_out = { l5 };
	std::unordered_set<Line*> n3_in = { l5,l6 };
	std::unordered_set<Line*> n3_out = { l7 };
	Node* n1 = new Node(n1_in, n1_out);
	Node* n2 = new Node(n2_in, n2_out);
	Node* n3 = new Node(n3_in, n3_out);
	std::unordered_set<Node*> nodes = { n1 };
	std::unordered_set<Node*> pis = { n2 };
	std::unordered_set<Node*> pos = { n3 };
	std::unordered_set<Node*> check = { n1,n2,n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	std::unordered_set<Node*> real = c->nodes();
	EXPECT_TRUE(std::is_permutation(real.begin(),real.end(),check.begin()));
}

//void addNode(Node* _node);
TEST(Circuit_AddNode_Test, TEST01) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l6 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l7 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l8 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l9 = new Line(nullptr, nullptr, nullptr, empty);
	std::unordered_set<Line*> n1_in = { l1,l2 };
	std::unordered_set<Line*> n1_out = { l3 };
	std::unordered_set<Line*> n2_in = { l3,l4 };
	std::unordered_set<Line*> n2_out = { l5 };
	std::unordered_set<Line*> n3_in = { l5,l6 };
	std::unordered_set<Line*> n3_out = { l7 };
	std::unordered_set<Line*> n4_in = { l8,l9 };
	std::unordered_set<Line*> n4_out = { l4 };
	Node* n1 = new Node(n1_in, n1_out);
	Node* n2 = new Node(n2_in, n2_out);
	Node* n3 = new Node(n3_in, n3_out);
	Node* n4 = new Node(n4_in, n4_out);
	std::unordered_set<Node*> nodes = { n1 };
	std::unordered_set<Node*> pis = { n2 };
	std::unordered_set<Node*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	c->addNode(n4);
	std::unordered_set<Node*> check = { n4,n1 };
	EXPECT_TRUE(std::is_permutation(check.begin(), check.end(), c->nodes().begin()));
}

//Node* removeNode(Node* _node);
TEST(Circuit_removeNode_Test, TEST01) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l6 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l7 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l8 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l9 = new Line(nullptr, nullptr, nullptr, empty);
	std::unordered_set<Line*> n1_in = { l1,l2 };
	std::unordered_set<Line*> n1_out = { l3 };
	std::unordered_set<Line*> n2_in = { l3,l4 };
	std::unordered_set<Line*> n2_out = { l5 };
	std::unordered_set<Line*> n3_in = { l5,l6 };
	std::unordered_set<Line*> n3_out = { l7 };
	std::unordered_set<Line*> n4_in = { l8,l9 };
	std::unordered_set<Line*> n4_out = { l4 };
	Node* n1 = new Node(n1_in, n1_out);
	Node* n2 = new Node(n2_in, n2_out);
	Node* n3 = new Node(n3_in, n3_out);
	Node* n4 = new Node(n4_in, n4_out);
	std::unordered_set<Node*> nodes = { n1 };
	std::unordered_set<Node*> pis = { n2 };
	std::unordered_set<Node*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	EXPECT_ANY_THROW(c->removeNode(n4););
}

//Node* removeNode(Node* _node);
TEST(Circuit_removeNode_Test, TEST02) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l6 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l7 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l8 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l9 = new Line(nullptr, nullptr, nullptr, empty);
	std::unordered_set<Line*> n1_in = { l1,l2 };
	std::unordered_set<Line*> n1_out = { l3 };
	std::unordered_set<Line*> n2_in = { l3,l4 };
	std::unordered_set<Line*> n2_out = { l5 };
	std::unordered_set<Line*> n3_in = { l5,l6 };
	std::unordered_set<Line*> n3_out = { l7 };
	std::unordered_set<Line*> n4_in = { l8,l9 };
	std::unordered_set<Line*> n4_out = { l4 };
	Node* n1 = new Node(n1_in, n1_out);
	Node* n2 = new Node(n2_in, n2_out);
	Node* n3 = new Node(n3_in, n3_out);
	Node* n4 = new Node(n4_in, n4_out);
	std::unordered_set<Node*> nodes = { n1 };
	std::unordered_set<Node*> pis = { n2 };
	std::unordered_set<Node*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	c->removeNode(n1);
	EXPECT_TRUE(c->nodes().empty());
}

//void addPI(Node* _node);
TEST(Circuit_addPI_Test, TEST01) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l6 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l7 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l8 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l9 = new Line(nullptr, nullptr, nullptr, empty);
	std::unordered_set<Line*> n1_in = { l1,l2 };
	std::unordered_set<Line*> n1_out = { l3 };
	std::unordered_set<Line*> n2_in = { l3,l4 };
	std::unordered_set<Line*> n2_out = { l5 };
	std::unordered_set<Line*> n3_in = { l5,l6 };
	std::unordered_set<Line*> n3_out = { l7 };
	std::unordered_set<Line*> n4_in = { l8,l9 };
	std::unordered_set<Line*> n4_out = { l4 };
	Node* n1 = new Node(n1_in, n1_out);
	Node* n2 = new Node(n2_in, n2_out);
	Node* n3 = new Node(n3_in, n3_out);
	Node* n4 = new Node(n4_in, n4_out);
	std::unordered_set<Node*> nodes = { n1 };
	std::unordered_set<Node*> pis = { n2 };
	std::unordered_set<Node*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	c->addPI(n4);
	std::unordered_set<Node*> check = { n4,n2 };
	EXPECT_TRUE(std::is_permutation(check.begin(), check.end(), c->pis().begin()));
}

//void addPO(Node* _node);
TEST(Circuit_addPO_Test, TEST01) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l6 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l7 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l8 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l9 = new Line(nullptr, nullptr, nullptr, empty);
	std::unordered_set<Line*> n1_in = { l1,l2 };
	std::unordered_set<Line*> n1_out = { l3 };
	std::unordered_set<Line*> n2_in = { l3,l4 };
	std::unordered_set<Line*> n2_out = { l5 };
	std::unordered_set<Line*> n3_in = { l5,l6 };
	std::unordered_set<Line*> n3_out = { l7 };
	std::unordered_set<Line*> n4_in = { l8,l9 };
	std::unordered_set<Line*> n4_out = { l4 };
	Node* n1 = new Node(n1_in, n1_out);
	Node* n2 = new Node(n2_in, n2_out);
	Node* n3 = new Node(n3_in, n3_out);
	Node* n4 = new Node(n4_in, n4_out);
	std::unordered_set<Node*> nodes = { n1 };
	std::unordered_set<Node*> pis = { n2 };
	std::unordered_set<Node*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	c->addPO(n4);
	std::unordered_set<Node*> check = { n4,n3 };
	EXPECT_TRUE(std::is_permutation(check.begin(), check.end(), c->pos().begin()));
}

//Node* removePI(Node* _node);
TEST(Circuit_removePI_Test, TEST01) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l6 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l7 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l8 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l9 = new Line(nullptr, nullptr, nullptr, empty);
	std::unordered_set<Line*> n1_in = { l1,l2 };
	std::unordered_set<Line*> n1_out = { l3 };
	std::unordered_set<Line*> n2_in = { l3,l4 };
	std::unordered_set<Line*> n2_out = { l5 };
	std::unordered_set<Line*> n3_in = { l5,l6 };
	std::unordered_set<Line*> n3_out = { l7 };
	std::unordered_set<Line*> n4_in = { l8,l9 };
	std::unordered_set<Line*> n4_out = { l4 };
	Node* n1 = new Node(n1_in, n1_out);
	Node* n2 = new Node(n2_in, n2_out);
	Node* n3 = new Node(n3_in, n3_out);
	Node* n4 = new Node(n4_in, n4_out);
	std::unordered_set<Node*> nodes = { n1 };
	std::unordered_set<Node*> pis = { n2 };
	std::unordered_set<Node*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	ASSERT_NO_THROW(c->removePI(n2););
	EXPECT_TRUE(c->pis().empty());
}

//Node* removePI(Node* _node);
TEST(Circuit_removePI_Test, TEST02) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l6 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l7 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l8 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l9 = new Line(nullptr, nullptr, nullptr, empty);
	std::unordered_set<Line*> n1_in = { l1,l2 };
	std::unordered_set<Line*> n1_out = { l3 };
	std::unordered_set<Line*> n2_in = { l3,l4 };
	std::unordered_set<Line*> n2_out = { l5 };
	std::unordered_set<Line*> n3_in = { l5,l6 };
	std::unordered_set<Line*> n3_out = { l7 };
	std::unordered_set<Line*> n4_in = { l8,l9 };
	std::unordered_set<Line*> n4_out = { l4 };
	Node* n1 = new Node(n1_in, n1_out);
	Node* n2 = new Node(n2_in, n2_out);
	Node* n3 = new Node(n3_in, n3_out);
	Node* n4 = new Node(n4_in, n4_out);
	std::unordered_set<Node*> nodes = { n1 };
	std::unordered_set<Node*> pis = { n2 };
	std::unordered_set<Node*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	EXPECT_ANY_THROW(c->removePI(n4););
}

//Node* removePI(Node* _node);
TEST(Circuit_removePI_Test, TEST03) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l6 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l7 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l8 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l9 = new Line(nullptr, nullptr, nullptr, empty);
	std::unordered_set<Line*> n1_in = { l1,l2 };
	std::unordered_set<Line*> n1_out = { l3 };
	std::unordered_set<Line*> n2_in = { l3,l4 };
	std::unordered_set<Line*> n2_out = { l5 };
	std::unordered_set<Line*> n3_in = { l5,l6 };
	std::unordered_set<Line*> n3_out = { l7 };
	std::unordered_set<Line*> n4_in = { l8,l9 };
	std::unordered_set<Line*> n4_out = { l4 };
	Node* n1 = new Node(n1_in, n1_out);
	Node* n2 = new Node(n2_in, n2_out);
	Node* n3 = new Node(n3_in, n3_out);
	Node* n4 = new Node(n4_in, n4_out);
	std::unordered_set<Node*> nodes = { n1 };
	std::unordered_set<Node*> pis = { n2 };
	std::unordered_set<Node*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	EXPECT_ANY_THROW(c->removePI(n1););
}

//Node* removePO(Node* _node);
TEST(Circuit_removePO_Test, TEST01) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l6 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l7 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l8 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l9 = new Line(nullptr, nullptr, nullptr, empty);
	std::unordered_set<Line*> n1_in = { l1,l2 };
	std::unordered_set<Line*> n1_out = { l3 };
	std::unordered_set<Line*> n2_in = { l3,l4 };
	std::unordered_set<Line*> n2_out = { l5 };
	std::unordered_set<Line*> n3_in = { l5,l6 };
	std::unordered_set<Line*> n3_out = { l7 };
	std::unordered_set<Line*> n4_in = { l8,l9 };
	std::unordered_set<Line*> n4_out = { l4 };
	Node* n1 = new Node(n1_in, n1_out);
	Node* n2 = new Node(n2_in, n2_out);
	Node* n3 = new Node(n3_in, n3_out);
	Node* n4 = new Node(n4_in, n4_out);
	std::unordered_set<Node*> nodes = { n1 };
	std::unordered_set<Node*> pis = { n2 };
	std::unordered_set<Node*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	ASSERT_NO_THROW(c->removePO(n3););
	EXPECT_TRUE(c->pos().empty());
}

//Node* removePO(Node* _node);
TEST(Circuit_removePO_Test, TEST02) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l6 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l7 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l8 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l9 = new Line(nullptr, nullptr, nullptr, empty);
	std::unordered_set<Line*> n1_in = { l1,l2 };
	std::unordered_set<Line*> n1_out = { l3 };
	std::unordered_set<Line*> n2_in = { l3,l4 };
	std::unordered_set<Line*> n2_out = { l5 };
	std::unordered_set<Line*> n3_in = { l5,l6 };
	std::unordered_set<Line*> n3_out = { l7 };
	std::unordered_set<Line*> n4_in = { l8,l9 };
	std::unordered_set<Line*> n4_out = { l4 };
	Node* n1 = new Node(n1_in, n1_out);
	Node* n2 = new Node(n2_in, n2_out);
	Node* n3 = new Node(n3_in, n3_out);
	Node* n4 = new Node(n4_in, n4_out);
	std::unordered_set<Node*> nodes = { n1 };
	std::unordered_set<Node*> pis = { n2 };
	std::unordered_set<Node*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	EXPECT_ANY_THROW(c->removePO(n4););
}

//Node* removePO(Node* _node);
TEST(Circuit_removePO_Test, TEST03) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l6 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l7 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l8 = new Line(nullptr, nullptr, nullptr, empty);
	Line* l9 = new Line(nullptr, nullptr, nullptr, empty);
	std::unordered_set<Line*> n1_in = { l1,l2 };
	std::unordered_set<Line*> n1_out = { l3 };
	std::unordered_set<Line*> n2_in = { l3,l4 };
	std::unordered_set<Line*> n2_out = { l5 };
	std::unordered_set<Line*> n3_in = { l5,l6 };
	std::unordered_set<Line*> n3_out = { l7 };
	std::unordered_set<Line*> n4_in = { l8,l9 };
	std::unordered_set<Line*> n4_out = { l4 };
	Node* n1 = new Node(n1_in, n1_out);
	Node* n2 = new Node(n2_in, n2_out);
	Node* n3 = new Node(n3_in, n3_out);
	Node* n4 = new Node(n4_in, n4_out);
	std::unordered_set<Node*> nodes = { n1 };
	std::unordered_set<Node*> pis = { n2 };
	std::unordered_set<Node*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	EXPECT_ANY_THROW(c->removePO(n2););
}
    

