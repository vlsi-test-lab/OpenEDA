/**
 * @file Value.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2018-12-24
 *
 * @copyright Copyright (c) 2018
 *
 */

#ifndef Value_h
#define Value_h

#include <limits>
#include <vector>

/*
 * A simultable value.
 *
 * A Value holds a value created during simulation. As opposed to raw data
 * types (bool, char, float, etc.), a Value holds extra informationa and has
 * support functions.
 *
 * The template parameter indicates the underlying data type. For most
 * practical purposes, this will be "bool", but other nuanced uses include
 * "char" for encrypted logic.
 */
template <class T>
class Value {
public:
	/*
	 * Create a default value.
	 *
	 * The magnitude will have a "maximum max", "minimum min", and will not be
	 * valid.
	 */
	Value();

	/*
	 * Create a Value of given parameters.
	 *
	 * By default, the max/min magnitude with be the type maximmum/minimum.
	 *
	 * By default, if not given, the Value will be valid.
	 *
	 * @param _magnitude Magnitude of the Value.
	 * @param _valid (Optional) Is the value valid.
	 * @param _min (Optional) Minimum possible value of the Value.
	 * @param _max (Optional) Maximum possible value of the Value.
	 */
	Value(T _magnitude, bool _valid = true, T _min = std::numeric_limits<T>::min(),
		  T _max = std::numeric_limits<T>::max());

	/*
	 * Two values are equal if their magnitudes are the same and they are valid.
	 *
	 * @param _other The other value being compared to.
	 * @return True if both magnitudes are the same and they are both valid.
	 */
	bool operator == (const Value<T>& _other) const;

	/*
	 * See the overloaded operator "==", as this is the logical opposite.

	 * @param _other The other value being compared to.
	 * @return True if both magnitudes are opposite or one is not valid.
	 */
	bool operator != (const Value<T>& _other) const;

	/*
	 * Compare two Values, presuming they are valid.
	 *
	 * @param _other The other value being compared to.
	 * @return True if both are valid and the magnitude of this Value is
	 *         < the magnitude of _other
	 */
	bool operator < (const Value<T>& _other) const;

	/*
	 * Return true if the two values are 'possibly' different.
	 *
	 * If either Value is not valid, the function returns true. If both are
	 * valid, the function returns true if their magnitudes are different.
	 *
	 * @param _value1 The first Value of the comparison.
	 * @param _value2 The second Value of the comparison.
	 * @return (bool) Are the two values (possibly) different
	 */
	static bool possiblyDifferent(const Value<T> _value1, const Value<T> _value2);

	/*
	 * Return the magnitude of the Value.
	 *
	 * @return The magnitude of the value.
	 */
	T magnitude() const;

	/*
	 * Set the magnitude of the Value.
	 *
	 * @param _magnitude The new magnitude of the value.
	 * @return The assigned magnitude of the value./
	 */
	 T magnitude(T _magnitude) ;

	 /*
	  * Return the validity of this Value.
	  *
	  * @return (bool) Is this Valid valid.
	  */
	 bool valid() const;

	 /* 
	  * Set the validity of this Value.
	  *
	  * @param _valid The new validity of this Value.
	  * @return (bool) The new validity of thsi Value.
	  */
	 bool valid(bool _valid);

	 /*
	  * Increment's this Value's magnitude.
	  *
	  * return (bool) True of the magnitude "warpped around" and is now at its 
	  *        minimum.*/
	 bool increment();

	 /*
	  * Return this Value's minimum value.
	  *
	  * @return This Value's minimum value.
	  */
	 T min() const;

	 /*
	  * Return this Value's maximum value.
	  *
	  * @return This Value's maximum value.
	  */
	 T max() const;

	 /*
	  * Return the cardinalit of this value, i.e., how many magnitudes it can hold.
	  *
	  * @return (unsigned long int) The number of magnitudes it can hold
	  */
	 unsigned long int cardinality() const;

private:
	//The  magnitude of the Value.
	T magnitude_;

	//Is the Value valid?
	bool valid_;

	//The minimum magnitude.
	T min_;

	//The maximum magnitude.
	T max_;
};


/*
 * This object holds a Value.
 *
 * A Valued object must be able to hold and return a value.
 *
 * The template parameters is the underlying data primitive which the value
 * holds.
 */
template <class T>
class Valued {
public:
	/*
	 * Initialize with the "Default" Value, which is not valid.
	 */
	Valued();

	/*
	 * Initialize the value to the given Value.
	 *
	 * @param _value The inditial value of this Valued oject.
	 */
	Valued(Value<T> _value);

	/*
	 * Return the Value held by this Valued object (will not recalculate).
	 *
	 * @return the Value held by this object.
	 */
	virtual Value<T> value() const;

	/*
	 * Set the Value to the given Value.
	 *
	 * Inheriting members may interpret this function as needed.
	 *
	 * @param _value The Value to set to (by default, only the first value will be
	 *        used. Any vector of size != 1 will throw an error).
	 * @return The Value after the object is set.
	 */
	virtual Value<T> value(std::vector<Value<T>> _value);

private:
	/*
	 * The current Value held by this object.
	 */
	Value<T> value_;
};

#endif

