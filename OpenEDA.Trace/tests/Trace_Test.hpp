/**
 * @file Trace_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-18
 *
 * @copyright Copyright (c) 2018
 *
 */

#include "gtest/gtest.h"
#include"Trace.h"

//static std::unordered_set<TraceNode*> pis(Circuit* _circuit, TraceNode* _node, std::unordered_set<TraceNode*> & _flagged)
TEST(TracePisTest, TEST01) {
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
	TraceNode* n1 = new TraceNode(n1_in, n1_out);
	TraceNode* n2 = new TraceNode(n2_in, n2_out);
	TraceNode* n3 = new TraceNode(n3_in, n3_out);
	std::unordered_set<Node*> nodes = { n1 };
	std::unordered_set<Node*> pis = { n2 };
	std::unordered_set<Node*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	std::unordered_set<TraceNode*> tr_check = {};
	std::unordered_set<TraceNode*> tr_checker = {n2,n1};
	std::unordered_set<TraceNode*> empty_trace = {};
	Trace tracer;
	tr_check = tracer.pis(c,n3,empty_trace);
	EXPECT_TRUE(std::is_permutation(tr_check.begin(),tr_check.end(),tr_checker.begin()));
}

//static std::unordered_set<TraceNode*> pis(Circuit* _circuit, TraceNode* _node, std::unordered_set<TraceNode*> & _flagged)
TEST(TracePisTest, TEST02) {
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
	TraceNode* n1 = new TraceNode(n1_in, n1_out);
	TraceNode* n2 = new TraceNode(n2_in, n2_out);
	TraceNode* n3 = new TraceNode(n3_in, n3_out);
	std::unordered_set<Node*> nodes = { };
	std::unordered_set<Node*> pis = { n2,n1 };
	std::unordered_set<Node*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
	std::unordered_set<TraceNode*> tr_check = {};
	std::unordered_set<TraceNode*> tr_checker = { n2,n1 };
	std::unordered_set<TraceNode*> empty_trace = {};
	Trace tracer;
	tr_check = tracer.pis(c, l6, empty_trace);
	EXPECT_TRUE(std::is_permutation(tr_check.begin(), tr_check.end(), tr_checker.begin()));
}
