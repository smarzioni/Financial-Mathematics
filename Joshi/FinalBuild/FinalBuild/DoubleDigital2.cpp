#include "DoubleDigital2.h"

PayOffDoubleDigital::PayOffDoubleDigital(double LowerLevel_,
	double UpperLevel_)
	: LowerLevel(LowerLevel_), UpperLevel(UpperLevel_)
{

}

double PayOffDoubleDigital::operator () (double Spot) const
{
	if (Spot <= LowerLevel)
		return 0;
	if (Spot >= UpperLevel)
		return 0;

	return 1;
}

PayOff* PayOffDoubleDigital::clone() const
{
	return new PayOffDoubleDigital(*this);
}

PayOffDigitalCall::PayOffDigitalCall(double Strike_)
	: Strike(Strike_)
{
}

double PayOffDigitalCall::operator () (double Spot) const
{
	if (Spot <= Strike)
		return 0;

	return 1;
}

PayOff* PayOffDigitalCall::clone() const
{
	return new PayOffDigitalCall(*this);
}

PayOffDigitalPut::PayOffDigitalPut(double Strike_)
	: Strike(Strike_)
{
}

double PayOffDigitalPut::operator () (double Spot) const
{
	if (Spot >= Strike)
		return 0;

	return 1;
}

PayOff* PayOffDigitalPut::clone() const
{
	return new PayOffDigitalPut(*this);
}