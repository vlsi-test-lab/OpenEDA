//
//  Global.cpp
//  CryptIP
//
//  Created by Spencer Millican on 9/2/17.
//  Copyright © 2017 Auburn University. All rights reserved.
//

#include "Global.hpp"

int debug_level = 0;

clock_t timer = std::clock();

long int limit = LONG_MAX;

void err(std::string to_print) {
	printf("ERROR: %s\n", to_print.c_str());
 	exit(EXIT_FAILURE);
}

void dbg(std::string to_print, int level) {
	if (level > debug_level) { return; }
	printf("DBG: %s\n", to_print.c_str());
}
