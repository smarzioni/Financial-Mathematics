
#include <iostream>

#include "PayOff.h"

//Trivial PayOff
/*
double PayOff::operator()(double Spot) const
{
	return Spot;
}

PayOff* PayOff::clone() const
{
	return new PayOff(*this);
}
*/

//copy constructor
PayOffBridge::PayOffBridge(const PayOffBridge& original)
{
	ThePayOffPtr = original.ThePayOffPtr->clone();
}

PayOffBridge::PayOffBridge(const PayOff& innerPayOff)
{
	ThePayOffPtr = innerPayOff.clone();
}

PayOffBridge::~PayOffBridge()
{
	delete ThePayOffPtr;
}

PayOffBridge& PayOffBridge::operator= (const PayOffBridge& original)
{
	if (this != &original)
	{
		delete ThePayOffPtr;
		ThePayOffPtr = original.ThePayOffPtr->clone();
	}

	return *this;
}

