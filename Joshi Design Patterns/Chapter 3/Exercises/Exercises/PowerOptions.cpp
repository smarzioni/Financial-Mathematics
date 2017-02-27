
#include "PowerOptions.h"
#include <minmax.h>
#include <cmath>

PayOffPowerCall::PayOffPowerCall(double Strike_, int power_)
	: Strike(Strike_), power(power_)
{
}

double PayOffPowerCall::operator()(double Spot) const
{
	return max(pow(Spot, power) - Strike, 0);
}

PayOffPowerPut::PayOffPowerPut(double Strike_, int power_)
	: Strike(Strike_), power(power_)
{
}

double PayOffPowerPut::operator()(double Spot) const
{
	return max(Strike - pow(Spot, power), 0);
}