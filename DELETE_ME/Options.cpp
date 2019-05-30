


//
//  Options.cpp
//  vlsi_programs_mac
//
//  Created by Spencer Millican on 1/31/18.
//  Copyright © 2018 Spencer Millican. All rights reserved.
//

#include "Options.hpp"

Options::Options(int argc, const char * argv[]) {
	numRand_ = -1;
	backtrackLimit_ = -1;
	k_ = -1;
	encSat_ = false;
	delayFile_ = std::string();
	circuitFiles_ = std::vector<std::string>();

	if (argc == 1)
	{
		help(true);
	}
	for (int i = 1; i < argc; i++)
	{
		const char* arg = argv[i];
		if (arg[0] != '-')
		{
			help(true);
		}

		if (arg[1] == 'r') { i++; numRand_ = atoi(argv[i]); }
		else if (arg[1] == 'b') { i++; backtrackLimit_ = atoi(argv[i]); }
		else if (arg[1] == 'k') { i++; k_ = atoi(argv[i]); }
		else if (arg[1] == 'S') { encSat_ = true; }
		else if (arg[1] == 'd') { i++;  delayFile_ = std::string(argv[i]); }
		else if (arg[1] == 't') {
			i++;
			int tempLimit = atoi(argv[i]);
			//            limit = (int)(tempLimit * CLOCKS_PER_SEC);
			timeLimit_ = (int)(tempLimit);
		}
		else if (arg[1] == 'p')
		{//Benchmark in "p" format.
			i++;
			const char* infile = argv[i];
			circuitFiles_.push_back(std::string(infile));
		}
		else if (arg[1] == 'x')
		{//A miscelaneous true/false setting, set by the user for their own purpose.
			i++;
			const char* setting = argv[i];
			miscSettings_[std::string(setting)] = true;
		}
		else
		{
			help(true);
		}
	}
}

void Options::help(bool _quit = false)
{
	printf("Usage: encrypt.exe <circuit_file> <args>\n");
	printf("  -pF <num_vec> : Do fault simulation and print fault stats for the number of vectors\n");
	printf("  -V  <num_vec> : Do simulation to find unused input combinations\n");
	printf("  -pG           : Print general information on the circuit given\n");
	printf("  -pU           : Print number of unused input combinations and nodes\n");
	printf("  -pC           : Print general cone information\n");
	printf("  -pD           : Print difficulty analysis\n");
	printf("  -pH           : Print histogram\n");
	printf("  -pA           : Print decryptability analysis\n");
	printf("  -pW           : Print circuit in UW format\n");
	printf("  -pE           : Print circuit in Encrypted format\n");
	printf("  -DG           : Attempt decryption in guess-and-check format.\n");
	printf("\n");
	if (_quit) {
		exit(EXIT_FAILURE);
	}
}
void Options::setMisc(std::string _m) {
	miscSettings_[_m] = true;
}

int Options::getNumRand() {
	if (numRand_ < 0) {
		::err("Cannot return numRand option: it was never set.");
	}
	return numRand_;
}

int Options::getBacktrackLimit() {
	if (backtrackLimit_ < 0) {
		::err("Cannot return backtrace limit: it was never set.");
	}
	return backtrackLimit_;
}

int Options::getK() {
	if (k_ < 0) {
		::err("Cannot return K: it was never set");
	}
	return k_;
}

bool Options::getEncSat() {
	return encSat_;
}

std::string Options::getDelayFile() {
	return delayFile_;
}

std::string Options::getNextCircuitFile() {
	if (circuitFiles_.size() == 0) {
		return std::string();
	}
	std::string ret = circuitFiles_.at(0);
	circuitFiles_.erase(circuitFiles_.begin());
	return ret;
}

std::vector<std::string> Options::getCircuitFiles() {
	return circuitFiles_;
}

bool Options::getMisc(std::string _m) {
	std::map<std::string, bool>::iterator it = miscSettings_.find(_m);
	if (it != miscSettings_.end()) {
		return true;
	}
	return false;
}

bool Options::defaultNumRand(int _d) {
	if (numRand_ < 0) {
		numRand_ = _d;
		return true;
	}
	return false;
}

bool Options::defaultBacktrackLimit(int _d) {
	if (backtrackLimit_ < _d) {
		backtrackLimit_ = _d;
		return true;
	}
	return false;
}

bool Options::defaultK(int _d) {
	if (k_ < 0) {
		k_ = _d;
		return true;
	}
	return false;
}

int Options::getTimeLimit() {
	return timeLimit_;
}

