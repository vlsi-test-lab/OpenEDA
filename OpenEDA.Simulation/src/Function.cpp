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
		 throw "Invalid: there is not 'default' Boolean function.";
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
	} else if (_functionString == "not") {
		function_ = &BooleanFunction::NOT;
	} else {
		throw "Cannot create Boolean function from this string." ;
	}
}

//-------------- Boolean Function Definitions

Value<bool> BooleanFunction::evaluate(std::vector<Value<bool>> _vector) const {
	return (this->*function_)(_vector);
}

Value<bool> BooleanFunction::AND(std::vector<Value<bool>> i) const {
	bool valid = true;
	if (i.size() < 1) {
		throw "Input to a boolean function must have at least one value.";
	}
	for (auto &val : i) {
		if (val.magnitude() == false && val.valid() == true) {
			return Value<bool>(false);
		}
		if (val.valid() == false) {
			valid = false; break;
		}
	}
	return Value<bool>(true, valid);
}

Value<bool> BooleanFunction::NAND(std::vector<Value<bool>> i) const {
	return BooleanFunction::NOT(std::vector<Value<bool>>(1, BooleanFunction::AND(i)));
}

Value<bool> BooleanFunction::OR(std::vector<Value<bool>> i) const {
	bool valid = true;
	if (i.size() < 1) {
		throw "Input to a boolean function must have at least one value.";
	}
	for (auto &val : i) {
		if (val.magnitude() == true && val.valid() == true) {
			return Value<bool>(true);
		}
		if (val.valid() == false) {
			valid = false; break;
		}
	}
	return Value<bool>(false, valid);
}

Value<bool> BooleanFunction::NOR(std::vector<Value<bool>> i) const {
	return BooleanFunction::NOT(std::vector<Value<bool>>(1, BooleanFunction::OR(i)));
}

Value<bool> BooleanFunction::XOR(std::vector<Value<bool>> i) const {
	if (i.size() < 1) {
		throw "Input to a boolean function must have at least one value." ;
	}
	bool ret = false; bool valid = true;
	for (auto &val : i) {
		ret = ret ^ val.magnitude();
		if (val.valid() == false) {
			valid = false; break;
		}
	}
	return Value<bool>(ret, valid);
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
	return Value<bool>(!(i.at(0).magnitude()), i.at(0).valid());
}

template<class T>
CopyFunction<T>::CopyFunction(std::string _name) : Function<T>(_name) {
}

template<class T>
Value<bool> CopyFunction<T>::evaluate(std::vector<Value<bool>> _vector) const {
	if (_vector.size() == 0) {
		return this->value();
	}
	return _vector.at(0);
}

template class CopyFunction<bool>;

template<class T>
Functioned<T>::Functioned() {
	this->function_ = nullptr;
}

template<class T>
Functioned<T>::Functioned(Function<T>* _function, std::unordered_set<Connecting*> _inputs, std::unordered_set<Connecting*> _outputs) : Connecting(_inputs, _outputs){
	this->function_ = _function;
}

template<class T>
Functioned<T>::~Functioned() {
	if (this->function_ != nullptr) {
		delete this->function_;
	}
}

template<class T>
Value<T> Functioned<T>::evaluate() {
	std::vector<Value<T>> inputValues;
	std::unordered_set<Connecting*> inputs = this->inputs();
	for (Connecting* input : inputs) {
		Valued<T>* valuedCastInput = dynamic_cast<Valued<T>*>(input);
		Value<T> inputValue = valuedCastInput->value();
		inputValues.push_back(inputValue);
	}
	return this->function_->evaluate(inputValues);
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