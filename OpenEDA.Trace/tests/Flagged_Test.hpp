#include "gtest/gtest.h"
#include"Flagged.hpp"

//Flagged()
TEST(FlaggedConstructorTest, TEST01) {
	EXPECT_NO_THROW(Flagged flag;);
}

//Flagged()
//flag()
TEST(FlaggedConstructorTest, TEST02) {
	Flagged flag;
	EXPECT_FALSE(flag.flag());
}

//Flagged()
TEST(FlaggedConstructorTest, TEST03) {
	EXPECT_NO_THROW(Flagged flag(true););
}

//Flagged()
//flag()
TEST(FlaggedConstructorTest, TEST04) {
	Flagged flag(true);
	EXPECT_TRUE(flag.flag());
}

//Flagged()
//flag()
TEST(FlaggedConstructorTest, TEST05) {
	Flagged flag(true);
	EXPECT_TRUE(flag.flag(false));
	EXPECT_FALSE(flag.flag());
}