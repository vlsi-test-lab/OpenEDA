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
	 * @return True if the two values (with unkowns) cannot be equal.
	 */
	static bool mismatch(const std::vector<Value<_primitive>> a, const std::vector<Value<_primitive>> b) {
		if (a.size() != b.size()) {
			throw "Cannot compare two value vectors of different sizes.";
		}
		for (unsigned int i = 0; i < a.size(); i++) {
			if (a.at(i).valid() == true && b.at(i).valid() == true) {
				if (a.at(i).magnitude() != b.at(i).magnitude()) {
					return true;
				}
			}
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
		for (size_t i = 0; i < val.size(); i++) {
			if (val.at(i).valid() == true) {
				index = i;
			} else {
				break;
			}
		}
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
		for (std::size_t i = 0; i < _vec.size(); i++) {
			if (i == _hold) {
				continue;
			}
			//DEL//wrong functionality. for (Value<T> val : _vec) {
			if (_vec.at(i).valid() == false) {
				throw "A vector with a non-valid value cannot be incremented.";
			}
			if (_vec.at(i).increment() == false) {
				return true;
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
	static std::vector<Value<_primitive>> random(size_t _size, std::vector<float> _weights = std::vector<float>(_size, 0.5)) {
		if (_size != _weights.size()) {
			throw "Cannot generate random vector: incorrect number of weights given";
		}
		std::vector<Value<_primitive>> toReturn;
		static std::default_random_engine e;
		for (size_t a = 0; a < _weights.size(); a++) {
			std::bernoulli_distribution b(_weights.at(a));
			toReturn.push_back(Value<_primitive>(b(e)));
		}
		return toReturn;
	}

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
};

#endif