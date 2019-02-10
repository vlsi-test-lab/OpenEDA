/**
 * @file Flagged.hpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-09
 *
 * @copyright Copyright (c) 2019
 *
 */


#ifndef Flagged_h
#define Flagged_h

/*
 * An object which contains a Boolean flag.
 *
 * This object is most likely implemented through inheritence.
 *
 * This object's functions allow it to simultaneously set & poll the flag.
 *
 * By default, Flagged objects start with a "false" flag.
 */
class Flagged {
public:
	/*
	 * Create an object with a default (false) flag.
	 */
	Flagged() {
		this->flag_ = false;
	}

	/*
	 * Create an object with a given flag.
	 *
	 * @param _flag The object's initial flag.
	 */
	Flagged(bool _flag) {
		this->flag_ = _flag;
	}

	/*
	 * Return this object's current flag.
	 *
	 * @return The object's flag value.
	 */
	bool flag() const {
		return this->flag_;
	}

	/*
	 * Return this object's current flag while setting it to a new value..
	 *
	 * @param _flag The object's new flag value.
	 * @return The object's flag value (before being set).
	 */
	bool flag(bool _flag) {
		bool toReturn = this->flag_;
		this->flag_ = _flag;
		return toReturn;
	}

private:
	/*
	 * This object's Boolean flag.
	 */
	bool flag_;
};

#endif