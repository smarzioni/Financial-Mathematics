//Taken from Joshi's C++ Design Patterns..
//Requires Arrays.cpp
//		   Normals.cpp
//		   ExoticEngine.cpp
//		   PathDependent.cpp
//		   PathDependentAsian.cpp
//		   AntiThetic.cpp
//		   ParkMiller.cpp
//		   PayOff3.cpp
//		   Random2.cpp
//		   SimpleMC8.cpp
//		   ExoticBSEngine.cpp
//		   Parameters.cpp
//		   MCStatistics.cpp
//		   PayOffBridge.cpp
//		   ConvergenceTable.cpp
//		   Wrapper.h


#include "AntiThetic.h"
#include "ConvergenceTable.h"
#include "PathDependentAsian.h"
#include "ParkMiller.h"
#include "ExoticBSEngine.h"
#include "MCStatistics.h"
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
	double d; //dividend rates,  (r-d) = drift
	unsigned long NumberOfPaths;
	unsigned NumberOfDates;

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

	cout << "\nDividend rate (in decimal, e.g. 0.02 for 2\%)\n";
	cin >> d;
	ParametersConstant dParam(d);

	cout << "\nNumber of Dates to consider for averaging?\n";
	cin >> NumberOfDates;

	cout << "\nNumber of Simulations?\n";
	cin >> NumberOfPaths;

	PayOffCall thePayOff(Strike);

	MJArray times(NumberOfDates);

	for (unsigned i = 0; i < NumberOfDates; i++)
		times[i] = (i + 1.0)*Expiry / NumberOfDates;

	PathDependentAsian theOption(times, Expiry, thePayOff);

	StatisticsMean gatherer;
	ConvergenceTable gathererTwo(gatherer);

	RandomParkMiller generator(1);
	AntiThetic GenTwo(generator);
	
	ExoticBSEngine theEngine(theOption,
		rParam,
		dParam,
		VolParam,
		GenTwo,
		Spot);
	theEngine.DoSimulation(gathererTwo, NumberOfPaths);

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

