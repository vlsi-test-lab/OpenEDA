
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
		/*std::vector<std::string> order = { 
			"1",
			"4",
			"8",
			"11",
			"14",
			"17",
			"21",
			"24",
			"27",
			"30",
			"34",
			"37",
			"40",
			"43",
			"47",
			"50",
			"53",
			"56",
			"60",
			"63",
			"66",
			"69",
			"73",
			"76",
			"79",
			"82",
			"86",
			"89",
			"92",
			"95",
			"99",
			"102",
			"105",
			"108",
			"112",
			"115"
		};
		for (size_t i = 0; i < order.size(); i++) {
			for (Levelized* pi : originalCircuit->pis()) {
				Connecting* piLine = *(pi->outputs().begin());
				std::string piName = piLine->name();
				if (piName == order.at(i)) {
					originalPisOrdered.push_back(dynamic_cast<SimulationNode<bool>*>(pi));
					break;
				}
			}
			for (Levelized* pi : modifiedCircuit->pis()) {
				Connecting* piLine = *(pi->outputs().begin());
				std::string piName = piLine->name();
				if (piName == order.at(i)) {
					modifiedPisOrdered.push_back(dynamic_cast<SimulationNode<bool>*>(pi));
					break;
				}
			}
		}*/
		originalPisOrdered = orderedPis(originalCircuit);
		modifiedPisOrdered = orderedPis(modifiedCircuit);
	}



	Parser<COP_TPI_Line, COP_TPI_Node> parser;
	Circuit* originalCircuit = parser.Parse("c432.bench");
	Circuit* modifiedCircuit = parser.Parse("c432.bench");

	TPI_COP<COP_TPI_Node, COP_TPI_Line> tpi = TPI_COP<COP_TPI_Node, COP_TPI_Line>(modifiedCircuit);
	TPGenerator<Testpoint_observe<bool, COP_TPI_Node, COP_TPI_Line>, COP_TPI_Node, COP_TPI_Line, bool> observeGen;
	std::set<Testpoint<bool, COP_TPI_Node, COP_TPI_Line>*> observeTPs = observeGen.allTPs(modifiedCircuit);
	std::vector<std::set<Testpoint<bool, COP_TPI_Node, COP_TPI_Line>*>> all_tps = { observeTPs };

	std::vector<SimulationNode<bool>*> originalPisOrdered;
	std::vector<SimulationNode<bool>*> modifiedPisOrdered;

};

//It was noticed that TDF fault coverage DECREASED after TPI was performed: 
//this is an attempt to re-careate this.
TEST_F(C432Tests, ObservePointTests) {
	//PERFORM TPI
	tpi.timeLimit(3600);
	tpi.testpointLimit(0.01*(originalCircuit->nodes().size()));
	std::set<Testpoint<bool, COP_TPI_Node, COP_TPI_Line>*> testpoints = tpi.testpoints(all_tps);
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
	for (Testpoint<bool, COP_TPI_Node, COP_TPI_Line>* testpoint : testpoints) {
		testpoint->activate();
	}

	for (size_t vecNum = 0; vecNum < numVec / 2; vecNum++) {
		std::vector<Value<bool>> vector = prpg.increment();
		originalSimulator.applyStimulus(originalCircuit, vector, EventQueue<bool>(), originalPisOrdered);
		modifiedSimulator.applyStimulus(modifiedCircuit, vector, EventQueue<bool>(), modifiedPisOrdered);
		ASSERT_LE(originalSimulator.detectedFaults().size(), modifiedSimulator.detectedFaults().size());
	}
}