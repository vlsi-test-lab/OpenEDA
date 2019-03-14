#include "gtest/gtest.h"
#include"TraceStructures.hpp"

class TraceStructuresTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	TraceNode<bool>* tr = new TraceNode<bool>;
	void TearDown()
	{
		delete tr;
	}
};

//TraceNode()
TEST_F(TraceStructuresTest, TEST01) {
	EXPECT_NO_THROW(TraceNode<bool>* trnode = new TraceNode<bool>(););
}

//TraceNode()
TEST_F(TraceStructuresTest, TEST02) {
	
	EXPECT_FALSE(tr->flag());
}

//TraceNode()
TEST_F(TraceStructuresTest, TEST03) {
	EXPECT_FALSE(tr->flag(true));
	EXPECT_TRUE(tr->flag());
}
