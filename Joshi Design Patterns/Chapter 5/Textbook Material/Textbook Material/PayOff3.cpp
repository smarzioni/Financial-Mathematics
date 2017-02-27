//Taken from Joshi's C++ Design Patterns

#include "PayOff3.h"
#include <minmax.h>

PayOffCall::PayOffCall(double Strike_) : Strike(Strike_)
{
}

double PayOffCall::operator () (double Spot) const
{
	return max(Spot - Strike, 0.0);
}

PayOff* PayOffCall::clone() const
{
	return new PayOffCall(*this);
}

PayOffPut::PayOffPut(double Strike_) : Strike(Strike_)
{
}

double PayOffPut::operator() (double Spot) const
{
	return max(Strike - Spot, 0.0);
}

PayOff* PayOffPut::clone() const
{
	return new PayOffPut(*this);
}

//Personal Comment. The keyword this is a pointer always pointing to the object calling
// it. In particular the method clone() expressed by the line:
// return new PayOffPut(*this);
// will return a pointer of type PayOff* to an object of type PayOffPut, which is 
// allocated out of the relevant scope (and so will need to be manually destroyed)
// and which is identical to the object invoking the method clone().
//Notice that we are using the method 
//PayOffPut::PayOffPut(const PayOffPut&) 
//which is the standard copy constructor of objects in C++. 
//We are not using the default constructor: 
//PayOffPut::PayOffPutt(double ) we override above