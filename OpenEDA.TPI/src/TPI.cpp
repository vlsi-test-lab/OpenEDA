/**
 * @file TPI.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-19
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "TPI.h"

template<class _primitive>
std::set<Testpoint<_primitive>> TPI<_primitive>::testpoints(
		std::vector<std::set<Testpoint<_primitive>>> _testpoints,
		std::vector<size_t> _limits
) {
	this->resetTimer();
	size_t curNumberTestpoints = 0;
	std::vector<size_t> numInserted = std::vector<size_t>(_testpoints.size(), 0);
	float curQuality = -1;
	std::set<Testpoint<_primitive>> inserted;

	if (_limits.size() == 0) {
		_limits = std::vector<size_t>(_testpoints.size(), std::numeric_limits<size_t>::max());
	}
	if (_limits.size() != _testpoints.size()) {
		throw "Testpoint insertion limits to not match the number of testpoint sets.";
	}


	while (
		this->timeUp() == false && 
		curNumberTestpoints < this->TPLimit_ &&
		curQuality < this->qualityLimit_
		   )
	{
		float bestQuality = -1;
		Testpoint<_primitive> bestTestpoint;
		size_t bestSet = 0;
		for (size_t i = 0; i < _testpoints.size(); i++) {
			if (numInserted.at(i) >= _limits.at(i)) { //Skip: set limit reached.
				continue;
			}
			std::pair<Testpoint<_primitive>, float> best = this->bestTestpoint(_testpoints.at(i));
			if (best.second > bestQuality) {
				bestQuality = best.second;
				bestTestpoint = best.first;
				bestSet = i;
			}
		}
		if (bestQuality < 0) {//No more TPs to add: no positive quality.
			break;
		}
		inserted.emplace(bestTestpoint);
		_testpoints.at(bestSet).erase(bestTestpoint);
	}

	return inserted;
}

template<class _primitive>
void TPI<_primitive>::timeLimit(size_t _timeLimit) {
	this->timeLimit_ = _timeLimit;
	this->resetTimer();
}

template<class _primitive>
void TPI<_primitive>::testpointLimit(size_t _testpointLimit) {
	this->TPLimit_ = _testpointLimit;
}

template<class _primitive>
std::pair<Testpoint<_primitive>, float> TPI<_primitive>::bestTestpoint(std::set<Testpoint<_primitive>> _testpoints) {
	float bestQuality = -1;
	Testpoint<_primitive> bestTestpoint;
	for (Testpoint<_primitive> curTestpoint : _testpoints) {
		float quality = this->quality(curTestpoint);
		if (quality > bestQuality) {
			bestQuality = quality;
			bestTestpoint = curTestpoint;
		}
	}
	return std::pair<Testpoint<_primitive>, float>(bestTestpoint, bestQuality);
}

template<class _primitive>
void TPI<_primitive>::resetTimer() {
	this->endTime_ = std::clock() + (this->timeLimit_ * CLOCKS_PER_SEC);
}

template<class _primitive>
bool TPI<_primitive>::timeUp() {
	return clock() > this->endTime_;
}
