//Taken from Joshi's C++ Design Patterns..
//Requires Arrays.cpp
//		   Normals.cpp
//		   AntiThetic.cpp
//		   ParkMiller.cpp
//		   PayOff3.cpp
//		   Random2.cpp
//		   SimpleMC8.cpp
//		   Vanilla3.cpp
//		   Parameters.cpp
//		   MCStatistics.cpp
//		   PayOffBridge.cpp
//		   ConvergenceTable.cpp
//		   Wrapper.h


#include "AntiThetic.h"
#include "ConvergenceTable.h"
#include "ParkMiller.h"
#include "SimpleMC8.h"
#include "MCStatistics.h"
#include "Vanilla3.h"
#include <iostream>
#define RANGE_CHECKING

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
	ConvergenceTable gathererTwo(gatherer);

	RandomParkMiller generator(1);
	AntiThetic GenTwo(generator);
	

	SimpleMonteCarlo6(
		theOption,
		Spot,
		VolParam,
		rParam,
		NumberOfPaths,
		gathererTwo,
		GenTwo);

	vector<vector<double>> results = gathererTwo.GetResultsSoFar();

	cout << "\nFor a Call option, the statistics gathered are \n";

	for (unsigned long i = 0; i < results.size(); i++)
	{
		for (unsigned long j = 0; j < results[i].size(); j++)
			cout << results[i][j] << " ";
		
		
		cout << "\n";
	}

	double temp;
	cout << "\nType a number and press enter to quit\n";
	cin >> temp;

	return 0;
}

