/**
 * @file WideSimulator_Test.hpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-07-01
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "gtest/gtest.h"
#include "SimulationStructures.hpp"
#include "Simulator.h"
#include "ValueVectorFunctions.hpp"
#include "Parser.hpp"

class WideSimulatorTest : public ::testing::Test {
public:
	void SetUp() override {
		std::vector<std::string> order = { "1", "2", "3", "6", "7" };
		for (size_t i = 0; i < pisUnordered.size(); i++) {
			for (Levelized* pi : c->pis()) {
				Connecting* piLine = *(pi->outputs().begin());
				std::string piName = piLine->name();
				if (piName == order.at(i)) {
					pisOrdered.push_back(dynamic_cast<SimulationNode<unsigned long long int>*>(pi));
					break;
				}
			}
		}
	}

	Parser<SimulationLine<unsigned long long int>, SimulationNode<unsigned long long int>, unsigned long long int> parser;
	Circuit* c = parser.Parse("c17.bench");
	std::unordered_set<Levelized*> pisUnordered = c->pis();
	std::vector<SimulationNode<unsigned long long int>*> pisOrdered;



	//                                5432109876543210
	unsigned long long int ans_22 = 0x0000000000FC0FFF;
	unsigned long long int ans_23 = 0x0000000054FC54FC;

	//X-state test
	//std::vector<Value<bool>> x0 = { x,o,o,i,x };
	//std::vector<Value<bool>> x1 = { x,i,o,i,x };
	//std::vector<Value<bool>> x2 = { o,x,o,o,x };
	//std::vector<Value<bool>> xr0 = { i,i };
	//std::vector<Value<bool>> xr1 = { i,i };
	//std::vector<Value<bool>> xr2 = { o,o };
	//std::vector<std::vector<Value<bool>>> XTestVectors = { x0, x1, x2 };
	//std::vector<std::vector<Value<bool>>> XTestResponses = { xr0, xr1, xr2 };

	Simulator<unsigned long long int> sim;
	EventQueue<unsigned long long int> simulationQueue;

};

TEST_F(WideSimulatorTest, c17_exhaustive) {
	for (size_t repeat = 0; repeat < 100; repeat++) { //It was found that fails can be intermittent.
		std::vector<Value<unsigned long long int>> inputs;
		inputs.push_back(Value<unsigned long long int>(0x000000000000FFFF));//Pin 1
		inputs.push_back(Value<unsigned long long int>(0x0000000000FF00FF));//Pin 2
		inputs.push_back(Value<unsigned long long int>(0x000000000F0F0F0F));//Pin 3
		inputs.push_back(Value<unsigned long long int>(0x0000000033333333));//Pin 4
		inputs.push_back(Value<unsigned long long int>(0x0000000055555555));//Pin 5
		std::vector<Value<unsigned long long int>> response = sim.applyStimulus(
			c,
			inputs,
			EventQueue<unsigned long long int>(),
			pisOrdered
		);

		ASSERT_EQ(ans_22, response.at(0).magnitude());
		ASSERT_EQ(ans_23, response.at(1).magnitude());
	}
}

