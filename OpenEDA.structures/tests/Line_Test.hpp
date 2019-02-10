/**
 * @file Line_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2018-12-30
 *
 * @copyright Copyright (c) 2018
 *
 */

#include"gtest/gtest.h"
#include"Line.h"
#include"Node.h"
#include<unordered_set>

 //Line(Node* _inNode, Node* _outNode, Line* _inLine, std::unordered_set<Line*> _outLines, std::string _name = "");
TEST(Line_Constructor_Test, TEST01) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr,nullptr,nullptr,empty,"l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");;
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty, "l3");;
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty, "l4");;
	
	std::unordered_set<Line*> in_l_n1 = {l1};
	std::unordered_set<Line*> o_l_n1 = {l2};
	std::unordered_set<Line*> in_l_n2 = {  };
	std::unordered_set<Line*> o_l_n2 = { l4 };
	Node* n1 = new Node(in_l_n1,o_l_n1); 
	Node* n2 = new Node(in_l_n2, o_l_n2);
	std::unordered_set<Line*> ol = {};
	EXPECT_NO_THROW(Line* l = new Line(n1, n2, nullptr, ol, "Test_Line"););
}

//Line(Node* _inNode, Node* _outNode, Line* _inLine, std::unordered_set<Line*> _outLines, std::string _name = "");
TEST(Line_Constructor_Test, TEST02) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");;
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty, "l3");;
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty, "l4");;
	std::unordered_set<Line*> in_l_n1 = { l1 };
	std::unordered_set<Line*> o_l_n1 = { l2 };
	Node* n1 = new Node(in_l_n1, o_l_n1);
	std::unordered_set<Line*> ol = {l3};
	EXPECT_ANY_THROW(Line* l = new Line(n1, nullptr, nullptr, ol, "Test_Line"););
}

//Line(Node* _inNode, Node* _outNode, Line* _inLine, std::unordered_set<Line*> _outLines, std::string _name = "");
TEST(Line_Constructor_Test, TEST03) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");;
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty, "l3");;
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty, "l4");;
	std::unordered_set<Line*> in_l_n1 = { l1 };
	std::unordered_set<Line*> o_l_n1 = { l2 };
	std::unordered_set<Line*> in_l_n2 = {  };
	std::unordered_set<Line*> o_l_n2 = { l4 };
	Node* n1 = new Node(in_l_n1, o_l_n1);
	Node* n2 = new Node(in_l_n2, o_l_n2);
	std::unordered_set<Line*> ol = {l3};
	EXPECT_ANY_THROW(Line* l = new Line(n1, n2, nullptr, ol, "Test_Line"););
}

//Line(Node* _inNode, Node* _outNode, Line* _inLine, std::unordered_set<Line*> _outLines, std::string _name = "");
TEST(Line_Constructor_Test, TEST04) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty, "l3");
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty, "l4");
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty, "l5");;
	std::unordered_set<Line*> in_l_n1 = { l1 };
	std::unordered_set<Line*> o_l_n1 = { l2 };
	std::unordered_set<Line*> in_l_n2 = { };
	std::unordered_set<Line*> o_l_n2 = { l4 };
	Node* n1 = new Node(in_l_n1, o_l_n1);
	Node* n2 = new Node(in_l_n2, o_l_n2);
	std::unordered_set<Line*> ol = {};
	EXPECT_ANY_THROW(Line* l =  new Line(n1, n2, l5, ol, "Test_Line"););
}

//Line(Node* _inNode, Node* _outNode, Line* _inLine, std::unordered_set<Line*> _outLines, std::string _name = "");
TEST(Line_Constructor_Test, TEST05) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty, "l3");
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty, "l4");
	std::unordered_set<Line*> in_l_n1 = { l1 };
	std::unordered_set<Line*> o_l_n1 = { l2 };
	std::unordered_set<Line*> in_l_n2 = {  };
	std::unordered_set<Line*> o_l_n2 = { l4 };
	Node* n2 = new Node(in_l_n2, o_l_n2);
	std::unordered_set<Line*> ol = {};
	EXPECT_NO_THROW(Line* l = new Line(nullptr, n2, l1, ol, "Test_Line"););
}


//bool isInputNode() const;
TEST(Line_IPNode_Test, TEST01) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty, "l3");
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty, "l4");
	std::unordered_set<Line*> in_l_n1 = { l1 };
	std::unordered_set<Line*> o_l_n1 = { l2 };
	std::unordered_set<Line*> in_l_n2 = {  };
	std::unordered_set<Line*> o_l_n2 = { l4 };
	Node* n2 = new Node(in_l_n2, o_l_n2);
	std::unordered_set<Line*> ol = {};
	Line* l = new Line(nullptr, n2, l1, ol, "Test_Line");
	EXPECT_FALSE(l->isInputNode());
}

//bool isInputNode() const;
TEST(Line_IPNode_Test, TEST02) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty, "l3");
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty, "l4");
	std::unordered_set<Line*> in_l_n1 = { l1 };
	std::unordered_set<Line*> o_l_n1 = { l2 };
	std::unordered_set<Line*> in_l_n2 = {  };
	std::unordered_set<Line*> o_l_n2 = { l4 };
	Node* n1 = new Node(in_l_n1, o_l_n1);
	Node* n2 = new Node(in_l_n2, o_l_n2);
	std::unordered_set<Line*> ol = {};
	Line* l = new Line(n1, n2, nullptr, ol, "Test_Line");
	EXPECT_TRUE(l->isInputNode());
}

//bool isOutputNode() const;
TEST(Line_OPNode_Test, TEST01) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty, "l3");
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty, "l4");
	std::unordered_set<Line*> in_l_n1 = { l1 };
	std::unordered_set<Line*> o_l_n1 = { l2 };
	std::unordered_set<Line*> in_l_n2 = {  };
	std::unordered_set<Line*> o_l_n2 = { l4 };
	Node* n2 = new Node(in_l_n2, o_l_n2);
	std::unordered_set<Line*> ol = {};
	Line* l = new Line(nullptr, n2, l1, ol, "Test_Line");
	EXPECT_TRUE(l->isOutputNode());
}

//bool isInputNode() const;
TEST(Line_OPNode_Test, TEST02) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty, "l3");
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty, "l4");
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty, "l5");
	std::unordered_set<Line*> in_l_n1 = { l1 };
	std::unordered_set<Line*> o_l_n1 = { l2 };
	std::unordered_set<Line*> in_l_n2 = {  };
	std::unordered_set<Line*> o_l_n2 = { l4 };
	Node* n1 = new Node(in_l_n1, o_l_n1);
	std::unordered_set<Line*> ol = {l4,l5};
	Line* l = new Line(n1, nullptr, nullptr, ol, "Test_Line");
	EXPECT_FALSE(l->isOutputNode());
}

//	virtual std::string name() const;
TEST(Line_name_Test, TEST01) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty, "l3");
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty, "l4");
	Line* l5 = new Line(nullptr, nullptr, nullptr, empty, "l5");
	std::unordered_set<Line*> in_l_n1 = { l1 };
	std::unordered_set<Line*> o_l_n1 = { l2 };
	std::unordered_set<Line*> in_l_n2 = {  };
	std::unordered_set<Line*> o_l_n2 = { l4 };
	Node* n1 = new Node(in_l_n1, o_l_n1);
	Node* n2 = new Node(in_l_n2, o_l_n2);
	std::unordered_set<Line*> ol = {};
	Line* l = new Line(n1, n2, nullptr, ol, "Test_Line");
	std::string name_test = "Test_Line";
	EXPECT_EQ(name_test,l->name());
}

//void setInputNode( Node* _node );
TEST(Line_setInputNode_Test, TEST01) {
	std::unordered_set<Line*> empty = {};
	Line* l = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty, "l3");
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty, "l4");
	std::unordered_set<Line*> inputs = { l1, l2 };
	std::unordered_set<Line*> outputs = { l3, l4 };
	Node* n = new Node(inputs, outputs);
	std::unordered_set<Connecting*> check = { n };
	l->setInputNode(n);
	ASSERT_TRUE(l->isInputNode());
	EXPECT_TRUE(std::is_permutation(check.begin(),check.end(),l->inputs().begin()));
}

//void setOutputNode( Node* _node );
TEST(Line_setOutputNode_Test, TEST01) {
	std::unordered_set<Line*> empty = {};
	Line* l = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty, "l3");
	Line* l4 = new Line(nullptr, nullptr, nullptr, empty, "l4");
	std::unordered_set<Line*> inputs = { l1, l2 };
	std::unordered_set<Line*> outputs = { l3, l4 };
	Node* n = new Node(inputs, outputs);
	std::unordered_set<Connecting*> check = { n };
	l->setOutputNode(n);
	ASSERT_TRUE(l->isOutputNode());
	EXPECT_TRUE(std::is_permutation(check.begin(),check.end(),l->outputs().begin()));
}

