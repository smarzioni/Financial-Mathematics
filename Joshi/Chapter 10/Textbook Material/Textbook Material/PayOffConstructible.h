#ifndef PAYOFF_CONSTRUCTIBLE_H
#define PAYOFF_CONSTRUCTIBLE_H

#include <iostream>
#include <string>
#include "PayOff3.h"
#include "PayOffBridge.h"
#include "PayOffFactory.h"

//class T is required to have a constructor T::T(double)

//Typical use PayOffHelper<PayOffCall> Call("call") 
// creates  a couple <"call", PayOff* Call(double Strike)> into the map stored in the 
// PAyOffFactory.

template<class T>
class PayOffHelper
{
public:
	PayOffHelper(std::string);
	static PayOff* Create(double);
	//this is static because you should always be able to do 
	//myCall = *(PayOffHelper<PayOffCall>::Create(Strike);
};

template<class T>
PayOff* PayOffHelper<T>::Create(double Strike)
{
	return new T(Strike);
}

template<class T>
PayOffHelper<T>::PayOffHelper(std::string id)
{
	//Get a pointer to the unique PayOffFactory
	PayOffFactory& thePayOffFactory = PayOffFactory::Instance();
	//register a PayOff of type T, named id with PayOffFunction T(double)
	thePayOffFactory.RegisterPayOff(id, PayOffHelper<T>::Create);

}
#endif // !PAYOFF_CONSTRUCTIBLE_H
