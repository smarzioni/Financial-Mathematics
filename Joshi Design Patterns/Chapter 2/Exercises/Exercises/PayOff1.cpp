//Taken from Joshi's C++ Desig Patterns...

#include  "PayOff1.h"
#include <minmax.h>

PayOff::PayOff(double Strike_, OptionType TheOptionType_, double LowerStrike_)
	:
	Strike(Strike_), TheOptionsType(TheOptionType_),
	LowerStrike(LowerStrike_)
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

	case digitCall:
		return (spot >= Strike) ? 1 : 0;
	
	case digitPut:
		return (spot <= Strike) ? 1 : 0;

	case doubleDigit:
	{
		if (spot > Strike) return 0;
		else {
			if (spot < LowerStrike)
				return 0;
			else
				return 1;
		}
	}
	
	default:
		throw("unknown option type found.");
	}
}

//Personal Comments. The way to initialize class member myMember used here
// myClass::myClass(myMember_) : myMember(myMEmber_) {}
//is the right way to initialize objects in C++ and should be used instead of assignments.
//It is calle "member initialization list".
//The exception thrown here is not one taken from std:exception.
