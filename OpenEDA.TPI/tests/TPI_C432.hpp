
#pragma once
/**
 * @file Testpoint_Test.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-06-23
 *
 * @copyright Copyright (c) 2019
 *
 */

#include"gtest/gtest.h"
#include"TPI_COP.hpp"

#include "Parser.hpp"
#include "COP_TPI_Structures.hpp"
#include "TPGenerator.hpp"
#include "TPI_COP.hpp"
#include "Testpoint_control.hpp"
#include "Testpoint_invert.hpp"
#include "Testpoint_observe.hpp"
#include "FaultSimulator.h"
#include "PRPG.h"

bool connectingSortFunction (SimulationNode<bool>* i, SimulationNode<bool>* j) {
	Connecting* iOutput = *(i->outputs().begin());
	std::string iName = iOutput->name();
	Connecting* jOutput = *(j->outputs().begin());
	std::string jName = jOutput->name();
	return iName.compare(jName) < 0;
}

std::vector<SimulationNode<bool>*> orderedPis(Circuit* _circuit) {
	std::vector<SimulationNode<bool>*> toReturn;
	for (Levelized* pi : _circuit->pis()) {
		SimulationNode<bool>* cast = dynamic_cast<SimulationNode<bool>*>(pi);
		if (cast == nullptr) {
			throw "Cannot order PIs if a pi is not of the correct type";
		}
		toReturn.push_back(cast);
	}
	std::sort(toReturn.begin(), toReturn.end(), connectingSortFunction);
	return toReturn;
}

class C432Tests : public ::testing::Test {
public:
	void SetUp() override {
		observeTPs = observeGen.allTPs(modifiedCircuit);
		all_tps = { observeTPs };
		originalPisOrdered = orderedPis(originalCircuit);
		modifiedPisOrdered = orderedPis(modifiedCircuit);
	}



	Parser<COP_TPI_Line<bool>, COP_TPI_Node<bool>, bool> parser;

	Circuit* originalCircuit = parser.Parse("c432.bench");
	Circuit* modifiedCircuit = parser.Parse("c432.bench");
	TPI_COP<bool, COP_TPI_Node<bool>, COP_TPI_Line<bool>> tpi = TPI_COP<bool, COP_TPI_Node<bool>, COP_TPI_Line<bool>>(modifiedCircuit);
	TPGenerator<Testpoint_observe<bool, COP_TPI_Node<bool>, COP_TPI_Line<bool>>, COP_TPI_Node<bool>, COP_TPI_Line<bool>, bool> observeGen;
	std::set<Testpoint<bool, COP_TPI_Node<bool>, COP_TPI_Line<bool>>*> observeTPs;
	std::vector<std::set<Testpoint<bool, COP_TPI_Node<bool>, COP_TPI_Line<bool>>*>> all_tps;

	std::vector<SimulationNode<bool>*> originalPisOrdered;
	std::vector<SimulationNode<bool>*> modifiedPisOrdered;

};

//It was noticed that TDF fault coverage DECREASED after TPI was performed: 
//this is an attempt to re-careate this.
TEST_F(C432Tests, ObservePointTests) {
	//PERFORM TPI
	tpi.timeLimit(3600);
	tpi.testpointLimit(0.01*(originalCircuit->nodes().size()));
	std::set<Testpoint<bool, COP_TPI_Node<bool>, COP_TPI_Line<bool>>*> testpoints = tpi.testpoints(all_tps);
	EXPECT_EQ(testpoints.size(), 2);

	//Fault Simulation Setup
	std::unordered_set<Fault<bool>*>originalFaults = FaultGenerator<bool>::allFaults(originalCircuit, false);
	FaultSimulator<bool>originalSimulator(true);
	originalSimulator.setFaults(originalFaults);
	std::unordered_set<Fault<bool>*>modifiedFaults = FaultGenerator<bool>::allFaults(modifiedCircuit, false);
	FaultSimulator<bool>modifiedSimulator(true);
	modifiedSimulator.setFaults(modifiedFaults);
	ASSERT_EQ(originalFaults.size(), modifiedFaults.size());

	

	//SIMULTE
	PRPG<bool> prpg(originalCircuit->pis().size());
	size_t numVec = 10000;
	for (size_t vecNum = 0; vecNum < numVec / 2 ; vecNum++) {
		std::vector<Value<bool>> vector = prpg.increment();
		originalSimulator.applyStimulus(originalCircuit, vector, EventQueue<bool>(), originalPisOrdered);
		modifiedSimulator.applyStimulus(modifiedCircuit, vector, EventQueue<bool>(), modifiedPisOrdered);
		ASSERT_EQ(originalSimulator.detectedFaults().size(), modifiedSimulator.detectedFaults().size());
	}

	//Activate TPs
	for (Testpoint<bool, COP_TPI_Node<bool>, COP_TPI_Line<bool>>* testpoint : testpoints) {
		testpoint->activate();
	}

	for (size_t vecNum = 0; vecNum < numVec / 2; vecNum++) {
		std::vector<Value<bool>> vector = prpg.increment();
		originalSimulator.applyStimulus(originalCircuit, vector, EventQueue<bool>(), originalPisOrdered);
		modifiedSimulator.applyStimulus(modifiedCircuit, vector, EventQueue<bool>(), modifiedPisOrdered);
		ASSERT_LE(originalSimulator.detectedFaults().size(), modifiedSimulator.detectedFaults().size());
	}
}

