//Taken from Joshi's C++ Design Patterns

#include "PayOff2.h"
#include <minmax.h>

PayOffCall::PayOffCall(double Strike_) : Strike(Strike_)
{
}

double PayOffCall::operator () (double Spot) const
{
	return max(Spot - Strike, 0);
}

PayOffPut::PayOffPut(double Strike_) : Strike(Strike_)
{
}

double PayOffPut::operator() (double Spot) const
{
	return max(Strike - Spot, 0);
}