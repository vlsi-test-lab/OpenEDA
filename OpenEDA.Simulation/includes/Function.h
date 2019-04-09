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
 */
class BooleanFunction : public Function<bool> {
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
	 * For a given input vector, return an output.
	 *
	 * @param _vector The input vector of Values to evaluate.
	 * @return The output corresponding to the input vector.
	 */
	virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;

private:

	/*
	 * The following are the separate (possible) primitive Booelan functions.
	 */
	Value<bool> AND(std::vector<Value<bool>>) const;
	Value<bool> OR(std::vector<Value<bool>>) const;
	Value<bool> NAND(std::vector<Value<bool>>) const;
	Value<bool> NOR(std::vector<Value<bool>>) const;
	Value<bool> XOR(std::vector<Value<bool>>) const;
	Value<bool> XNOR(std::vector<Value<bool>>) const;
	Value<bool> BUF(std::vector<Value<bool>>) const;
	Value<bool> NOT(std::vector<Value<bool>>) const;

	/*
	 * This function pointer holds the Boolean function implemented by this function.
	 */
	Value<bool>(BooleanFunction::*function_)(std::vector<Value<bool>>) const;
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
	 */
	CopyFunction(std::string _name);

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
	virtual Value<bool> evaluate(std::vector<Value<bool>> _vector) const;


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