#ifndef NEWTON_RAPHSON_H
#define NEWTON_RAPHSON_H

#include <cmath>

// x[n+1] = (y -f(x[n]))/f'(x[n])  + x[n] 

template<class T, double (T::*Value)(double) const,
	double (T::*Derivative)(double) const >
double NewtonRaphson(double Target,
	double Start,
	double Tolerance,
	const T& TheObject)
{
	double y = (TheObject.*Value)(Start);
	double x = Start;

	while (fabs(y - Target) > Tolerance)
	{
		double d = (TheObject.*Derivative)(x);

		x += (Target - y) / d; //NR iteration

		y = (TheObject.*Value)(x);
	}

	return x;
}
#endif // !NEWTON_RAPHSON_H
#pragma once
