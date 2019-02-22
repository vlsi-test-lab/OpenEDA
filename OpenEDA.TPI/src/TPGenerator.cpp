/**
 * @file TPGenerator.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-22
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "TPGenerator.h"

#include "Testpoint_control.h"
#include "Testpoint_observe.h"
#include "Testpoint_invert.h"

template<>
static std::set<Testpoint_observe<bool>> TPGenerator<Testpoint_observe<bool>, bool>::allTPs(FaultyLine<bool>* _line) {
	std::set<Testpoint_observe<bool>> toReturn;
	toReturn.emplace(Testpoint_observe<bool>(_line));
	return toReturn;
}

template<>
static std::set<Testpoint_control<bool>> TPGenerator<Testpoint_control<bool>, bool>::allTPs(FaultyLine<bool>* _line) {
	std::set<Testpoint_control<bool>> toReturn;
	toReturn.emplace(Testpoint_control<bool>(Value<bool>(false), _line));
	toReturn.emplace(Testpoint_control<bool>(Value<bool>(true), _line));
	return toReturn;
}

template<>
static std::set<Testpoint_invert<bool>> TPGenerator<Testpoint_invert<bool>, bool>::allTPs(FaultyLine<bool>* _line) {
	std::set<Testpoint_invert<bool>> toReturn;
	toReturn.emplace(Testpoint_invert<bool>(_line));
	return toReturn;
}