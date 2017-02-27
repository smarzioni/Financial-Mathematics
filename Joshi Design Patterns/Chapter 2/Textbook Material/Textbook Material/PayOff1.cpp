//Taken from Joshi's C++ Desig Patterns...

#include "PayOff1.h"
#include <minmax.h>

PayOff::PayOff(double Strike_, OptionType TheOptionType_)
	:
	Strike(Strike_), TheOptionsType(TheOptionType_)
{
}

double PayOff::operator()(double spot) const
{
	switch (TheOptionsType)
	{
	case call:
		return max(spot - Strike, 0.0);

	case put:
		return max(Strike - spot, 0.0);
	
	default:
		throw("unknown option type found.");
	}
}

//Personal Comments. The way to initialize class member myMember used here
// myClass::myClass(myMember_) : myMember(myMEmber_) {}
//is the right way to initialize objects in C++ and should be used instead of assignments.
//It is calle "member initialization list".
//The exception thrown here is not one taken from std:exception.
