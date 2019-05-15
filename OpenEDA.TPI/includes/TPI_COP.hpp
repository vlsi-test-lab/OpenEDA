/**
 * @file TPI_COP.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-21
 *
 * @copyright Copyright (c) 2019
 *
 */


#ifndef TPI_COP_h
#define TPI_COP_h

#include "TPI.hpp"
#include "COP_fault_calculator.h"

/*
 * COP-based TPI.
 *
 * The TPI implemented by this TPI method is very similar to the method in the
 * following article. The given article does some implied optimization after
 * a TP is inserted by only calculating the change in fault coverage for 
 * "effected" faults, but otherwise, the resulting TPs selected should be the
 * same.
 *
 * H.-C. Tsai, K.-T. Cheng, C.-J. Lin and S. Bhawmik. A hybrid algorithm for 
 * test point selection for scan-based BIST. Proc. of 34th Design Automation 
 * Conference, pages 478-483,1997.
 *
 * NOTE: There is no "_primitive" parameter since COP can only be performed on 
 *       Boolean circuits.
 * @param _nodeType The type of nodes used in the circuit to be modified.
 * @param _lineType THe type of lines used in the circuit to be modified.
 */

template <class _nodeType, class _lineType>
class TPI_COP : public TPI<bool, _nodeType, _lineType> {
public:
	/*
	 * Create a TPI algorithm with a given TP, quality, and time limit (in
	 * seconds).
	 *
	 * @param _circuit The circuit to insert TPs into.
	 * @param (optional) _TPLimit The maximumum allowed TPs to insert. By
	 *        default, this will be the maximum possible.
	 * @param (optional) _qualityLimit The maximum quality to achieve.
	 *        By default, this is will 100% (1.0f).
	 * @param (optional) _timeLimit The maximum time (in seconds) to spend
	 *        on TPI. By default, this will be the "maximum possible time".
	 */
	TPI_COP(
		Circuit* _circuit,
		size_t _TPLimit = std::numeric_limits<size_t>::max(),
		float _qualityLimit = 1.0,
		size_t _timeLimit = std::numeric_limits<size_t>::max()
	) :
		TPI<bool, _nodeType, _lineType>(
			_circuit, 
			_TPLimit, 
			_qualityLimit, 
			_timeLimit)
		, FaultCoverageCalculator_(
			_circuit
		) 
	{
		this->baseFaultCoverage_ = -1;
	};

	/*
	 * Return the "quality" of this testpoint.
	 *
	 * For this TPI method, the "quality" is the change in fault coverage.
	 *
	 * @param _testpoint The testpoint to measure.
	 * @return The quality of the testpoint.
	 */
	float quality(Testpoint<bool, _nodeType, _lineType>* _testpoint) {
		float base = this->base();
		_testpoint->activate();		
		float TPCoverage = this->FaultCoverageCalculator_.faultCoverage();
		float toReturn = TPCoverage - base;
		_testpoint->deactivate();
 		return toReturn;
	};

private:
	/*
	 * The "base fault coverage". If not yet calculated, it will be negative.
	 */
	float baseFaultCoverage_;

	/*
	 * The calculator used for calculating fault coverage.
	 */
	COP_fault_calculator FaultCoverageCalculator_;

	/*
	 * Return the "base" quality (no extra TP fault coverage) to compare other
	 * testpoints against.
	 *
	 * This function will be used to "bestTestpoint" to return final quality.
	 *
	 * If no base is needed, have it return "0" always.
	 *
	 * @return The base quality"
	 */
	virtual float base() {
		if (this->baseFaultCoverage_ < 0) {
			this->baseFaultCoverage_ = this->FaultCoverageCalculator_.faultCoverage();
		}
		return this->baseFaultCoverage_;
	};

	/*
	 * Reset the "base" quality to compare against other testpoints against.
	 *
	 * The  input parameter manually sets the value.
	 *
	 * @param _base The manually set base value.
	 * @return The new base quality.
	 */
	virtual float base(float _base) {
		this->baseFaultCoverage_ = _base;
		return this->baseFaultCoverage_;
	};
};

#endif