/**
 * @file Function.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2018-12-25
 *
 * @copyright Copyright (c) 2018
 *
 */

#ifndef Function_h
#define Function_h

#include <string>
#include <vector>

#include <algorithm> //std::transform
#include <cctype> //std::tolower

#include "Value.h"
#include "Connection.h"

/*
 * A representation of a output-generating function.
 *
 * A function takes in a vector of inputs and translates them into an output.
 * 
 * The template parameter indicates the underlying primitive which implements 
 * the function (e.g., bool, char, etc.).
 */
template <class T>
class Function {
public:
	/*
	 * Create the Function with a given name.
	 *
	 * @param _name The name of the Function.
	 */
	Function(std::string _name) {
		std::transform(_name.begin(), _name.end(), _name.begin(), (int(*)(int))std::tolower);
		this->name_ = _name;
	}

	/*
	 * "Clone constructor".
	 *
	 * @return A copy of this Function object (as a function).
	 */
	virtual Function<T>* clone() const = 0;

	/*
	 * For a given input vector, return an output.
	 *
	 * @param _vector The input vector of Values to evaluate.
	 * @return The output corresponding to the input vector.
	 */
	virtual Value<T> evaluate(std::vector<Value<T>> _vector) const = 0;

	/*
	 * The function as a string.
	 *
	 * The function will be retruned as a string "e.g., 'and'".
	 *
	 * All returned values will be lower case.
	 *
	 * @return The Function name.
	 */
	std::string string() const {
		return this->name_;
	}

private:
	/*
	 * The name of the Function
	 */
	std::string name_;
};

/*
 * A Boolean function.
 *
 * This class implements a Boolean function which is evaluated algorithmically.
 *
 * @param _width The "width" of the Boolean function (i.e., how many bits to process at once).
 */
template <class _width>
class BooleanFunction : public Function<_width> {
public:
	/*
	 * Will throw an exception: there is no "undefined" Boolean function.
	 */
	BooleanFunction();


	/*
	 * Create a boolean function given a string (i.e., AND, OR, etc).
	 *
	 * The given string will determine the Boolean function implemented.
	 *
	 * @param String which determines the Boolean function.
	 */
	BooleanFunction(std::string _functionString);

	/*
	 * Copy constructor.
	 *
	 * @param _obj The function to copy.
	 */
	BooleanFunction(const BooleanFunction & _obj);

	/*
	 * "Clone constructor".
	 *
	 * @return A copy of this Function object (as a function).
	 */
	virtual Function<_width>* clone() const;

	/*
	 * For a given input vector, return an output.
	 *
	 * @param _vector The input vector of Values to evaluate.
	 * @return The output corresponding to the input vector.
	 */
	virtual Value<_width> evaluate(std::vector<Value<_width>> _vector) const;

private:

	/*
	 * The following are the separate (possible) primitive Booelan functions.
	 */
	Value<_width> AND(std::vector<Value<_width>>) const;
	Value<_width> OR(std::vector<Value<_width>>) const;
	Value<_width> NAND(std::vector<Value<_width>>) const;
	Value<_width> NOR(std::vector<Value<_width>>) const;
	Value<_width> XOR(std::vector<Value<_width>>) const;
	Value<_width> XNOR(std::vector<Value<_width>>) const;
	Value<_width> BUF(std::vector<Value<_width>>) const;
	Value<_width> NOT(std::vector<Value<_width>>) const;

	/*
	 * This function pointer holds the Boolean function implemented by this function.
	 */
	Value<_width>(BooleanFunction::*function_)(std::vector<Value<_width>>) const;

};

/*
 * A "copy/constant value" Function.
 *
 * This Function is best used for setting perminant values, implementing PIs,
 * and implementing POs.
 *
 * The "evaluation" function will copy input Values.
 *
 * The function behavior is undefined if more than one input Value is given.
 *
 * The template parameter is the data primitive of the underlying Value.
 */
template <class T>
class CopyFunction : public Function<T> , public Valued<T> {
public:
	/*
	 * Create a CopyFunction of a given name.
	 *
	 * Typical names will be "const", "pi", "po", etc.
	 *
	 * @param Name the name of the  the function
	 * @param (optional) The constant value of this function. If it is not
	 *        defined (or an "invalid" value is given), the function will always
	 *        copy the values given to it. Otherwise, the returned value will
	 *        always be the value given.
	 */
	CopyFunction(std::string _name, Value<T> _value = Value<T>());

	/*
	 * Copy constructor.
	 *
	 * @param _obj The object to copy
	 */
	CopyFunction(const CopyFunction<T> & _obj);

	/*
	 * "Clone constructor".
	 *
	 * @return A copy of this Function object (as a function).
	 */
	virtual Function<T>* clone() const;

	/*
	 * Evaluate the Function.
	 * 
	 * If this CopyFunction has a Value assigned to it and no input, this Value
	 * will be returned. Else, the given Value will be given.
	 *
	 * If more than one input value is given, the returned Value is uncertain.
	 *
	 * @param _vector The input vector of Values to evaluate.
	 * @return The output corresponding to the input vector.
	 */
	virtual Value<T> evaluate(std::vector<Value<T>> _vector) const;


};

/*
 * An object which contains a Function.
 *
 * A Functioned object contains a Function, to which can be called to evaluate.
 *
 * The template paramter indicates the underlying data primitive of the 
 * Function.
 */
template <class T>
class Functioned : public virtual Valued<T>  {
public:
	/*
	 * The default Functioned object is connected no nothing and has no (nullptr) function.
	 */
	Functioned();

	/*
	 * Initialize with the given Function, inputs, and outputs.
	 *
	 * @param _function The Function of this object.
	 * @param _inputs The input Connecting objects of this object.
	 * @param _outputs The output Connecting objects of this object.
	 */
	Functioned(Function<T>* _function);

	/*
	 * Copy constructor.
	 *
	 * A heap copy of the function will be created.
	 *
	 * @param _obj Object to copy.
	 */
	Functioned(const Functioned<T> & _obj);

	/*
	 * Delete this Functioned object.
	 *
	 * This object's Function will also be deleted.
	 */
	~Functioned();

	/*
	 * Return the last evaulation of this Function.
	 *
	 * @return The last Value created by this Function.
	 */
//DELETE note needed: function is same as inherited.	virtual Value<T> value() const;

	/*
	 * Evaluate this function.
	 *
	 * The given vector will be passed to this object's Function. The value held
	 * by this function will also be set.
	 *
	 * @param _value The vector to evaluate.
	 * @return The output of the function.
	 */
	virtual Value<T> value(std::vector<Value<T>> _value);

	/*
	 * Returns this object's Function.
	 *
	 * @return This object's Function.
	 */
	Function<T>* function() const;

	/*
	 * Set this object's Function.
	 *
	 * If this object already has a Function, the old one will be deleted.
	 *
	 * @return This object's Function (after assignment)
	 */
	Function<T>* function(Function<T>* _function);

protected:
	/*
	 * The Function of this Functioned object.
	 *
	 * Upun destruction, it will be deleted.
	 */
	Function<T>* function_;
};

#endif