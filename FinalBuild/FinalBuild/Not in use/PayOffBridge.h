#ifndef PAYOFFBRIDGE_H
#define PAYOFFBRIDGE_H

#include "PayOff3.h"

//The class PayOffBridge is meant to be an intermediate step between the class PayOff
// and any class storing a pointer to PayOff  that take care of the copy/assignment/detruction
// complications. Instead of a pointer to PayOff the class using it will need a pointer to PayOffBridge.
// Since the constructor has the form PayOffBridge(const PayOff& innerPayOff) any time a function 
// waits for an argument PayOffBridge we can instead pass an argument of type PayOffBridge.

class PayOffBridge
{
public:
	PayOffBridge(const PayOffBridge& original); //copy constructor
	PayOffBridge(const PayOff& innerPayOff);	//constructor

	inline double operator() (double Spot) const;
	~PayOffBridge(); //destructor
	PayOffBridge& operator= (const PayOffBridge& original); //assignement

private:
	PayOff* ThePayOffPtr;
};

inline double PayOffBridge::operator()(double Spot) const
{
	return ThePayOffPtr->operator()(Spot);
}

#endif // !PAYOFFBRIDGE_H
