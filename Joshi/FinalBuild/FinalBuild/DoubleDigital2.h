#ifndef DOUBLEDIGITAL_H
#define DOUBLEDIGITAL_H

#include "PayOff3.h"

//Digital Call, ut and Double Digitals PayOff class

class PayOffDoubleDigital : public PayOff
{
public:
	PayOffDoubleDigital(double LowerLevel_,
		double UpperLevel_);
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
	PayOffDigitalCall(double Strike_);
	virtual double operator()(double Spot) const;
	virtual PayOff* clone() const;
	virtual ~PayOffDigitalCall() {}

private:
	double Strike;
};

class PayOffDigitalPut : public PayOff
{
public:
	PayOffDigitalPut(double Strike_);
	virtual double operator()(double Spot) const;
	virtual PayOff* clone() const;
	virtual ~PayOffDigitalPut() {}

private:
	double Strike;
};
#endif 

