/**
 * @file Function.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-05-06
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "PRPG.h"

template<class _primitive>
PRPG<_primitive>::PRPG(size_t _size, std::vector<Value<_primitive>> _seed) {
	if (_seed.size() == 0) { //No seed defined, create the "default"
		_seed = std::vector<Value<_primitive>>(31, Value<_primitive>((_primitive)1));
	}
	if (_seed.size() != 31) {
		throw "PRPG seed size must be 31 bits.";
	}

	this->lfsr_ = _seed;
	this->last_ = std::vector<Value<_primitive>>(_size, Value<_primitive>((_primitive)1));
	this->load();
}

template<class _primitive>
std::vector<Value<_primitive>> PRPG<_primitive>::increment() {
	std::vector<Value<_primitive>> XORedValues{ 
		this->lfsr_.at(0), //"0"
		this->lfsr_.at(3)  //"3"
	};
	BooleanFunction function = BooleanFunction("xor");
	Value<_primitive> newValue = function.evaluate(XORedValues);
	newValue = ValueVectorFunction<bool>::shift(this->lfsr_, newValue);
	ValueVectorFunction<bool>::shift(this->last_, newValue);

	return this->last_;
}

template<class _primitive>
std::vector<Value<_primitive>> PRPG<_primitive>::load() {
	for (size_t i = 0; i < this->last_.size() - 1; i++) { //NOTE: the "-1" is so the last value can be easily returned.
		this->increment();
	}
	return this->increment(); //NOTE: see the above note on "-1".
}

template class PRPG<bool>;