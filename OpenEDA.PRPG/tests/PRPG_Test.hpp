#include "gtest/gtest.h"
#include "PRPG.h"

class PRPGTest : public ::testing::Test {
public:
	void SetUp() override {

	}

	//DELETE: old 31-bit, external LFSR //PRPG<bool> prpg = PRPG<bool>(31);
	PRPG<bool> prpg = PRPG<bool>(64);
	Value<bool> i = Value<bool>(1);
	Value<bool> o = Value<bool>(0);

	//DELETE: old 31-bit, external LFSR
	//std::vector<Value<bool>> excpectedFirstLoad = {
	//	o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, i, i, i
	//};
	//std::vector<Value<bool>> excpectedSecondLoad = {
	//	o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, i, i, i, i, i, i
	//};
	
	
	std::vector<Value<bool>> excpectedFirstLoad = { o,i,o,o,o,i,o,i,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,i };
	std::vector<Value<bool>> excpectedSecondLoad = { i,i,o,i,i,o,i,i,o,i,i,i,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,i };

	PRPG<unsigned long long int> prpgBig = PRPG<unsigned long long int>(1);
	//The first 64 PRPG values (as 64-bit numbers)
	std::vector<unsigned long long int> prpgValues = {
		15564440312192400000,
		7782220156096220000,
		3891110078048110000,
		1945555039024050000,
		972777519512027000,
		486388759756014000,
		243194379878007000,
		121597189939003000,
		60798594969501700,
		30399297484750800,
		15199648742375400,
		7599824371187710,
		3799912185593860,
		1899956092796930,
		949978046398464,
		474989023199232,
		237494511599616,
		118747255799808,
		59373627899904,
		29686813949952,
		14843406974976,
		7421703487488,
		3710851743744,
		1855425871872,
		927712935936,
		463856467968,
		231928233984,
		115964116992,
		57982058496,
		28991029248,
		14495514624,
		7247757312,
		3623878656,
		1811939328,
		905969664,
		452984832,
		226492416,
		113246208,
		56623104,
		28311552,
		14155776,
		7077888,
		3538944,
		1769472,
		884736,
		442368,
		221184,
		110592,
		55296,
		27648,
		13824,
		6912,
		3456,
		1728,
		864,
		432,
		216,
		108,
		54,
		27,
		15564440312192400000,
		12970366926827000000,
		6485183463413510000,
		17654110539292300000,
	};
	void TearDown() {
		
	}
};

//TEST: Will the post-seed values be loaded?
//TEST: Will the second post-seed of values be loaded?
TEST_F(PRPGTest, BinaryValuesTest) {
	std::vector<Value<bool>> firstLoad = prpg.load();
	EXPECT_EQ(firstLoad,excpectedFirstLoad);
	std::vector<Value<bool>> secondLoad = prpg.load();
	EXPECT_EQ(secondLoad, excpectedSecondLoad);
}

//This test is no longer implmented becuase of long long int accuracy issues: the excel spreadsheet which generated
//the testing values converted floating to int, and hterefore large numbers were not accurate. However, results
//were manually checked.
//TEST_F(PRPGTest, PRPGStateTest) {
//	for (size_t i = 0; i < prpgValues.size(); i++) {
//		unsigned long long int prpgVal = prpgBig.increment().at(0).magnitude();
//		ASSERT_EQ(prpgVal, prpgValues.at(i));
//	}
//}
