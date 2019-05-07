/**
 * @file SimulationStructure_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-01-10
 *
 * @copyright Copyright (c) 2018
 *
 */

#include "gtest/gtest.h"
#include "SimulationStructures.hpp"
#include "Simulator.h"
#include "ValueVectorFunctions.hpp"
#include "Parser.hpp"

class SimulatorTest : public ::testing::Test {
public:
	void SetUp() override {
		std::vector<std::string> order = {"7", "6", "3", "2", "1"};
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
	
	Parser<SimulationLine<bool>, SimulationNode<bool>> parser;
	Circuit* c = parser.Parse("c17.bench");
	std::unordered_set<Levelized*> pisUnordered = c->pis();
	std::vector<SimulationNode<bool>*> pisOrdered;

	Value<bool> i = Value<bool>(1);
	Value<bool> o = Value<bool>(0);

	/*std::vector<Value<bool>> v0 = { o,o,o,o,o };
	std::vector<Value<bool>> v1 = { o,o,o,o,i };
	std::vector<Value<bool>> v2 = { o,o,o,i,o };
	std::vector<Value<bool>> v3 = { o,o,o,i,i };
	std::vector<Value<bool>> v4 = { o,o,i,o,o };
	std::vector<Value<bool>> v5 = { o,o,i,o,i };
	std::vector<Value<bool>> v6 = { o,o,i,i,o };
	std::vector<Value<bool>> v7 = { o,o,i,i,i };
	std::vector<Value<bool>> v8 = { o,i,o,o,o };
	std::vector<Value<bool>> v9 = { o,i,o,o,i };
	std::vector<Value<bool>> v10 = { o,i,o,i,o };
	std::vector<Value<bool>> v11 = { o,i,o,i,i };
	std::vector<Value<bool>> v12 = { o,i,i,o,o };
	std::vector<Value<bool>> v13 = { o,i,i,o,i };
	std::vector<Value<bool>> v14 = { o,i,i,i,o };
	std::vector<Value<bool>> v15 = { o,i,i,i,i };
	std::vector<Value<bool>> v16 = { i,o,o,o,o };
	std::vector<Value<bool>> v17 = { i,o,o,o,i };
	std::vector<Value<bool>> v18 = { i,o,o,i,o };
	std::vector<Value<bool>> v19 = { i,o,o,i,i };
	std::vector<Value<bool>> v20 = { i,o,i,o,o };
	std::vector<Value<bool>> v21 = { i,o,i,o,i };
	std::vector<Value<bool>> v22 = { i,o,i,i,o };
	std::vector<Value<bool>> v23 = { i,o,i,i,i };
	std::vector<Value<bool>> v24 = { i,i,o,o,o };
	std::vector<Value<bool>> v25 = { i,i,o,o,i };
	std::vector<Value<bool>> v26 = { i,i,o,i,o };
	std::vector<Value<bool>> v27 = { i,i,o,i,i };
	std::vector<Value<bool>> v28 = { i,i,i,o,o };
	std::vector<Value<bool>> v29 = { i,i,i,o,i };
	std::vector<Value<bool>> v30 = { i,i,i,i,o };
	std::vector<Value<bool>> v31 = { i,i,i,i,i };*/

	std::vector<Value<bool>> ans_22 = {
		o,o,o,o,o,o,o,o,
		i,i,i,i,i,i,o,o,
		o,o,o,o,i,i,i,i,
		i,i,i,i,i,i,i,i
	};
	std::vector<Value<bool>> ans_23 = {
		o,i,o,i,o,i,o,o,
		i,i,i,i,i,i,o,o,
		o,i,o,i,o,i,o,o,
		i,i,i,i,i,i,o,o
	};



	Simulator<bool> sim;
	EventQueue<bool> simulationQueue;
	
};

//std::vector<Value<T>> applyStimulus(Circuit * _circuit, std::vector<Value<T>> _stimulus, std::vector<SimulationNode<T>*> _inputs = std::vector<SimulationNode<T>*>());
TEST_F(SimulatorTest, TEST01) {
	std::vector<Value<bool>> inputs = std::vector<Value<bool>>(5, Value<bool>(1));
	for (size_t i = 0; i < 32; i++) {
		ValueVectorFunction<bool>::increment(inputs);
		std::vector<Value<bool>> response;
		EXPECT_NO_THROW(
			response = sim.applyStimulus(
				c,
				inputs,
				EventQueue<bool>(),
				pisOrdered
			)
		);
		Value<bool> exp_22 = ans_22.at(i);
		Value<bool> exp_23 = ans_23.at(i);
		EXPECT_EQ(exp_22,response.at(0));
		EXPECT_EQ(exp_23, response.at(1));
	}

}