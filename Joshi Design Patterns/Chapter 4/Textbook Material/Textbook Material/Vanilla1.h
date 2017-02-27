#ifndef VANILLA_1_H
#define VANILLA_1_H

#include "PayOff2.h"

//This is how TO NOT define an option class. Indeed it depends on the Class PayOff
// which is defined somewhere else. Any future change to the PayOff class will need
// to be backtracked here, and this is a recepie for hard to debug future problems.

class VanillaOption
{
public:
	VanillaOption(PayOff& ThePayOff_, double Expiry_);
	double GetExpiry() const;
	double OptionPayOff(double Spot) const;

private:
	double Expiry;
	PayOff& ThePayOff;
};

#endif // !VANILLA_1_H
