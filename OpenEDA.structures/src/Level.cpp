/**
 * @file Level.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2018-12-23
 *
 * @copyright Copyright (c) 2018
 *
 */

#include "Level.h"

#include <vector>

Levelized::Levelized() {
}

Levelized::Levelized(std::unordered_set<Connecting*> _inputs, std::unordered_set<Connecting*> _outputs) : Connecting(_inputs, _outputs){

}

int Levelized::inputLevel() {
	if (this->inputLevel_ >= 0) {
		return this->inputLevel_;
	}

	//Level is not known/does not exist, calculate it.
	std::vector<int> levels;
	for (Connecting* input : this->inputs()) {
		Levelized* castLevelized = static_cast<Levelized*>(input);
		levels.push_back(castLevelized->inputLevel());
	}
	int ret = this->levelCalculation(levels);
	if (ret < 0) {
		throw "Level could not be calculated.";
	}

	this->inputLevel_ = ret;
	return ret;
}

int Levelized::inputLevelConst() const {
	if (this->inputLevel_ >= 0) {
		return this->inputLevel_;
	}
	
	throw "Cannot return level without calculating.";
	return UNKNOWN_LEVEL;
}

void Levelized::inputLevelClear() {
	if (this->inputLevel_ < 0) {
		return; //Level has already been cleared.
	}

	this->inputLevel_ = UNKNOWN_LEVEL;
	for (Connecting* output : this->outputs()) {
		Levelized* castLevelized = static_cast<Levelized*>(output);
		castLevelized->inputLevelClear();
	}
}

void Levelized::inputLevelZero() {
	this->inputLevel_ = 0;
}

int Levelized::outputLevel() {
	if (this->outputLevel_ >= 0) {
		return this->outputLevel_;
	}

	//Level is not known/does not exist, calculate it.
	int ret = UNKNOWN_LEVEL;
	std::vector<int> levels;
	for (Connecting* output : this->outputs()) {
		Levelized* castLevelized = static_cast<Levelized*>(output);
		levels.push_back(castLevelized->outputLevel());
	}
	ret = this->levelCalculation(levels);
	if (ret < 0) {
		throw "Level could not be calculated.";
	}

	this->outputLevel_ = ret;
	return ret;
}

int Levelized::outputLevelConst() const {
	if (this->outputLevel_ >= 0) {
		return this->outputLevel_;
	}

	throw "Cannot return level without calculating.";
	return UNKNOWN_LEVEL;
}

void Levelized::outputLevelClear() {
	if (this->outputLevel_ <= 0) {
		return;
	}

	this->outputLevel_ = UNKNOWN_LEVEL;
	for (Connecting* input : this->inputs()) {
		Levelized* castLevelized = static_cast<Levelized*>(input);
		castLevelized->outputLevelClear();
	}
}

void Levelized::outputLevelZero() {
	this->outputLevel_ = 0;
}

int Levelized::levelCalculation(std::vector<int> _levels) {
	int toReturn = -2; //May be incremented to -1
	for (auto level : _levels) {
		toReturn = toReturn > level ? toReturn : level;
	}
	return toReturn + 1;
}
