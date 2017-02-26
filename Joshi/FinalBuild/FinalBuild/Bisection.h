#ifndef BISECTION_H
#define BISECTION_H
/*
The function Bisection takes the an object function TheFunction of Class T and approximates 
 the solution x to T(x) = y.
 The class T is required to have the operator() overloaded as 
 double T::operator() (double).
*/
#include <cmath>

template<class T>
double Bisection(double Target,
	double Low,
	double High,
	double Tolerance,
	T TheFunction)
{
	double x = 0.5*(Low + High);
	double y = TheFunction(x);

	do 
	{
		if (y < Target)
			Low = x;
		if (y > Target)
			High = x;
		
		x = 0.5* (Low + High);
		y = TheFunction(x);
	} while ((fabs(y - Target) > Tolerance));

	return x;
}
#endif // !BISECTION_H
