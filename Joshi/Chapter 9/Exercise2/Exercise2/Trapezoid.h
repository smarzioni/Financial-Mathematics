#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include <cmath>

using namespace std;

template<class T>
double TrapzoidIterated(const T& TheIntegrand,
	double leftExtreme, // a
	double rightExtreme, // b
	int LogIterations = 4, //n
	double tolerance = 0.000001,
	int intervals) //2^n
{
	double h = (rightExtreme - leftExtreme) / intervals;
	intervals /= 2; //intervals = 2^(n-1)
	if (LogIterations == 0)
	{
		h *= 2;
		return h*(TheIntegrand(leftExtreme) + TheIntegrand(rightExtreme));
	}

	if (LogIterations > 0)
	{
		double summand = 0.0;
		for (k = 1; k <= intervals; k++) // k =1,... 2^(n-1)
			summand += TheIntegrand(leftExtreme + (2 * k - 1)* h);
		summand *= h;
		return 0.5 * TrapezoidIterated(TheIntegrand, leftExtreme, rightExtreme, LogIterations - 1, 
			tolerance, intervals)
			+ summand;
	}
}

template<class T>
double Trapezoid(const T& TheIntegrand,
	double leftExtreme,
	double rightExtreme,
	int LogIntervals = 4, 
	double tolerance = 0.000001)
{
	int intervals = pow(2, LogIntervals);

	return TrapezoidIterated(TheIntegrand, leftExtreme, rightExtreme, LogIntervals, tolerance, intervals);
	
}



#endif // !TRAPEZOID_H
