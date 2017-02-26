//Code copied from Joshi's Design Patterns book, page 5.

#include "Random1.h"
#include <cstdlib>
#include <cmath>

using namespace std;

//GetOneGaussianBySummation generstes a random number normally distributed ~ N(0,1)
// as approximation of a Sum of uniform random variables. (see CLT)
double GetOneGaussianBySummation()
{
	double result = 0;

	for (unsigned long j = 0; j < 12; j++)
		result += rand() / static_cast<double>(RAND_MAX);

	result -= 6.0;

	return result;
}

//PERSONAL COMMENTS
//rand() generates a uniformly distributed random number between 0 and RAND_MAX
//stati_cast<double> explicitly converts a numerical variable to double.
// Here it is used to perform a floating point division.
//It sums 12 random number uniformly distributed in [0,1]. 
//Such sum is normally distributed as ~ N(6, 1) thanks to the Central Limit Theorem 

//The function GetOneGaussianByBoxMuller generates a normal random number starting 
//from two uniform random number in [-1,1]. The formula used is known as 
//Box-Muller method in Polar Form.
 
double GetOneGaussianByBoxMuller()
{
	double result;

	double x, y;

	double sizeSquared;

	do
	{
		x = 2.0*rand()/static_cast<double>(RAND_MAX) - 1;
		y = 2.0*rand() / static_cast<double>(RAND_MAX) - 1;
		sizeSquared = x*x + y*y;
	} while (sizeSquared >= 1.0);

	result = x*sqrt(-2 * log(sizeSquared) / sizeSquared);

	return result;
}