/**
 * @file Function.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2018-12-25
 *
 * @copyright Copyright (c) 2018
 *
 */

#include "Function.h"

#include <algorithm> //std::transform
#include <cctype> //std::tolower

template<class _width>
 BooleanFunction<_width>::BooleanFunction() : Function<_width>("invalid") {
		 throw "Invalid: there is no 'default' Boolean function.";
 }

 template<class _width>
 BooleanFunction<_width>::BooleanFunction(std::string _functionString) : Function<_width>(_functionString) {
	function_ = &BooleanFunction::BUF; //Overwritten, so it does not matter.  This prevents "uninitialized member" analysis.
	std::transform(_functionString.begin(), _functionString.end(), _functionString.begin(), (int(*)(int))std::tolower);
	if (_functionString == "and") {
		function_ = &BooleanFunction::AND;
	} else if (_functionString == "nand") {
		function_ = &BooleanFunction::NAND;
	} else if (_functionString == "or") {
		function_ = &BooleanFunction::OR;
	} else if (_functionString == "nor") {
		function_ = &BooleanFunction::NOR;
	} else if (_functionString == "xor") {
		function_ = &BooleanFunction::XOR;
	} else if (_functionString == "xnor") {
		function_ = &BooleanFunction::XNOR;
	} else if (_functionString == "buf") {
		function_ = &BooleanFunction::BUF;
	} else if (_functionString == "buff") {
		function_ = &BooleanFunction::BUF;
	} else if (_functionString == "copy") {
		function_ = &BooleanFunction::BUF;
	} else if (_functionString == "not") {
		function_ = &BooleanFunction::NOT;
	} 
	
	else {
		throw "Cannot create Boolean function from this string." ;
	}
}

 template<class _width>
 BooleanFunction<_width>::BooleanFunction(const BooleanFunction & _obj) : Function<_width>(_obj.string()) {
	 std::string _functionString = _obj.string();
	 function_ = &BooleanFunction::BUF; //Overwritten, so it does not matter.  This prevents "uninitialized member" analysis.
	 std::transform(_functionString.begin(), _functionString.end(), _functionString.begin(), (int(*)(int))std::tolower);
	 if (_functionString == "and") {
		 function_ = &BooleanFunction::AND;
	 } else if (_functionString == "nand") {
		 function_ = &BooleanFunction::NAND;
	 } else if (_functionString == "or") {
		 function_ = &BooleanFunction::OR;
	 } else if (_functionString == "nor") {
		 function_ = &BooleanFunction::NOR;
	 } else if (_functionString == "xor") {
		 function_ = &BooleanFunction::XOR;
	 } else if (_functionString == "xnor") {
		 function_ = &BooleanFunction::XNOR;
	 } else if (_functionString == "buf") {
		 function_ = &BooleanFunction::BUF;
	 } else if (_functionString == "buff") {
		 function_ = &BooleanFunction::BUF;
	 } else if (_functionString == "copy") {
		 function_ = &BooleanFunction::BUF;
	 } else if (_functionString == "not") {
		 function_ = &BooleanFunction::NOT;
	 }

	 else {
		 throw "Cannot create Boolean function from this string.";
	 }
 }

 template<class _width>
 Function<_width>* BooleanFunction< _width>::clone() const {
	 return new BooleanFunction<_width>(*this);
 }

//-------------- Boolean Function Definitions

 template<class _width>
Value<_width> BooleanFunction<_width>::evaluate(std::vector<Value<_width>> _vector) const {
	return (this->*function_)(_vector);
}

template<class _width>
Value<_width> BooleanFunction<_width>::AND(std::vector<Value<_width>> i) const {
	if (i.size() < 1) {
		throw "Input to a boolean function must have at least one value.";
	}
	_width mag = 0xFFFFFFFFFFFFFFFF;
	_width valid = 0xFFFFFFFFFFFFFFFF;
	for (Value<_width> &val : i) {
		_width otherMag = val.magnitude();
		_width otherValid = val.valid();
		valid = (valid & otherValid) | (otherValid & ~otherMag) | (valid & ~mag);
		mag = mag & otherMag;
	}
	return Value<_width>(mag, valid);
}

template<class _width>
Value<_width> BooleanFunction<_width>::NAND(std::vector<Value<_width>> i) const {
	return BooleanFunction::NOT(std::vector<Value<_width>>(1, BooleanFunction::AND(i)));
}

template<class _width>
Value<_width> BooleanFunction<_width>::OR(std::vector<Value<_width>> i) const {
	if (i.size() < 1) {
		throw "Input to a boolean function must have at least one value.";
	}
	_width mag = 0x0;
	_width valid = 0xFFFFFFFFFFFFFFFF;
	for (Value<_width> &val : i) {
		_width otherMag = val.magnitude();
		_width otherValid = val.valid();
		valid = (valid & otherValid) | (otherValid & otherMag) | (valid & mag);
		mag = mag | otherMag;
	}
	return Value<_width>(mag, valid);
}

template<class _width>
Value<_width> BooleanFunction<_width>::NOR(std::vector<Value<_width>> i) const {
	return BooleanFunction::NOT(std::vector<Value<_width>>(1, BooleanFunction::OR(i)));
}

template<class _width>
Value<_width> BooleanFunction<_width>::XOR(std::vector<Value<_width>> i) const {
	if (i.size() < 1) {
		throw "Input to a boolean function must have at least one value." ;
	}
	_width mag = 0x0;
	_width valid = 0xFFFFFFFFFFFFFFFF;
	for (Value<_width> &val : i) {
		_width otherMag = val.magnitude();
		_width otherValid = val.valid();
		valid = (valid & otherValid);
		mag = mag ^ otherMag;
	}
	return Value<_width>(mag, valid);
}

template<class _width>
Value<_width> BooleanFunction<_width>::XNOR(std::vector<Value<_width>> i) const {
	return BooleanFunction::NOT(std::vector<Value<_width>>(1, BooleanFunction::XOR(i)));
}


template<class _width>
Value<_width> BooleanFunction<_width>::BUF(std::vector<Value<_width>> i) const {
	if (i.size() > 1) {
		throw "Cannot buffer more than 1 value.";
	}
	if (i.size() < 1) {
		throw "Input to a boolean function must have at least one value." ; 
	}
	return i.at(0);
}

template<class _width>
Value<_width> BooleanFunction<_width>::NOT(std::vector<Value<_width>> i) const {
	if (i.size() > 1) {
		throw "Cannot invert more than 1 value." ;
	}
	if (i.size() < 1) {
		throw "Input to a boolean function must have at least one value." ;
	}
	return ~i.at(0);
	//DELETE obsolete. return Value<bool>(!(i.at(0).magnitude()), i.at(0).valid());
}

template<class T>
CopyFunction<T>::CopyFunction(std::string _name, Value<T> _value) : Function<T>(_name) , Valued<T>(_value){
}

template<class T>
CopyFunction<T>::CopyFunction(const CopyFunction<T> & _obj) : Function<T>(_obj.string()) , Valued<T>(_obj.value()) {
}

template<class T>
Function<T>* CopyFunction<T>::clone() const {
	return new CopyFunction<T>(*this);
}

template<class T>
Value<T> CopyFunction<T>::evaluate(std::vector<Value<T>> _vector) const {
	if (this->value().valid() == true) {
		return this->value();
	}
	if (_vector.size() == 0) {
		throw "CopyFunction cannot return a vector with nothing to copy.";
	}
	return _vector.at(0);
}



template<class T>
Functioned<T>::Functioned() {
	this->function_ = nullptr;
}

template<class T>
Functioned<T>::Functioned(Function<T>* _function) {
	this->function_ = _function;
}

template<class T>
Functioned<T>::Functioned(const Functioned<T>& _obj) {
	this->function_ = _obj.function()->clone();
}

template<class T>
Functioned<T>::~Functioned() {
	if (this->function_ != nullptr) {
		delete this->function_;
	}
}

template<class T>
Value<T> Functioned<T>::value(std::vector<Value<T>> _value) {
	this->Valued<T>::value(
		std::vector<Value<T>>(1, this->function_->evaluate(_value))
	);
	return this->Valued<T>::value();

}

template<class T>
Function<T>* Functioned<T>::function() const {
	return this->function_;
}

template<class T>
Function<T>* Functioned<T>::function(Function<T>* _function) {
	this->function_ = _function;
	return this->function_;
}

template class Functioned<bool>;
template class BooleanFunction<bool>;
template class CopyFunction<bool>;

template class Functioned<unsigned long long int>;
template class BooleanFunction<unsigned long long int>;
template class CopyFunction<unsigned long long int>;