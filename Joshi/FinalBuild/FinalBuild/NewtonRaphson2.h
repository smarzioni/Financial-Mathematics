#ifndef NEWTON_RAPHSON2_H
#define NEWTON_RAPHSON2_H

#include <cmath>
#include <ctime>

using namespace std;
//this is a non-robust implementation of  Newton-Raphson root method. It checks for not convergence
// however does not to test the method's hypothesis nor tries to improve the starting point.

// The iteration is stopped after 2 minutes for possible not convergence.
//The convergence criteria are simultaneous
//  |x[n+1] -x[n]| < tolerance
//	|f(x[n+1]) - y| < tolerance
// however there is NO gaurantee that |x[n+1] - xReal | < tolerance, where xReal is such that 
//		f(xReal) == y.

//Newton-Raphson iteration:
// x[n+1] = (y -f(x[n]))/f'(x[n])  + x[n] 
//The user is required to create an class T containing two methods 
// double Value(double)
// double Derivative(double)
// corresponding, respectively, to the function f() and its derivative f'()

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

		if (static_cast<double>(StartTime - clock()) / CLOCKS_PER_SEC > 120)
			throw("\nThe Solver is taking too much time. Possible divergence\n");

	} while ((fabs(x - xPast) > Tolerance) || (fabs( y - Target) > Tolerance) );

	return x;
}
#endif // !NEWTON_RAPHSON2_H
