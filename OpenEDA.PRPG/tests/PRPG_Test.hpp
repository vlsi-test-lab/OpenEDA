#include "gtest/gtest.h"
#include "PRPG.h"

class PRPGTest : public ::testing::Test {
public:
	void SetUp() override {

	}

	PRPG<bool> prpg = PRPG<bool>(31);
	Value<bool> i = Value<bool>(1);
	Value<bool> o = Value<bool>(0);

	std::vector<Value<bool>> excpectedFirstLoad = {
		o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, i, i, i
	};
	std::vector<Value<bool>> excpectedSecondLoad = {
		o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, i, i, i, i, i, i
	};

	void TearDown() {
		
	}
};

//TEST: Will the post-seed values be loaded?
//TEST: Will the second post-seed of values be loaded?
TEST_F(PRPGTest, ValuesTest) {
	std::vector<Value<bool>> firstLoad = prpg.load();
	EXPECT_EQ(firstLoad,excpectedFirstLoad);
	std::vector<Value<bool>> secondLoad = prpg.load();
	EXPECT_EQ(secondLoad, excpectedSecondLoad);
}
