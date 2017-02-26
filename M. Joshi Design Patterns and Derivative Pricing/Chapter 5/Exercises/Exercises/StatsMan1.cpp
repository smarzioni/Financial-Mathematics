//Taken from Joshi's C++ Design Patterns..
//Requires DoubleDigital2.cpp
//		   PayOff3.cpp
//		   Random1.cpp
//		   SimpleMC7.cpp
//		   Vanilla3.cpp
//		   Parameters.cpp
//		   MCStatistics.cpp
//		   PayOffBridge.cpp

#include "SimpleMC7.h"
#include "MCStatistics.h"
#include "DoubleDigital2.h"
#include "Vanilla3.h"
#include <iostream>

using namespace std;


int main()
{
	double Expiry;
	double Strike;
	double Spot;
	double Vol;
	double r;
	unsigned long NumberOfPaths;
	cout << "\nEnter expiry time (in years)\n";
	cin >> Expiry;

	cout << "\nEnter strike price\n";
	cin >> Strike;

	cout << "\nEnter Spot price\n";
	cin >> Spot;

	cout << "\nEnter volatility (in decimal, e.g. 0.2 for 20\%)\n";
	cin >> Vol;
	ParametersConstant VolParam(Vol);

	cout << "\nRisk-free interest rate (in decimal, e.g. 0.02 for 2\%)\n";
	cin >> r;
	ParametersConstant rParam(r);

	cout << "\nNumber of Simulations?\n";
	cin >> NumberOfPaths;

	//The following two lines work because the constructor of PayOffBridge accepts
	//as argument (const PayOff&). In this way, even if the contructor of
	//VanillaOption requires (const PayOffBridge&, double), the compilers knows
	// a unique way to go from PayOffCall& to Payoff& to PayOffBridge&

	PayOffCall thePayOff(Strike);

	VanillaOption theOption(thePayOff, Expiry);

	StatisticsMean gatherer;

	SimpleMonteCarlo5(
		theOption,
		Spot,
		VolParam,
		rParam,
		NumberOfPaths,
		gatherer);

	vector<vector<double>> results = gatherer.GetResultsSoFar();

	cout << "\nFor a Call option, the statistics gathered are \n";

	for (unsigned long i = 0; i < results.size(); i++)
	{
		for (unsigned long j = 0; j < results[i].size(); j++)
			cout << results[i][j] << " ";
	}
	cout << "\n";

	double temp;
	cout << "\nType a number and press enter to quit\n";
	cin >> temp;

	return 0;
}

