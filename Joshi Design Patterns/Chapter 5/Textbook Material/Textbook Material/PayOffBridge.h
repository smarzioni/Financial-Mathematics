#ifndef PAYOFFBRIDGE_H
#define PAYOFFBRIDGE_H

#include "PayOff3.h"

//The class PayOffBridge is meant to be an intermediate step between the class PayOff
// and the class VanillaOption that take care of the copy/assignment/detruction
// complications. In this the body of the VanillaOption won't need to take care of them

class PayOffBridge
{
public:
	PayOffBridge(const PayOffBridge& original);
	PayOffBridge(const PayOff& innerPayOff);

	inline double operator() (double Spot) const;
	~PayOffBridge();
	PayOffBridge& operator= (const PayOffBridge& original);

private:
	PayOff* ThePayOffPtr;
};

inline double PayOffBridge::operator()(double Spot) const
{
	return ThePayOffPtr->operator()(Spot);
}

#endif // !PAYOFFBRIDGE_H
