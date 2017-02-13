//Code inspired by Jodshi's C++ Design Patterns
//Simple Monte carlo Simulation to compute the price of a double digital option.
// the stock price is supposed to be a geometric brownian motion.
//The annualized interest rate r and the volatility are supposed constant.

//requires Random1.cpp
#include "Random1.h"
#include <iostream>
#include <cmath>

using namespace std;

double payoff(
	double Spot,
	double KL,
	double KU)
{
	double Payoff;

	if (Spot < KL) Payoff = 0;
	else {
		if (Spot > KU) Payoff = 0;
		else Payoff = 1;
	}

	return Payoff;
}

double SimpleMonteCarlo1(
	double Expiry,  //T
	double KL,     //Lower and
	double KU,	   //Upper Srikes
	double Spot,    //S_0
	double Vol,     //sigma^2
	double r,
	unsigned long NumberOfPaths)
{
	double variance = Vol*Vol*Expiry;
	double rootVariance = sqrt(variance); //sigma
	double itoCorrection = -0.5*variance;

	//movedSpot is S(T) divided by the random multiplicative term exp(sigma W(T)).
	//As this quantity is not random, we pre compute it once and for all before 
	//the MC simulations.
	double movedSpot = Spot*exp(r*Expiry + itoCorrection);
	double thisSpot;
	double runningSum = 0;

	//The following for cycle runs NumberOfPaths MonteCarlo simulations.
	//The only random quantity in this setting is a normal random number ~N(0,1)
	//that accounts the brownian motion. 
	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisGaussian = GetOneGaussianByBoxMuller();
		thisSpot = movedSpot*exp(rootVariance*thisGaussian);
		runningSum += payoff(thisSpot, KL, KU);
	}

	double mean = runningSum / NumberOfPaths;
	mean *= exp(-r*Expiry);
	return mean;
}

int main()
{
	double Expiry;
	double KL;
	double KU;
	double Spot;
	double Vol;
	double r;
	unsigned long NumberOfPaths;
	cout << "\nEnter expiry time (in years)\n";
	cin >> Expiry;

	cout << "\nEnter lower strike price\n";
	cin >> KL;

	cout << "\nEnter upper strike price\n";
	cin >> KU;

	cout << "\nEnter Spot price\n";
	cin >> Spot;

	cout << "\nEnter volatility (in decimal, e.g. 0.2 for 20\%)\n";
	cin >> Vol;

	cout << "\nRisk-free interest rate (in decimal, e.g. 0.02 for 2\%)\n";
	cin >> r;

	cout << "\nNumber of Simulations?\n";
	cin >> NumberOfPaths;

	double result = SimpleMonteCarlo1(
		Expiry,
		KL,
		KU,
		Spot,
		Vol,
		r,
		NumberOfPaths);
	cout << "\nthe Monte-Carlo price is " << result << "\n";

	int temp;
	cout << "\nType something and press enter to quit\n";
	cin >> temp;
	return 0;
}