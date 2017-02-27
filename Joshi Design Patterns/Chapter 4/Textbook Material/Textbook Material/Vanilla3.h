#ifndef VANILLA_3_H
#define VANILLA_3_H

#include "PayOffBridge.h"


class VanillaOption
{
public:
	VanillaOption(const PayOffBridge& ThePayOff_, double Expiry_); //default constructor

	double GetExpiry() const;
	double OptionPayOff(double Spot) const;

private:
	double Expiry;
	PayOffBridge ThePayOff; // Instead of a reference to a PayOff object we have pointer.
};

#endif // !VANILLA_2_H

//Comments. This is a VanillaOption if we use a bridge class for the payoff
//The advantage is that in this class we do not see any complication relative to 
// the copy/assignment/destruction of objects.