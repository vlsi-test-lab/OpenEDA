//
//  Global.hpp
//  CryptIP
//
//  Created by Spencer Millican on 9/2/17.
//  Copyright © 2017 Auburn University. All rights reserved.
//

#ifndef Global_hpp
#define Global_hpp

//#include <stdio.h>

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#include <string>
#include <cstdlib>
#include <ctime>
#include <limits.h>

extern clock_t timer;

extern long int limit;

void err(std::string to_print);

void dbg(std::string to_print, int level);

#endif /* Global_hpp */
#pragma once
