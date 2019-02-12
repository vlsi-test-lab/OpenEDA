#include "gtest/gtest.h"
#include"TraceStructures.hpp"

//TraceNode()
TEST(TraceStructuresTest, TEST01) {
	EXPECT_NO_THROW(TraceNode<bool> tr;);
}

//TraceNode()
TEST(TraceStructuresTest, TEST02) {
	TraceNode<bool> tr;
	EXPECT_FALSE(tr.flag());
}

//TraceNode()
TEST(TraceStructuresTest, TEST03) {
	TraceNode<bool> tr;
	EXPECT_FALSE(tr.flag(true));
	EXPECT_TRUE(tr.flag());
}
