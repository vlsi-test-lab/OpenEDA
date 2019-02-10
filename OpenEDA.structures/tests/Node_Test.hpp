/**
 * @file Node_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-02
 *
 * @copyright Copyright (c) 2019
 *
 */

#include"gtest/gtest.h"
#include"Node.h"
#include<unordered_set>

//Node(std::unordered_set<Line*> _inputs, std::unordered_set<Line*> _outputs);
TEST(Node_Constructor_Test, TEST01) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");;
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty, "l3");;
	std::unordered_set<Line*> inputs = { l1,l2 };
	std::unordered_set<Line*> outputs = { l3 };
	Node* n = new Node(inputs, outputs);
	EXPECT_TRUE(l1->isOutputNode());
	EXPECT_TRUE(l2->isOutputNode());
}

//Node(std::unordered_set<Line*> _inputs, std::unordered_set<Line*> _outputs);
TEST(Node_Constructor_Test, TEST02) {
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	Line* l2 = new Line(nullptr, nullptr, nullptr, empty, "l2");;
	Line* l3 = new Line(nullptr, nullptr, nullptr, empty, "l3");;
	std::unordered_set<Line*> inputs = { l1,l2 };
	std::unordered_set<Line*> outputs = { l3 };
	Node* n = new Node(inputs, outputs);
	EXPECT_TRUE(l3->isInputNode());
}