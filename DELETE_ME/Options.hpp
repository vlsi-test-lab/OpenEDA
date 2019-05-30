//
//  Options.hpp
//  vlsi_programs_mac
//
//  Created by Spencer Millican on 1/31/18.
//  Copyright © 2018 Spencer Millican. All rights reserved.
//

#ifndef Options_hpp
#define Options_hpp

//#include <stdio.h>
#include <string>
#include <vector>
#include <map>

#include "Global.hpp"

//This class is used for setting circuit options and loading those options at a later time. Using this object makes the use of command line-options simpler.
class Options {
public:
	//Create a set of program options from argc and argv.
	Options(int argc, const char * argv[]);

	//Print the help message. Quit if option given is true.
	void help(bool _quit);

	//Set a miscelaneous option.
	void setMisc(std::string _m);

	//These methods return the set optoins. May return empty strings, default values, or throw errors.
	int getNumRand();
	int getBacktrackLimit();
	int getK();
	int getTimeLimit();
	bool getEncSat();
	std::string getDelayFile();
	std::string getNextCircuitFile(); //Gets one circuit file at a time. Will return an empty string if there are no other circuit files to give. This method will destroy the circuit file gotten.
	std::vector<std::string> getCircuitFiles(); //Returns a list of all circuit files.
	bool getMisc(std::string _m); //Returns true if the option is set.

								  //These methods will set default options (i.e., they will set them if they are not set yet. Will return true if the option has not been set yet.
	bool defaultNumRand(int);
	bool defaultBacktrackLimit(int);
	bool defaultK(int);
private:
	//Number of random vectors to apply. -1 = not set.
	int numRand_;

	//Backtrack limit. -1 = not set.
	int backtrackLimit_;

	//Cardinality of encryption. -1 = not set.
	int k_;

	//Do we perform satisfiability check on encrypted circuits? default is false.
	bool encSat_;

	//The time limit, in seconds.
	int timeLimit_;

	//Delay file to use.
	std::string delayFile_;

	//Circuit files to parse.
	std::vector<std::string> circuitFiles_;

	//A list (map) of miscelaneous boolean options which were set with "-mX"
	std::map<std::string, bool> miscSettings_;
};

#endif /* Options_hpp */
#pragma once
