/**
 * @file Circuit_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-12-27
 *
 * @copyright Copyright (c) 2018
 *
 */

#include"gtest/gtest.h"
#include"Circuit.h"
#include<unordered_set>

#include "Simulator.h"
#include "SimulationStructures.hpp"
#include "Parser.hpp"
#include "ValueVectorFunctions.hpp"


class CopyTest : public ::testing::Test {
public:
	void SetUp() override {
		std::vector<std::string> order = { "7", "6", "3", "2", "1" };
		std::unordered_set<Levelized*> pisUnordered = c17->pis();
		for (size_t i = 0; i < pisUnordered.size(); i++) {
			for (Levelized* pi : c17->pis()) {
				Connecting* piLine = *(pi->outputs().begin());
				std::string piName = piLine->name();
				if (piName == order.at(i)) {
					c17PisOrdered.push_back(dynamic_cast<SimulationNode<bool>*>(pi));
					break;
				}
			}
		}

		pisUnordered = c17copy->pis();
		for (size_t i = 0; i < pisUnordered.size(); i++) {
			for (Levelized* pi : c17copy->pis()) {
				Connecting* piLine = *(pi->outputs().begin());
				std::string piName = piLine->name();
				if (piName == order.at(i)) {
					c17CopyPisOrdered.push_back(dynamic_cast<SimulationNode<bool>*>(pi));
					break;
				}
			}
		}
	}

	Parser<SimulationLine<bool>, SimulationNode<bool>> parser;
	Circuit* c17 = parser.Parse("c17.bench");
	Circuit* c17copy = new Circuit(*c17);
	
	std::vector<SimulationNode<bool>*> c17PisOrdered;
	std::vector<SimulationNode<bool>*> c17CopyPisOrdered;

	Simulator<bool> simulator;
	EventQueue<bool> simulationQueue;

};

TEST_F(CopyTest, c17CopyTest) {
	std::vector<Value<bool>> inputVector = std::vector<Value<bool>>(c17->pis().size(), Value<bool>(0));
	do {
		std::vector<Value<bool>> originalOut = simulator.applyStimulus(c17, inputVector, simulationQueue, c17PisOrdered);
		std::vector<Value<bool>> copyOut = simulator.applyStimulus(c17copy, inputVector, simulationQueue, c17CopyPisOrdered);
		bool mismatch = ValueVectorFunction<bool>::mismatch(originalOut, copyOut);
		EXPECT_EQ(false, mismatch);
	} while (ValueVectorFunction<bool>::increment(inputVector));
}

class Circuit_Test : public ::testing::Test {
public:
	void SetUp() override {

	}
	std::unordered_set<Levelized*> empty = {};
	Levelized* l1 = new Levelized();
	Levelized* l2 = new Levelized();
	Levelized* l3 = new Levelized();
	Levelized* l4 = new Levelized();
	Levelized* l5 = new Levelized();
	Levelized* l6 = new Levelized();
	Levelized* l7 = new Levelized();
	Levelized* l8 = new Levelized();
	Levelized* l9 = new Levelized();
	std::unordered_set<Levelized*> n1_in = { l1,l2 };
	std::unordered_set<Levelized*> n1_out = { l3 };
	std::unordered_set<Levelized*> n2_in = { l3,l4 };
	std::unordered_set<Levelized*> n2_out = { l5 };
	std::unordered_set<Levelized*> n3_in = { l5,l6 };
	std::unordered_set<Levelized*> n3_out = { l7 };
	std::unordered_set<Levelized*> n4_in = { l8,l9 };
	std::unordered_set<Levelized*> n4_out = { l4 };
	Levelized* n1 = new Levelized(n1_in, n1_out);
	Levelized* n2 = new Levelized(n2_in, n2_out);
	Levelized* n3 = new Levelized(n3_in, n3_out);
	Levelized* n4 = new Levelized(n4_in, n4_out);
	std::unordered_set<Levelized*> nodes = { n1 };
	std::unordered_set<Levelized*> pis = { n2 };
	std::unordered_set<Levelized*> pos = { n3 };
	Circuit* c = new Circuit(nodes, pis, pos);
};

//Circuit(std::unordered_set<Levelized*> _nodes, std::unordered_set <Levelized*> _inputs, std::unordered_set<Levelized*> _outputs);
//std::unordered_set<Levelized*> nodes() const;
//std::unordered_set<Levelized*> pis() const;
//std::unordered_set<Levelized*> pos() const;
TEST_F(Circuit_Test, TEST01) {

	EXPECT_TRUE(std::is_permutation(nodes.begin(),nodes.end(),c->nodes().begin()));
	EXPECT_TRUE(std::is_permutation(pis.begin(), pis.end(), c->pis().begin()));
	EXPECT_TRUE(std::is_permutation(pos.begin(), pos.end(), c->pos().begin()));
}

//Circuit(std::unordered_set<Levelized*> _nodes, std::unordered_set <Levelized*> _inputs, std::unordered_set<Levelized*> _outputs);
//std::unordered_set<Levelized*> nodes() const;
//std::unordered_set<Levelized*> pis() const;
//std::unordered_set<Levelized*> pos() const;
TEST_F(Circuit_Test, TEST02) {
	std::unordered_set<Levelized*> check = { n1,n2,n3 };
	std::unordered_set<Levelized*> real = c->nodes();
	EXPECT_TRUE(std::is_permutation(real.begin(),real.end(),check.begin()));
}

//void addNode(Levelized* _node);
TEST_F(Circuit_Test, TEST03) {

	c->addNode(n4);
	std::unordered_set<Levelized*> check = { n4,n1,n2,n3 };
	EXPECT_TRUE(std::is_permutation(check.begin(), check.end(), c->nodes().begin()));
}

//Levelized* removeNode(Levelized* _node);
TEST_F(Circuit_Test, TEST04) {

	EXPECT_ANY_THROW(c->removeNode(n4););
}

//Levelized* removeNode(Levelized* _node);
TEST_F(Circuit_Test, TEST05) {

	c->removeNode(n1);
	EXPECT_FALSE(c->nodes().empty());
}

//void addPI(Levelized* _node);
TEST_F(Circuit_Test, TEST06) {

	c->addPI(n4);
	std::unordered_set<Levelized*> check = { n4,n2 };
	EXPECT_TRUE(std::is_permutation(check.begin(), check.end(), c->pis().begin()));
}

//void addPO(Levelized* _node);
TEST_F(Circuit_Test, TEST07) {

	c->addPO(n4);
	std::unordered_set<Levelized*> check = { n4,n3 };
	EXPECT_TRUE(std::is_permutation(check.begin(), check.end(), c->pos().begin()));
}

//Levelized* removePI(Levelized* _node);
TEST_F(Circuit_Test, TEST08) {

	ASSERT_NO_THROW(c->removeNode(n2););
	EXPECT_TRUE(c->pis().empty());
}

//Levelized* removePI(Levelized* _node);
TEST_F(Circuit_Test, TEST09) {

	EXPECT_ANY_THROW(c->removeNode(n4););
}



//Levelized* removePO(Levelized* _node);
TEST_F(Circuit_Test, TEST11) {

	ASSERT_NO_THROW(c->removeNode(n3););
	EXPECT_TRUE(c->pos().empty());
}




    

