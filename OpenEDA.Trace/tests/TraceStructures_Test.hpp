#include "gtest/gtest.h"
#include"TraceStructures.hpp"

//TraceNode()
TEST(TraceStructuresTest, TEST01) {
	EXPECT_NO_THROW(TraceNode tr;);
}

//TraceNode()
TEST(TraceStructuresTest, TEST02) {
	TraceNode tr;
	EXPECT_FALSE(tr.flag());
}

//TraceNode()
TEST(TraceStructuresTest, TEST03) {
	TraceNode tr;
	EXPECT_FALSE(tr.flag(true));
	EXPECT_TRUE(tr.flag());
}

//TraceNode()
TEST(TraceStructuresTest, TEST04) {
	TraceNode tr;
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	tr.addInput(l1);
	EXPECT_TRUE(l1->isOutputNode());
}

//TraceNode()
TEST(TraceStructuresTest, TEST05) {
	TraceNode tr;
	std::unordered_set<Line*> empty = {};
	Line* l1 = new Line(nullptr, nullptr, nullptr, empty, "l1");
	tr.addOutput(l1);
	EXPECT_TRUE(l1->isInputNode());
}