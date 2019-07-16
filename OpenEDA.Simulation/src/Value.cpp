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
	valid_ = (T)0x0000000000000000;
}

template<class T>
Value<T>::Value(T _magnitude, T _valid, T _min, T _max) {
	magnitude_ = _magnitude;
	valid_ = _valid;
	min_ = _min;
	max_ = _max;
}

template<class T>
bool Value<T>::operator==(const Value<T>& _other) const {
	if ((this->valid() & _other.valid()) == (T)0x0) {
		return false;
	}
	//DELETE: obsolete by previous statement.
	/*if (_other.valid() == 0x0) {
		return false;
	}*/
	return (this->magnitude() & this->valid()) == (_other.magnitude() & _other.valid());
}

template<class T>
bool Value<T>::operator!=(const Value<T>& _other) const {
	//return !(*this == _other);
	if ((this->valid() & _other.valid()) == (T)0x0) {
		return false;
	}
	/*if (_other.valid() == 0x0) {
		return false;
	}*/
	return (this->magnitude() & this->valid()) != (_other.magnitude() & _other.valid());
}

template<class T>
bool Value<T>::operator<(const Value<T>& _other) const {
	//if (this->valid() == false | _other.valid() == false) {
	if (this->valid() & _other.valid() != (T)0xFFFFFFFFFFFFFFFF) {
		throw "Cannot compare '<' of two values if one is not valid.";
	}
	return this->magnitude() < _other.magnitude();
}

//template<class T>
//Value<T> Value<T>::operator&(const Value<T>& _other) const {
//	bool valid = true;
//	if (this->valid_ == false) {
//		valid = false;
//	} else if (this->magnitude_ == (T) 0) {
//		return Value<T>((T)0, true);
//	}
//	if (_other.valid() == false) {
//		valid = false;
//	} else if (_other.magnitude() == (T)0) {
//		return Value<T>((T)0, true);
//	}
//	return Value<T>((T)1, valid);
//}
//
//template<class T>
//Value<T> Value<T>::operator|(const Value<T>& _other) const {
//	bool valid = true;
//	if (this->valid_ == false) {
//		valid = false;
//	} else if (this->magnitude_ == (T)1) {
//		return Value<T>((T)1, true);
//	}
//	if (_other.valid() == false) {
//		valid = false;
//	} else if (_other.magnitude() == (T)1) {
//		return Value<T>((T)1, true);
//	}
//	return Value<T>((T)0, valid);
//}
//
//template<class T>
//Value<T> Value<T>::operator^(const Value<T>& _other) const {
//	if (this->valid_ == false || _other.valid() == false) {
//		return Value<T>((T)0, false);
//	} 
//	if (this->magnitude_ == _other.magnitude()) {
//		return Value<T>((T)0, true);
//	}
//	return Value<T>((T)1, true);
//}

template<class T>
Value<T> Value<T>::operator~() const {
	return Value<T>(~this->magnitude_, this->valid_);
}

//Technically, the "~" operator does not function properly on bool:
//https://stackoverflow.com/questions/29402367/does-using-bitwise-not-operator-on-boolean-values-invoke-undefined-behavior
template<>
Value<bool> Value<bool>::operator~() const {
	return Value<bool>(!this->magnitude_, this->valid_);
}

//DELETE obsolete
//template<class T>
//bool Value<T>::possiblyDifferent(const Value<T> _value1, const Value<T> _value2) {
//	if ((_value1.valid() == false || _value2.valid()) == false) { return true; }
//	if (_value1 != _value2) { return true; }
//	return false;
//}

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
T Value<T>::valid() const {
	return this->valid_;
}

template<class T>
T Value<T>::valid(T _valid) {
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

template<>
bool Value<unsigned long long int>::increment() {
	if (this->magnitude_) { //there's a 1
		this->magnitude_ = 0x0000000000000000;
		return true;
	}
	this->magnitude_ = 0xFFFFFFFFFFFFFFFF;
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
Value<T> Valued<T>::value(std::vector<Value<T>> _value) {
	if (_value.size() != 1) {
		throw "Cannot set value: one Value should be given.";
	}
	this->value_ = _value.at(0);
	return this->value_;
}

template class Valued<bool>;
template class Valued<unsigned long long int>;
template class Value<bool>;
template class Value<unsigned long long int>;