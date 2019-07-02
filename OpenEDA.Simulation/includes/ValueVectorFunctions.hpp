/**
 * @file ValueVectorFunctions.hpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-15
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef ValueVectorFunctions_h
#define ValueVectorFunctions_h

#include <vector>
#include <random>
#include <algorithm> //rotate

#include "Value.h"

 /*
  * A static container for Value-containing vector manipulation.
  *
  * @param The underlying data primitive of Values.
  */
template <class _primitive>
class ValueVectorFunction {
public:
	/*
	 * Return true if two vectors of Values "mismatch" (two values are known and not equal).
	 *
	 * An exception will be thrown if the two vectors ar not the same size.
	 *
	 * @param a The first vector to compare.
	 * @param b The second vector to compare.
	 * @param (optional) _compare A vector corresponding to the values to compare (false = do not compare).
	 *        If not given, all values will be compared.
	 * @return True if the two values (with unkowns) cannot be equal.
	 */
	static bool mismatch(
		const std::vector<Value<_primitive>> a,
		const std::vector<Value<_primitive>> b,
		std::vector<bool> _compare = std::vector<bool>()
	) {
		if (a.size() != b.size()) {
			throw "Cannot compare two value vectors of different sizes.";
		}
		if (_compare.empty() == true) {
			_compare = std::vector<bool>(a.size(), true);
		} else if (_compare.size() != a.size()) {
			throw "Cannot compare two value vectors: comparison vector does not match the given vector sizes.";
		}
		for (unsigned int i = 0; i < a.size(); i++) {
			if (_compare.at(i) == false) {
				continue;
			}
			Value<_primitive> aValue = a.at(i);
			Value<_primitive> bValue = b.at(i);
			if (aValue != bValue) {
				return true;
			}
			//DELETE: this is now obsolete with non-bool values.
			/*if (a.at(i).valid() == true && b.at(i).valid() == true) {
				if (a.at(i).magnitude() != b.at(i).magnitude()) {
					return true;
				}
			}*/
		}
		return false;
	}

	/*
	 * "Backtrack" a vector of values. Return false if it can no longer be back-tracked.
	 *
	 * In this context, "backtrack" means (attempt to) skip to the next possible
	 * entry in a binary progression without incrementing.
	 *
	 * @param val Entry to backtrack.
	 * @return False if the entry cannot be backtracked.
	 */
	static bool backtrack(std::vector<Value<_primitive>> & val) {
		int index = -1;

		//First, find the largest index which has a valid value.
		for (size_t i = 0; i < val.size(); i++) {
			if (val.at(i).valid()) {
				index = i;
			} else {
				break;
			}
		}

		//Then work backwards trying to flip the value.
		while (index >= 0) {
			if (val.at(index).increment() == false) {
				return true;
			}
			val.at(index).valid(false);
			index--;
		}
		return false;
	}

	/*
	 * "Forward track" a vector. Return false if it cannot be done.
	 * 
	 * In this context, "forward track" is not increment. Instead, move the vector
	 * to the next place in a binary tree progression.
	 *
	 * @param val Entry to forward track.
	 * @return False if the entry cannot be forward trawked (i.e., the vector is full). 
	 */
	static bool forwardtrack(std::vector<Value<_primitive>> & val) {
		int index = -1;
		for (size_t i = 0; i < val.size(); i++) {
			if (val.at(i).valid() == false) {
				index = i; break;
			}
		}
		if (index < 0) {
			return false;
		} //All elements fillled, no forward track can be done.
		val.at(index).valid(true); val.at(index).magnitude(val.at(index).min());
		return true;
	}


	/*
	 * Increment the vector while holding a given value.
	 *
	 * An exception may be thrown if a non-valid Value is present.
	 *
	 * @param _vec The vector to increment.
	 * @param _hold The value to hold (i.e., skip). If not given, no Values will be skipped.
	 * @return False if the vector "rolled over".
	 */
	static bool increment(std::vector <Value<_primitive>> & _vec, int _hold = -1) {
		_primitive CONSTANTS[6] = {
			0xAAAAAAAAAAAAAAAA, //1010
			0xCCCCCCCCCCCCCCCC, //1100
			0xF0F0F0F0F0F0F0F0, //00001111
			0xFF00FF00FF00FF00,
			0xFFFF0000FFFF0000,
			0xFFFFFFFF00000000
		};

		_primitive valids = validMask(_vec.size());
		for (std::size_t i = 0; i < _vec.size(); i++) {
			if (i == _hold) { continue;	}
			if (i < numConstantFields()) {
				_vec[i] = Value<_primitive>(CONSTANTS[i], valids);
				continue;
			}
			//DELETE: Will no longer check for valid values.
			/*if (_vec.at(i).valid() == false) {
				throw "A vector with a non-valid value cannot be incremented.";
			}*/
			if (_vec.at(i).magnitude() == (_primitive)0x0) { //It's a 0: flip it an return.
				_vec.at(i).magnitude((_primitive)0xFFFFFFFFFFFFFFFF);
				return true;
			} else {
				_vec.at(i).magnitude((_primitive)0x0000000000000000);
			}
		}
		return false;
	}

	/*
	 * Create a random vector with a given (optional) set of weights.
	 *
	 * If no weight set is given, "even weights" (i.e., pure random) will be returned.
	 *
	 * If the size given does not equal the number of weights, throw an error.
	 *
	 * @param _size The size of the vector to return.
	 * @param (optional) _weights The weight assigned to each input, by default, "50%".
	 * @return The generated random vector.
	 */
	static std::vector<Value<_primitive>> random(size_t _size, std::vector<float> _weights = std::vector<float>());

	/*
	 * Shift a vector left.
	 *
	 * Vectors will be shifted towards 0, i.e., the LSB will be destroyed
	 * (returned) and the MSB will become the given value.
	 *
	 * @param (reference) _vector The vector to shift left.
	 * @param _input The new value to shift in as the new MSB.
	 * @return The previously LSB of the vector.
	 */
	static Value<_primitive> shift(std::vector<Value<_primitive>> & _vector, Value<_primitive> _input) {
		std::rotate(_vector.begin(), _vector.begin() + 1, _vector.end());
		Value<_primitive> toReturn = _vector.back(); _vector.pop_back();
		_vector.push_back(_input);
		return toReturn;
	}

private:
	/*
	 * For increment, return the number of "constant fields".
	 */
	static size_t numConstantFields();

	

	/*
	 * For increment, return a "partial valid" mask for a given number of inputs.
	 *
	 * @param _inputs The number of inputs which are being incremented.
	 */
	static _primitive validMask(size_t _inputs) {
		/*
		 * The valid masks for a given input size.
		 */
		_primitive VALID_MASKS [7] = {
			0x0000000000000001, //0 input (which doesn't make sense)
			0x0000000000000003, //1 input : 01
			0x000000000000000F, //2 inputs : 0101
			0x00000000000000FF, //3
			0x000000000000FFFF, //4
			0x00000000FFFFFFFF, //5
			0xFFFFFFFFFFFFFFFF  //6 (and more)
		};
		_inputs = (_inputs > 6) ? 6 : _inputs; //Max out at 6.
		return VALID_MASKS[_inputs];
	}

};

template<>
inline size_t ValueVectorFunction<bool>::numConstantFields() {
	return 0;
}

template<>
inline size_t ValueVectorFunction<unsigned long long int>::numConstantFields() {
	return 6;
}

template<>
inline std::vector<Value<bool>> ValueVectorFunction<bool>::random(size_t _size, std::vector<float> _weights) {
	if (_weights.size() == 0) {
		_weights = std::vector<float>(_size, 0.5);
	}
	if (_size != _weights.size()) {
		throw "Cannot generate random vector: incorrect number of weights given";
	}
	std::vector<Value<bool>> toReturn;
	static std::default_random_engine e;
	for (size_t a = 0; a < _weights.size(); a++) {
		std::bernoulli_distribution b(_weights.at(a));
		toReturn.push_back(Value<bool>(b(e)));
	}
	return toReturn;
}

template<>
inline std::vector<Value<unsigned long long int>> ValueVectorFunction<unsigned long long int>::random(size_t _size, std::vector<float> _weights) {
	if (_weights.size() == 0) {
		_weights = std::vector<float>(_size, 0.5);
	}
	if (_size != _weights.size()) {
		throw "Cannot generate random vector: incorrect number of weights given";
	}
	std::vector<Value<unsigned long long int>> toReturn;
	static std::default_random_engine e;
	for (size_t a = 0; a < _weights.size(); a++) {
		//std::bernoulli_distribution b(_weights.at(a));
		unsigned long long int num = rand(); //Only 16 bits, because, why not make things confusing.
		num = num << 16; num = num | rand();
		num = num << 16; num = num | rand();
		num = num << 16; num = num | rand();
		toReturn.push_back(Value<unsigned long long int>(num));
	}
	return toReturn;
}

#endif