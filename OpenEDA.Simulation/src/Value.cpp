/**
 * @file Value.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2018-12-25
 *
 * @copyright Copyright (c) 2018
 *
 */

#include "Value.h"

template <class T>
Value<T>::Value() {
	min_ = std::numeric_limits<T>::min();
	max_ = std::numeric_limits<T>::max();
	magnitude_ = min_;
	valid_ = false;
}

template<class T>
Value<T>::Value(T _magnitude, bool _valid, T _min, T _max) {
	magnitude_ = _magnitude;
	valid_ = _valid;
	min_ = _min;
	max_ = _max;
}

template<class T>
bool Value<T>::operator==(const Value<T>& _other) const {
	if (this->valid() == false) {
		return false;
	}
	if (_other.valid() == false) {
		return false;
	}
	return this->magnitude() == _other.magnitude();
}

template<class T>
bool Value<T>::operator!=(const Value<T>& _other) const {
	return !(*this == _other);
}

template<class T>
bool Value<T>::operator<(const Value<T>& _other) const {
	if (this->valid() == false) {
		return false;
	}
	if (this->valid() == false) {
		return false;
	}
	return this->magnitude() < _other.magnitude();
}

template<class T>
bool Value<T>::different(const Value<T> _value1, const Value<T> _value2) {
	if ((_value1.valid() == false || _value2.valid()) == false) { return true; }
	if (_value1 != _value2) { return true; }
	return false;
}

template<class T>
T Value<T>::magnitude() const {
	return this->magnitude_;
}

template<class T>
T Value<T>::magnitude(T _magnitude) {
	if (_magnitude < this->min() || _magnitude > this->max()) {
		throw "Cannot set the magnitude of a Value out-of-bounds.";
	}
	this->magnitude_ = _magnitude;
	return _magnitude;
}

template<class T>
bool Value<T>::valid() const {
	return this->valid_;
}

template<class T>
bool Value<T>::valid(bool _valid) {
	this->valid_ = _valid;
	return _valid;
}

template<class T>
bool Value<T>::increment() {
	if (this->magnitude_ == this->max()) {
		this->magnitude_ = this->min();
		return true;
	}
	this->magnitude_ = this->magnitude_ + 1;
	return false;
}

template<class T>
T Value<T>::min() const {
	return this->min_;
}

template<class T>
T Value<T>::max() const {
	return this->max_;
}

template<class T>
unsigned long int Value<T>::cardinality() const {
	return (unsigned long int) this->max() - (unsigned long int) this->min() + 1;
}

template class Value<bool>;

template<class T>
Valued<T>::Valued() {
	this->value_ = Value<T>();
}

template<class T>
Valued<T>::Valued(Value<T> _value) {
	this->value_ = _value;
}

template<class T>
Value<T> Valued<T>::value() const {
	return this->value_;
}

template<class T>
Value<T> Valued<T>::value(Value<T> _value) {
	this->value_ = _value;
	return this->value_;
}

template class Valued<bool>;