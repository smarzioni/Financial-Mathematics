#ifndef NEWTON_RAPHSON2_H
#define NEWTON_RAPHSON2_H

#include <cmath>
#include <ctime>

using namespace std;
//this is a non-robust implementation of  Newton-Raphson root method. It checks for not convergence
// however does not to test the method's hypothesis ore improve the starting point.
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
	double xPast;
	clock_t StartTime = clock();

	do
	{
		double d = (TheObject.*Derivative)(x);

		xPast = x;

		x += (Target - y) / d; //NR iteration

		y = (TheObject.*Value)(x);

		if (static_cast<double>(StartTime - clock()) / CLOCKS_PER_SEC > 300)
			throw("\nThe Solver is taking too much time. Possible divergence\n");

	} while (fabs(x - xPast) > Tolerance);

	return x;
}
#endif // !NEWTON_RAPHSON2_H
