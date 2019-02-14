/**
 * @file FaultStructures.hpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-22
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef FaultStructures_h
#define FaultStructures_h

#include "SimulationStructures.hpp"
#include "Fault.h"

//Forward declaration
template <class T>
class Faulty;

/*
 * A Line with a potential Fault on it.
 *
 * @param _primitive The data primitive implemented by Values.
 */
template <class _primitive>
class FaultyLine : virtual public SimulationLine<_primitive> , virtual public Faulty<_primitive> {
public:
	/*
	 * Create a with a "UNDEF" name.
	 */
	FaultyLine() : SimulationLine<_primitive>(), Faulty<_primitive>(), Connecting("UNDEF") {
	};

	/*
	 * Create a Line with a given name
	 *
	 * @param _name The name of the Line
	 */
	FaultyLine(std::string _name) : 
		SimulationLine<_primitive>(_name), 
		Faulty<_primitive>(),
		Connecting(_name) 
	{
	};
};

#endif