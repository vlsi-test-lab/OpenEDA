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
#include "ValueVectorFunctions.hpp"



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


	Parser<FaultyLine<bool>, FaultyNode<bool>, bool> parser;
	Circuit* c = parser.Parse("c17.bench");
	std::unordered_set<Levelized*> pisUnordered = c->pis();
	std::vector<SimulationNode<bool>*> pisOrdered;

	FaultSimulator<bool> faultSimulator;
	FaultSimulator<bool> tdfSimulator = FaultSimulator<bool>(true);
	FaultGenerator<bool> faultGenerator;
	std::unordered_set<Fault<bool>*> faults = faultGenerator.allFaults(c);
	std::unordered_set<Fault<bool>*> tdfFaults = faultGenerator.allFaults(c,false);

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
	std::vector<size_t> numDetected = {3, 5, 9, 12, 16, 17, 21, 22};

	void TearDown()
	{
		delete c;
		//This was deleted: the fault simulator will delete the tests.
		//for (Fault<bool>* fault : faults) {
		//	delete fault;
		//}
	}
};

TEST_F(FaultSimTest, c17safs) {
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

TEST_F(FaultSimTest, c17tdfs) {
	ASSERT_EQ(tdfFaults.size(), 34);
	tdfSimulator.setFaults(tdfFaults);

	for (size_t i = 0; i < testVectors.size(); i++) {
		for (size_t j = 0; j < testVectors.size(); j++) {
			std::vector<Value<bool>> firstVector = testVectors.at(i);
			std::vector<Value<bool>> secondVector = testVectors.at(j);
			size_t expectedNumDetectedFaults = numDetected.at(i);
			tdfSimulator.applyStimulus(c, firstVector, EventQueue<bool>(), pisOrdered);
			tdfSimulator.applyStimulus(c, secondVector, EventQueue<bool>(), pisOrdered);
		}
	}
	size_t numDetectedFaults = tdfSimulator.detectedFaults().size();
	EXPECT_EQ(34, numDetectedFaults);

}

template <class type>
bool connectingSortFunction(SimulationNode<type>* i, SimulationNode<type>* j) {
	Connecting* iOutput = *(i->outputs().begin());
	std::string iName = iOutput->name();
	Connecting* jOutput = *(j->outputs().begin());
	std::string jName = jOutput->name();
	return iName.compare(jName) < 0;
}

template <class type>
std::vector<SimulationNode<type>*> orderedPis(Circuit* _circuit) {
	std::vector<SimulationNode<type>*> toReturn;
	for (Levelized* pi : _circuit->pis()) {
		SimulationNode<type>* cast = dynamic_cast<SimulationNode<type>*>(pi);
		if (cast == nullptr) {
			throw "Cannot order PIs if a pi is not of the correct type";
		}
		toReturn.push_back(cast);
	}
	std::sort(toReturn.begin(), toReturn.end(), connectingSortFunction<type>);
	return toReturn;
}

class FaultSimTestWide : public ::testing::Test {
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

		boolPisOrdered = orderedPis<bool>(regularCircuit);
		widePisOrdered = orderedPis<unsigned long long int>(wideCircuit);
	}


	Parser<FaultyLine<unsigned long long int>, FaultyNode<unsigned long long int>, unsigned long long int> parser;
	Circuit* c = parser.Parse("c17.bench");
	std::unordered_set<Levelized*> pisUnordered = c->pis();
	std::vector<SimulationNode<unsigned long long int>*> pisOrdered;

	FaultSimulator<unsigned long long int> faultSimulator;
	FaultGenerator<unsigned long long int> faultGenerator;
	std::unordered_set<Fault<unsigned long long int>*> faults = faultGenerator.allFaults(c);
	std::unordered_set<Fault<unsigned long long int>*> tdfFaults = faultGenerator.allFaults(c, false);

	Value<bool> o = Value<bool>(0);
	Value<bool> i = Value<bool>(1);
	Value<bool> x = Value<bool>();

	//See the above "order" for what each of these inputs are.
	Value<unsigned long long int> p1inputs = Value<unsigned long long int>(0x0000000000000014, 0x000000000000001F);
	Value<unsigned long long int> p2inputs = Value<unsigned long long int>(0x00000000000000C3, 0x00000000000000FF);
	Value<unsigned long long int> p3inputs = Value<unsigned long long int>(0x000000000000001B, 0x00000000000000FF);
	Value<unsigned long long int> p6inputs = Value<unsigned long long int>(0x0000000000000042, 0x00000000000000DF);
	Value<unsigned long long int> p7inputs = Value<unsigned long long int>(0x000000000000000E, 0x000000000000003F);
	std::vector<Value<unsigned long long int>> stimulus = {
		p1inputs,
		p2inputs,
		p3inputs,
		p6inputs,
		p7inputs
	};

	/////////////////////////////////////////////////////////////////
	// Wide vs bool tests.
	/////////////////////////////////////////////////////////////////
	Parser<FaultyLine<bool>, FaultyNode<bool>, bool> parserBool;
	Circuit* regularCircuit = parserBool.Parse("c432.bench");
	Circuit* wideCircuit = parser.Parse("c432.bench");
	
	FaultGenerator<bool> faultGeneratorBool;
	
	std::unordered_set<Fault<bool>*> faultsBool = faultGeneratorBool.allFaults(regularCircuit);
	std::unordered_set<Fault<bool>*> tdfFaultsBool = faultGeneratorBool.allFaults(regularCircuit, false);
	std::unordered_set<Fault<unsigned long long int>*> faultsWide = faultGenerator.allFaults(wideCircuit);
	std::unordered_set<Fault<unsigned long long int>*> tdfFaultsWide = faultGenerator.allFaults(wideCircuit, false);

	FaultSimulator<bool> faultSimulatorBoolSAF;
	FaultSimulator<bool> faultSimulatorBoolTDF = FaultSimulator<bool>(true);
	FaultSimulator<unsigned long long int> faultSimulatorWideSAF;
	FaultSimulator<unsigned long long int> faultSimulatorWideTDF = FaultSimulator<unsigned long long int>(true);

	//The input stimulus:
	std::vector<Value<unsigned long long int>> WideVec = 
		std::vector<Value<unsigned long long int>>(36, Value<unsigned long long int>(0x0000000000000000));


	std::vector<Value<bool>> BoolVec = std::vector<Value<bool>>(36, Value<bool>(0x0000000000000000));
	std::vector<SimulationNode<bool>*> boolPisOrdered;
	std::vector<SimulationNode<unsigned long long int>*> widePisOrdered;


	void TearDown() {
		delete c;
		delete wideCircuit;
		delete regularCircuit;
		//This was deleted: the fault simulator will delete the tests.
		//for (Fault<bool>* fault : faults) {
		//	delete fault;
		//}
	}
};

TEST_F(FaultSimTestWide, c17safs) {
	ASSERT_EQ(faults.size(), 22);
	faultSimulator.setFaults(faults);
		
	size_t expectedNumDetectedFaults = 22;
	faultSimulator.applyStimulus(c, stimulus, EventQueue<unsigned long long int>(), pisOrdered);
	size_t numDetectedFaults = faultSimulator.detectedFaults().size();
	EXPECT_EQ(expectedNumDetectedFaults, numDetectedFaults);
	
}

TEST_F(FaultSimTestWide, wideVsBool) {
	ASSERT_EQ(faultsBool.size(), faultsWide.size());
	ASSERT_EQ(tdfFaultsBool.size(), tdfFaultsWide.size());
	faultSimulatorBoolSAF.setFaults(faultsBool);
	faultSimulatorWideSAF.setFaults(faultsWide);
	faultSimulatorBoolTDF.setFaults(tdfFaultsBool);
	faultSimulatorWideTDF.setFaults(tdfFaultsWide);

	//C432 has 40 inputs, but we won't simulate ALL input combinatons or pairs: that it's not feasible.
	//We'll simulate a total of 256 stuck-at fault vectors, and we'll check that fault coverage is the same every 64.
	WideVec[0] = Value<unsigned long long int>(0xAAAAAAAAAAAAAAAA);
	WideVec[1] = Value<unsigned long long int>(0xCCCCCCCCCCCCCCCC);
	WideVec[2] = Value<unsigned long long int>(0xF0F0F0F0F0F0F0F0);
	WideVec[3] = Value<unsigned long long int>(0xFF00FF00FF00FF00);
	WideVec[4] = Value<unsigned long long int>(0xFFFF0000FFFF0000);
	WideVec[5] = Value<unsigned long long int>(0xFFFFFFFF00000000);
	
	for (size_t i = 1; i <= 256; i++) {
		faultSimulatorBoolSAF.applyStimulus(regularCircuit, BoolVec, EventQueue<bool>(), boolPisOrdered);
		if ((i % 64) == 0) {
			faultSimulatorWideSAF.applyStimulus(wideCircuit, WideVec, EventQueue<unsigned long long int>(), widePisOrdered);
			ASSERT_EQ(faultSimulatorWideSAF.detectedFaults().size(), faultSimulatorBoolSAF.detectedFaults().size());
			ValueVectorFunction<unsigned long long int>::increment(WideVec);
		}
		ValueVectorFunction<bool>::increment(BoolVec);
	}

	//TDF simulation will always be from "all 0's" to a given vector. This makes things easy.
	//In this context, the "applied vector" will the vector we are toing to.
	WideVec =
		std::vector<Value<unsigned long long int>>(36, Value<unsigned long long int>(0x0000000000000000));
	WideVec[0] = Value<unsigned long long int>(0xAAAAAAAAAAAAAAAA);
	WideVec[1] = Value<unsigned long long int>(0xCCCCCCCCCCCCCCCC);
	WideVec[2] = Value<unsigned long long int>(0xF0F0F0F0F0F0F0F0);
	WideVec[3] = Value<unsigned long long int>(0xFF00FF00FF00FF00);
	WideVec[4] = Value<unsigned long long int>(0xFFFF0000FFFF0000);
	WideVec[5] = Value<unsigned long long int>(0xFFFFFFFF00000000);

	BoolVec = std::vector<Value<bool>>(36, Value<bool>(0x0000000000000000));

	Simulator<bool> regularSimulator; //We'll use this to "reset" the state of the circuit to all 0s.
	
	for (size_t i = 1; i <= 64; i++) {
		regularSimulator.applyStimulus(regularCircuit,
									   std::vector<Value<bool>>(36, Value<bool>(0))
									   );
		faultSimulatorBoolTDF.applyStimulus(regularCircuit, BoolVec, EventQueue<bool>(), boolPisOrdered);
		ValueVectorFunction<bool>::increment(BoolVec);
	}
	Simulator<unsigned long long int> wideSimulator;
	wideSimulator.applyStimulus(wideCircuit,
								std::vector<Value<unsigned long long int>>(36, Value<unsigned long long int>(0x0000000000000000))
								);
	faultSimulatorWideTDF.applyStimulus(wideCircuit, WideVec, EventQueue<unsigned long long int>(), widePisOrdered);
	ASSERT_EQ(faultSimulatorWideTDF.detectedFaults().size(), faultSimulatorBoolTDF.detectedFaults().size());

}