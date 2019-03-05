#include "gtest/gtest.h"
#include"Flagged.hpp"

class FlaggedConstructorTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	Flagged flag;
};

//Flagged()
TEST(FlaggedConstructorTest, TEST01) {
	EXPECT_NO_THROW(Flagged flag;);
}

//Flagged()
//flag()
TEST_F(FlaggedConstructorTest, TEST02) {
	
	EXPECT_FALSE(flag.flag());
}

//Flagged()
TEST(FlaggedConstructorTest, TEST03) {
	EXPECT_NO_THROW(Flagged flag(true););
}

//Flagged()
//flag()
TEST_F(FlaggedConstructorTest, TEST04) {
	EXPECT_TRUE(flag.flag());
}

//Flagged()
//flag()
TEST_F(FlaggedConstructorTest, TEST05) {
	EXPECT_TRUE(flag.flag(false));
	EXPECT_FALSE(flag.flag());
}