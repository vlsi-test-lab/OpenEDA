// Propagate Fault.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "vector"
#include <Propagate_fault_stucture.h>

template<class _primitive>
Propagate_fault<_primitive>::Propagate_fault(bool _calculateAlways) {
	this->Propagate_faults_ = -1;
}

template<class _primitive>
int Propagate_fault<_primitive>::propagate_faults() {
	if (this->Propagate_faults_ > 0)
	{
		return Propagate_faults_;
	}
	this->Propagate_faults_ = this->calculate_propagate_faults();
	if (this->Propagate_faults_ < 0)
	{
		throw "Propagate_faults_.size()<0";
	}
	return Propagate_faults_;
}




template<class _primitive>
Propagate_faultLine<_primitive>::Propagate_faultLine() :Propagate_fault<_primitive>(false),  FaultyLine<_primitive>(), COPLine<_primitive>(),Connecting() {

}

template<class _primitive>
Propagate_faultLine<_primitive>::Propagate_faultLine(std::string _name) : Propagate_fault<_primitive>(false),FaultyLine<_primitive>(_name), COPLine<_primitive>(_name), Connecting(_name){

}


template<class _primitive>
int Propagate_faultLine<_primitive>::calculate_propagate_faults() {
	int toReturn = -1;
	if (this->inputs().size() ==0 )
	{
		return 0.0;
	}
	Propagate_faultLine<_primitive>* cast = dynamic_cast<Propagate_faultLine<_primitive>*>(*(this->inputs().begin()));
	if (cast == nullptr)// input is a node
	{
		toReturn = cast->calculate_propagate_faults();
	}
	else {
		Propagate_faultLine<_primitive>* cast_stem = dynamic_cast<Propagate_faultLine<_primitive>*>(*(this->inputs().begin()));
		std::unordered_set<Connecting*> branchs = cast_stem->outputs();	
		float sum_observability = 0;
		float this_observability = 0;
		for (Connecting* branch : branchs)
		{
			
			COP* cop_branch = dynamic_cast<COP*>(branch);
			if (branch == this)
			{
				this_observability = cop_branch->observability();
			}
			sum_observability = sum_observability + cop_branch->observability();
		}
		

		toReturn = cast_stem->calculate_propagate_faults()*this_observability / sum_observability;
	}
	if (toReturn < 0) {
		throw "Propagate_fault fail.";
	}
	return toReturn;

 }
 
 

template<class _primitive>
int Propagate_faultNode<_primitive>::calculate_propagate_faults() {
	int toReturn = -1;
	if (this->inputs().size() == 0)
	{
		return 0.0;
	}
	for (Connecting* input : this->inputs()) {
		Propagate_fault<_primitive>* cast = dynamic_cast<Propagate_fault<_primitive>*>(input);
		toReturn=toReturn+cast->calculate_propagate_faults();
	}
	if (toReturn < 0) {
		throw "Propagate_fault fail.";
	}
	return toReturn;

}

//template class Propagate_faultNode<bool>;
//template class Propagate_faultNode<unsigned long long int>;

template class Propagate_faultLine<bool>;
template class Propagate_faultLine<unsigned long long int>;

template class Propagate_fault<bool>;
template class Propagate_fault<unsigned long long int>;