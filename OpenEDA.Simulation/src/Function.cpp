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

 BooleanFunction::BooleanFunction() : Function<bool>("invalid") {
		 throw "Invalid: there is no 'default' Boolean function.";
 }

 BooleanFunction::BooleanFunction(std::string _functionString) : Function<bool>(_functionString) {
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

 BooleanFunction::BooleanFunction(const BooleanFunction & _obj) : Function<bool>(_obj.string()) {
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

 Function<bool>* BooleanFunction::clone() const {
	 return new BooleanFunction(*this);
 }

//-------------- Boolean Function Definitions

Value<bool> BooleanFunction::evaluate(std::vector<Value<bool>> _vector) const {
	return (this->*function_)(_vector);
}

Value<bool> BooleanFunction::AND(std::vector<Value<bool>> i) const {
	if (i.size() < 1) {
		throw "Input to a boolean function must have at least one value.";
	}
	bool mag = true;
	bool valid = true;
	for (Value<bool> &val : i) {
		bool otherMag = val.magnitude();
		bool otherValid = val.valid();
		valid = (valid & otherValid) | (otherValid & ~otherMag) | (valid & ~mag);
		mag = mag & otherMag;
	}
	return Value<bool>(mag, valid);
}

Value<bool> BooleanFunction::NAND(std::vector<Value<bool>> i) const {
	return BooleanFunction::NOT(std::vector<Value<bool>>(1, BooleanFunction::AND(i)));
}

Value<bool> BooleanFunction::OR(std::vector<Value<bool>> i) const {
	if (i.size() < 1) {
		throw "Input to a boolean function must have at least one value.";
	}
	bool mag = false;
	bool valid = true;
	for (Value<bool> &val : i) {
		bool otherMag = val.magnitude();
		bool otherValid = val.valid();
		valid = (valid & otherValid) | (otherValid & otherMag) | (valid & mag);
		mag = mag | otherMag;
	}
	return Value<bool>(mag, valid);
}

Value<bool> BooleanFunction::NOR(std::vector<Value<bool>> i) const {
	return BooleanFunction::NOT(std::vector<Value<bool>>(1, BooleanFunction::OR(i)));
}

Value<bool> BooleanFunction::XOR(std::vector<Value<bool>> i) const {
	if (i.size() < 1) {
		throw "Input to a boolean function must have at least one value." ;
	}
	bool mag = false;
	bool valid = true;
	for (Value<bool> &val : i) {
		bool otherMag = val.magnitude();
		bool otherValid = val.valid();
		valid = (valid & otherValid);
		mag = mag ^ otherMag;
	}
	return Value<bool>(mag, valid);
}

Value<bool> BooleanFunction::XNOR(std::vector<Value<bool>> i) const {
	return BooleanFunction::NOT(std::vector<Value<bool>>(1, BooleanFunction::XOR(i)));
}


Value<bool> BooleanFunction::BUF(std::vector<Value<bool>> i) const {
	if (i.size() > 1) {
		throw "Cannot buffer more than 1 value.";
	}
	if (i.size() < 1) {
		throw "Input to a boolean function must have at least one value." ; 
	}
	return i.at(0);
}

Value<bool> BooleanFunction::NOT(std::vector<Value<bool>> i) const {
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
Value<bool> CopyFunction<T>::evaluate(std::vector<Value<bool>> _vector) const {
	if (this->value().valid() == true) {
		return this->value();
	}
	if (_vector.size() == 0) {
		throw "CopyFunction cannot return a vector with nothing to copy.";
	}
	return _vector.at(0);
}

template class CopyFunction<bool>;

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