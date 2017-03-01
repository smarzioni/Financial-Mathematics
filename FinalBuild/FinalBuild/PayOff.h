
#ifndef PAYOFF_H
#define PAYOFF_H

#include "ArgumentList.h"
#include "ArgListFactory.h"
#include "Wrapper.h"


/*
The Base Class PayOff is used as a function object via the overloaded operator(double Spot) to return
the pay off given the Spot price. As different types of payoffs exist, we will have
different derived classes from PayOff.
In this File we use the ArgumentListFactory to store the different PayOffs
We expect all the ArgumentLists passed to the following constructor to be named "payoff".
We expect all the  ArgumentLists passed to the following constructor to have a string stored with
  key "name" and Value "name-of-the-payoff" (e.g. "call", "put" etc..)
*/
class PayOff
{
public:
	PayOff() {};

	virtual double operator()(double Spot) const = 0;
	virtual ~PayOff() {} //virtual destructor
	virtual PayOff* clone() const = 0;
private:
};

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


class PayOffCall : public PayOff //inherit the interface of the class PayOff
{
public:
	PayOffCall(ArgumentList args);

	virtual double operator()(double Spot) const;
	virtual ~PayOffCall() {}
	virtual PayOff* clone() const;

private:
	double Strike;
};

class PayOffPut : public PayOff
{
public:
	PayOffPut(ArgumentList args);
	virtual double operator()(double Spot) const;
	virtual ~PayOffPut() {}
	virtual PayOff* clone() const;

private:
	double Strike;
};

class PayOffSpread : public PayOff
{
public:
	PayOffSpread(ArgumentList args);
	virtual double operator() (double Spot) const;
	virtual ~PayOffSpread() {}
	virtual PayOff* clone() const;

private:
	Wrapper<PayOff> payoff1;
	Wrapper<PayOff> payoff2;
	double Volume1;
	double Volume2;
};

class PayOffDoubleDigital : public PayOff
{
public:
	PayOffDoubleDigital(ArgumentList args);
	virtual double operator()(double Spot) const;
	virtual PayOff* clone() const;
	virtual ~PayOffDoubleDigital() {}

private:
	double LowerLevel;
	double UpperLevel;
};

class PayOffDigitalCall : public PayOff
{
public:
	PayOffDigitalCall(ArgumentList args);
	virtual double operator()(double Spot) const;
	virtual PayOff* clone() const;
	virtual ~PayOffDigitalCall() {}

private:
	double Strike;
};

class PayOffDigitalPut : public PayOff
{
public:
	PayOffDigitalPut(ArgumentList args);
	virtual double operator()(double Spot) const;
	virtual PayOff* clone() const;
	virtual ~PayOffDigitalPut() {}

private:
	double Strike;
};

#endif


//personal Comments.
//The class PayOff is inherited by the two classes PayOffCall and PayOffPut.
//Both the Destructor ~PayOff() and the operator() are declared virtual.
//In this way an object of type PayOffCall will have some extra data (a function pointer),
//that will refer to the right implementation of the virtual function corresponding to,
// e.g., operator().
// Putting  the =0 in line 10 means that such method HAS TO be implemented in the derived classes.
//Such methods are called pure virtual.
// As such, the class PayOff by itself is incompleted and objects of this class can not
//be defined.
// The need to declear a virtual destrucor and override it is that, if we call a 
// delete to a pointer of type PayOff* which actually point to an object of a 
// derived type (like PayOffPut) then, if not overridden, the destructor invoked
// would be the one of the class PayOff. For example it would forget to deallocate the
//	memory of the member Strike. 
