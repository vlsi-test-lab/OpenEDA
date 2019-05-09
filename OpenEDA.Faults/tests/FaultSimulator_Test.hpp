/**
 * @file COPStructures_Tests.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-03-01
 *
 * @copyright Copyright (c) 2019
 *
 */

#include"gtest/gtest.h"
#include"FaultSimulator.h"
#include"FaultGenerator.h"
#include"Parser.hpp"



class FaultSimTest : public ::testing::Test {
public:
	void SetUp() override {
		std::vector<std::string> order = { "1", "2", "3", "6", "7" };
		for (size_t i = 0; i < pisUnordered.size(); i++) {
			for (Levelized* pi : c->pis()) {
				Connecting* piLine = *(pi->outputs().begin());
				std::string piName = piLine->name();
				if (piName == order.at(i)) {
					pisOrdered.push_back(dynamic_cast<SimulationNode<bool>*>(pi));
					break;
				}
			}
		}
	}


	Parser<FaultyLine<bool>, FaultyNode<bool>> parser;
	Circuit* c = parser.Parse("c17.bench");
	std::unordered_set<Levelized*> pisUnordered = c->pis();
	std::vector<SimulationNode<bool>*> pisOrdered;

	FaultSimulator<bool> faultSimulator;
	FaultGenerator<bool> faultGenerator;
	std::unordered_set<Fault<bool>*> faults = faultGenerator.allFaults(c);

	Value<bool> o = Value<bool>(0);
	Value<bool> i = Value<bool>(1);
	Value<bool> x = Value<bool>();
	
	//See the above "order" for what each of these inputs are.
	std::vector<Value<bool>> v0 = { x,i,o,o,x }; //Detects 2s0, 16->22s1, 11->16s0
	std::vector<Value<bool>> v1 = { x,i,o,i,x };
	std::vector<Value<bool>> v2 = { x,o,o,x,o };
	std::vector<Value<bool>> v3 = { i,o,i,o,o };
	std::vector<Value<bool>> v4 = { o,o,i,o,i };
	std::vector<Value<bool>> v5 = { i,o,o,o,i };
	std::vector<Value<bool>> v6 = { o,i,i,i,i };
	std::vector<Value<bool>> v7 = { o,i,i,o,o };
	std::vector<std::vector<Value<bool>>> testVectors = { v0, v1, v2, v3, v4, v5, v6, v7 };
	//The expected fault coverages after applying each vector, in terms of number of faults detected.
	std::vector<size_t> numDetected = {3, 5, 9, 12, 16, 21, 22};

	void TearDown()
	{
		delete c;
		//This was deleted: the fault simulator will delete the tests.
		//for (Fault<bool>* fault : faults) {
		//	delete fault;
		//}
	}
};

TEST_F(FaultSimTest, c17) {
	ASSERT_EQ(faults.size(), 22);
	faultSimulator.setFaults(faults);

	for (size_t i = 0; i < testVectors.size(); i++) {
		std::vector<Value<bool>> vector = testVectors.at(i);
		size_t expectedNumDetectedFaults = numDetected.at(i);
		faultSimulator.applyStimulus(c, vector, EventQueue<bool>(), pisOrdered);
		size_t numDetectedFaults = faultSimulator.detectedFaults().size();
		EXPECT_EQ(expectedNumDetectedFaults, numDetectedFaults);
	}

}
