#ifndef PAYOFF_DEFS_H
#define PAYOFF_DEFS_H
#include "ArgumentList.h"
#include "ArgListFactory.h"
#include "PayOff.h"
#include "Wrapper.h"
#include <minmax.h>

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


#endif // !PAYOFF_DEFS_H
