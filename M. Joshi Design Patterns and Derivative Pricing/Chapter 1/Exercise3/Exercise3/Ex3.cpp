//Code inspired by Jodshi's C++ Design Patterns
//Simple Monte carlo Simulation to compute the price of a Call or Putt option.
// the stock price is supposed to be a geometric brownian motion.
//The annualized interest rate r and the volatility are supposed constant.

//requires Random1.cpp
#include "Random1.h"
#include <iostream>
#include <cmath>
#include <string>

using namespace std;
using std::string;

double payoff(
	double Spot,
	double Strike,
	int option)
{
	double Payoff;

	switch (option)
	{
	case 0:
		Payoff = Spot - Strike; // (S(T) - K)
		Payoff = (Payoff > 0) ? Payoff : 0; // MAX(S(T) - K, 0)
		break;
	case 1:
		Payoff = Strike - Spot; // (K - S(T))
		Payoff = (Payoff > 0) ? Payoff : 0; // MAX(K- S(T), 0)
		break;
	}
	return Payoff;
}

double SimpleMonteCarlo1(
	double Expiry,  //T
	double Strike,
	double Spot,    //S_0
	double Vol,     //sigma^2
	double r,
	int option,
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

	//The foolowing for cycle runs NumberOfPaths MonteCarlo simulations.
	//The only random quantity in this setting is a normal random number ~N(0,1)
	//that accounts the brownian motion. 
	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisGaussian = GetOneGaussianByBoxMuller();
		thisSpot = movedSpot*exp(rootVariance*thisGaussian);
		double thisPayoff = payoff(thisSpot, Strike, option);
		runningSum += thisPayoff;
	}

	double mean = runningSum / NumberOfPaths;
	mean *= exp(-r*Expiry);
	return mean;
}

int main()
{
	double Expiry;
	double Strike;
	double Spot;
	double Vol;
	double r;
	string option;
	int noption = 3;
	unsigned long NumberOfPaths;

	do
	{
		cout << "\Enter option type (no uppercases)\n";
		cin >> option;
		if (option == "call") noption = 0;
		else
		{
			if (option == "put") noption = 1;
			else noption = 3;
		}
	} while (noption > 1 || noption < 0);

	cout << "\nEnter expiry time (in years)\n";
	cin >> Expiry;

	cout << "\nEnter strike price\n";
	cin >> Strike;

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
		Strike,
		Spot,
		Vol,
		r,
		noption,
		NumberOfPaths);
	cout << "\nthe Monte-Carlo price is " << result << "\n";

	int temp;
	cout << "\nType something and press enter to quit\n";
	cin >> temp;
	return 0;
}

