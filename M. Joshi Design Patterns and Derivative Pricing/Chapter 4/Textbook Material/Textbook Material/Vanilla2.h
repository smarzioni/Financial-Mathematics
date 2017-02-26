#ifndef VANILLA_2_H
#define VANILLA_2_H

#include "PayOff3.h"


class VanillaOption
{
public:
	VanillaOption(const PayOff& ThePayOff_, double Expiry_); //default constructor
	VanillaOption(const VanillaOption& original); //Copy constructor
	VanillaOption& operator= (const VanillaOption& original); //Override assignment
	~VanillaOption();

	double GetExpiry() const;
	double OptionPayOff(double Spot) const;

private:
	double Expiry;
	PayOff* ThePayOffPtr; // Instead of a reference to a PayOff object we have pointer.
};

#endif // !VANILLA_2_H

//Comments. We have dstored in the class VanillaOption a Pointer to PayOff instead
// of a reference. This means, in particular, that we can have an Option without 
// any specified PayOff object attached