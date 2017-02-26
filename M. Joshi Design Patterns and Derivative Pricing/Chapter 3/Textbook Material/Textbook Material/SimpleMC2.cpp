//Taken from Joshi's C++ Design Patterns..

#include <cmath>
#include "Random1.h"
#include "SimpleMC2.h"

using namespace std;

double SimpleMonteCarlo2(
	const PayOff& thePayOff,
	double Expiry, // T
	double Spot,   //S(0)
	double Vol,    //sigma
	double r,
	unsigned long NumberOfPaths)
{
	double variance = Vol*Vol*Expiry;
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;

	double movedSpot = Spot*exp(r*Expiry + itoCorrection);
	double thisSpot;
	double runningSum = 0;

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisGaussian = GetOneGaussianByBoxMuller();
		thisSpot = movedSpot*exp(rootVariance*thisGaussian);
		double thisPayOff = thePayOff(thisSpot);
		runningSum += thisPayOff;
	}
	double mean = runningSum / NumberOfPaths;
	mean *= exp(-r*Expiry);

	return mean;
}

//Personal Comments.
//The fact that the PayOff is passed by reference gauranties that if we pass 
// a class derived from PayOff instead this will correctly passed in its integrity.
// In particular overridden methods will mantain their derived body.
// If we pass PayOff by value instead, and then apply the method to a derived object,
// this will be copied to an object of type PayOff, and lose all the extra data and
// methods from the derived class. 
//This is the same monte carlo simulation of the Chapter 1.
//Only difference is that uses the class PayOff to compute the actual Payoff,
//and the strike price is hidden there.