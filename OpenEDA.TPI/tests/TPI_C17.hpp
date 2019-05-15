
#pragma once
/**
 * @file Testpoint_Test.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-05-13
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

class C17Tests : public ::testing::Test {
public:
	void SetUp() override {

	}

	Parser<COP_TPI_Line, COP_TPI_Node> parser;
	Circuit* c17 = parser.Parse("c17.bench");
	TPI_COP<COP_TPI_Node, COP_TPI_Line> tpi = TPI_COP<COP_TPI_Node, COP_TPI_Line>(c17);
	TPGenerator<Testpoint_control<bool, COP_TPI_Node, COP_TPI_Line>, COP_TPI_Node, COP_TPI_Line, bool> controlGen;
	TPGenerator<Testpoint_observe<bool, COP_TPI_Node, COP_TPI_Line>, COP_TPI_Node, COP_TPI_Line, bool> observeGen;
	TPGenerator<Testpoint_invert<bool, COP_TPI_Node, COP_TPI_Line>, COP_TPI_Node, COP_TPI_Line, bool> invertGen;
	std::set<Testpoint<bool, COP_TPI_Node, COP_TPI_Line>*> controlTPs = controlGen.allTPs(c17);
	std::set<Testpoint<bool, COP_TPI_Node, COP_TPI_Line>*> observeTPs = observeGen.allTPs(c17);
	std::set<Testpoint<bool, COP_TPI_Node, COP_TPI_Line>*> invertTPs = invertGen.allTPs(c17);

	//The Expected fault coverage of a given testpoint if one vector is applied.
	std::map<std::string, float> ExpOneVecFC =
	{
{"C1_1",0.00554726340553977},
{"C1_2",-0.00441256436434659},
{"C1_3",0.0220544988458806},
{"C1_3_10",-0.0144556218927557},
{"C1_3_11",0.0113345059481534},
{"C1_6",0.0303108908913352},
{"C1_7",0.00119712136008521},
{"C1_10",-0.0192940451882102},
{"C1_11",-0.0455724542791193},
{"C1_11_16",-0.0278167724609375},
{"C1_11_19",-0.011747880415483},
{"C1_16",-0.0143224542791193},
{"C1_16_22",0.00143571333451703},
{"C1_16_23",0.0163060968572443},
{"C1_19",-0.0207144997336648},
{"C1_22",-0.0948444713245739},
{"C1_23",-0.0880085338245739},

{"C0_1",-0.00508949973366479},
{"C0_2",0.016572432084517},
{"C0_3",-0.0121917724609375},
{"C0_3_10",-0.00508949973366479},
{"C0_3_11",-0.0324332497336648},
{"C0_6",-0.0324332497336648},
{"C0_7",0.000592318448153412},
{"C0_10",-0.0948444713245739},
{"C0_11",-0.0370497270063921},
{"C0_11_16",0.00627413662997159},
{"C0_11_19",-0.00650995427911932},
{"C0_16",-0.16773154518821},
{"C0_16_22",-0.0607535622336648},
{"C0_16_23",-0.059599442915483},
{"C0_19",-0.0880085338245739},
{"C0_22",-0.0948444713245739},
{"C0_23",-0.0880085338245739},


{"O_1",0.03125},
{"O_2",0.0145596590909091},
{"O_3",0.0214996337890625},
{"O_3_10",0.0527496337890625},
{"O_3_11",0.0527718283913352},
{"O_6",0.0312721946022727},
{"O_7",0.0241477272727273},
{"O_10",0.0229089910333806},
{"O_11",0.0229644775390625},
{"O_11_16",0.0478224320845171},
{"O_11_19",0.0542144775390625},
{"O_16",0.00729508833451703},
{"O_16_22",0.0186587246981534},
{"O_16_23",0.0243405428799716},
{"O_19",0.0275698575106534},
{"O_22",0},
{"O_23",0},
{"I_1",0},
{"I_2",0},
{"I_3",0},
{"I_3_10",0},
{"I_3_11",0},
{"I_6",0},
{"I_7",0},
{"I_10",-0.0373174493963068},
{"I_11",0.00749345259232953},
{"I_11_16",0.0128617720170454},
{"I_11_19",0.00202248313210227},
{"I_16",-0.0338467684659091},
{"I_16_22",-0.0152726606889205},
{"I_16_23",-0.0183799050071023},
{"I_19",-0.0162270285866477},
{"I_22",0},
{"I_23",0}


	};
};

TEST_F(C17Tests, AllTPsGenerated) {
	EXPECT_EQ(controlTPs.size(), 34);
	EXPECT_EQ(invertTPs.size(), 17);
	EXPECT_EQ(observeTPs.size(), 17);
}

TEST_F(C17Tests, C17ExhaustiveControl) {
	for (Testpoint<bool, COP_TPI_Node, COP_TPI_Line>* controlTP : controlTPs) {
		std::string tpName = "C";
		std::string lineName = controlTP->location()->name();
		std::string controlValue = controlTP->value().magnitude() == false ? "0" : "1";
		std::string fanout = "";
		if (controlTP->location()->inputs().size() != 0) {
			Connecting* input = *(controlTP->location()->inputs().begin());
			if (dynamic_cast<COP_TPI_Node*>(input) == nullptr) {
				Connecting* fanOutNode = *(controlTP->location()->outputs().begin());
				Connecting* fanOutLine = *(fanOutNode->outputs().begin());
				fanout = "_" + fanOutLine->name();
			}
		}
		tpName = tpName + controlValue + "_" + lineName + fanout;
		printf("\nDBG TP %s\n", tpName.c_str());
		float foundFC = tpi.quality(controlTP);
		float expFC = ExpOneVecFC.at(tpName);
		EXPECT_NEAR(foundFC, expFC,0.0001);
	}
}

TEST_F(C17Tests, C17ExhaustiveObserve) {
	for (Testpoint<bool, COP_TPI_Node, COP_TPI_Line>* observeTP : observeTPs) {
		std::string tpName = "O";
		std::string lineName = observeTP->location()->name();
		std::string fanout = "";
		if (observeTP->location()->inputs().size() != 0) {
			Connecting* input = *(observeTP->location()->inputs().begin());
			if (dynamic_cast<COP_TPI_Node*>(input) == nullptr) {
				Connecting* fanOutNode = *(observeTP->location()->outputs().begin());
				Connecting* fanOutLine = *(fanOutNode->outputs().begin());
				fanout = "_" + fanOutLine->name();
			}
		}
		tpName = tpName + "_" + lineName + fanout;
		printf("\n\nDBG TP: %s\n",tpName.c_str());
		float foundFC = tpi.quality(observeTP);
		float expFC = ExpOneVecFC.at(tpName);
		EXPECT_NEAR(foundFC, expFC, 0.0001);
	}
}

TEST_F(C17Tests, C17ExhaustiveInvert) {
	for (Testpoint<bool, COP_TPI_Node, COP_TPI_Line>* invertTP : invertTPs) {
		std::string tpName = "I";
		std::string lineName = invertTP->location()->name();
		std::string fanout = "";
		if (invertTP->location()->inputs().size() != 0) {
			Connecting* input = *(invertTP->location()->inputs().begin());
			if (dynamic_cast<COP_TPI_Node*>(input) == nullptr) {
				Connecting* fanOutNode = *(invertTP->location()->outputs().begin());
				Connecting* fanOutLine = *(fanOutNode->outputs().begin());
				fanout = "_" + fanOutLine->name();
			}
		}
		tpName = tpName + "_" + lineName + fanout;
		printf("\n\nDBG TP: %s\n", tpName.c_str());
		float foundFC = tpi.quality(invertTP);
		float expFC = ExpOneVecFC.at(tpName);
		EXPECT_NEAR(foundFC, expFC, 0.0001);
	}
}