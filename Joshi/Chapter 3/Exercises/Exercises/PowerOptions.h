#ifndef POWEROPTIONS_H
#define POWEROPTIONS_H
#include "PayOff2.h"

class PayOffPowerCall : public PayOff //inherit the interface of the class PayOff
{
public:
	PayOffPowerCall(double Strike_, int power_);
	virtual double operator()(double Spot) const;
	virtual ~PayOffPowerCall() {}

private:
	double Strike;
	int power;
};

class PayOffPowerPut : public PayOff //inherit the interface of the class PayOff
{
public:
	PayOffPowerPut(double Strike_, int power_);
	virtual double operator()(double Spot) const;
	virtual ~PayOffPowerPut() {}

private:
	double Strike;
	int power;
};

#endif // !POWEROPTIONS_H
