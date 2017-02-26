//This Main tests some combination of Option/PayOffs.

//The Interface is really far from optimal or final and it is going to be changed. 
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
#include "GeometricAsian.h"
#include "DoubleDigital2.h"
#include "DiscreteKnockDownOut.h"
#include "DiscreteKnockUpOut.h"
#include <iostream>
#define RANGE_CHECKING

using namespace std;


int main()
{
	double Expiry;
	double Strike;
	double Rebate;
	double LowBarrier;
	double UpBarrier;
	double Spot;
	double Vol;
	double r;
	double d; //dividend rates,  (r-d) = drift
	unsigned long NumberOfPaths;
	unsigned NumberOfDates;

	cout << "\nThis Routine will compute price of different securities with the same underlying Stock\n";
	cout << "The Stock is supposed to follow the Black-Scholes model with constant coefficients\n";

	cout << "\nEnter the present Spot price of the Stock\n";
	cin >> Spot;

	cout << "\nEnter volatility (in decimal, e.g. 0.2 for 20\%)\n";
	cin >> Vol;
	ParametersConstant VolParam(Vol);

	cout << "\nEnter the Risk-free interest rate (in decimal, e.g. 0.02 for 2\%)\n";
	cin >> r;
	ParametersConstant rParam(r);

	cout << "\nEnter the dividend rate (in decimal, e.g. 0.02 for 2\%)\n";
	cin >> d;
	ParametersConstant dParam(d);

	cout << "\nEnter Number of days in which register the price (1 for Vanilla options)?\n";
	cin >> NumberOfDates;

	cout << "\nEnter expiry time of the security (in years)\n";
	cin >> Expiry;

	cout << "\nEnter strike price\n";
	cin >> Strike;

	cout << "\nEnter Rebate (on out) For Knock-out options\n";
	cin >> Rebate;

	cout << "\nEnter lower Barrier for Knock Down-and-Out Put Option\n";
	cin >> LowBarrier;

	cout << "\nEnter Upper Barrier for Knock Up-and-Out Call Option\n";
	cin >> UpBarrier;

	cout << "\nNumber of Simulations? (Suggested 1000 -- 1000000)\n";
	cin >> NumberOfPaths;

	PayOffCall theCall(Strike);
	PayOffDigitalCall theCallD(Strike);
	PayOffPut thePut(Strike);
	PayOffDigitalPut thePutD(Strike);

	MJArray times(NumberOfDates);

	for (unsigned i = 0; i < NumberOfDates; i++)
		times[i] = (i + 1.0)*Expiry / NumberOfDates;

	//Arithmetic Asian Options
	PathDependentAsian theCallOption(times, Expiry, theCall);
	PathDependentAsian thePutOption(times, Expiry, thePut);
	PathDependentAsian theCallDOption(times, Expiry, theCallD);
	PathDependentAsian thePutDOption(times, Expiry, thePutD);

	{
		StatisticsMean gatherer;
		ConvergenceTable gathererTwo(gatherer);

		RandomParkMiller generator(1);
		AntiThetic GenTwo(generator);

		ExoticBSEngine theEngine(theCallOption,
			rParam,
			dParam,
			VolParam,
			GenTwo,
			Spot);
		theEngine.DoSimulation(gathererTwo, NumberOfPaths);

		vector<vector<double>> results = gathererTwo.GetResultsSoFar();

		cout << "\nFor an Arithmetic Asian Call option, the prices gathered are \n";

		for (unsigned long i = 0; i < results.size(); i++)
		{
			for (unsigned long j = 0; j < results[i].size(); j++)
				cout << results[i][j] << " ";


			cout << "\n";
		}
	}
	{
		StatisticsMean gatherer;
		ConvergenceTable gathererTwo(gatherer);

		RandomParkMiller generator(1);
		AntiThetic GenTwo(generator);

		ExoticBSEngine theEngine(thePutOption,
			rParam,
			dParam,
			VolParam,
			GenTwo,
			Spot);
		theEngine.DoSimulation(gathererTwo, NumberOfPaths);

		vector<vector<double>> results = gathererTwo.GetResultsSoFar();

		cout << "\nFor an Arithmetic Asian Put option, the prices gathered are \n";

		for (unsigned long i = 0; i < results.size(); i++)
		{
			for (unsigned long j = 0; j < results[i].size(); j++)
				cout << results[i][j] << " ";


			cout << "\n";
		}
	}

	{
		StatisticsMean gatherer;
		ConvergenceTable gathererTwo(gatherer);

		RandomParkMiller generator(1);
		AntiThetic GenTwo(generator);

		ExoticBSEngine theEngine(theCallDOption,
			rParam,
			dParam,
			VolParam,
			GenTwo,
			Spot);
		theEngine.DoSimulation(gathererTwo, NumberOfPaths);

		vector<vector<double>> results = gathererTwo.GetResultsSoFar();

		cout << "\nFor an Arithmetic Asian Digitl Call option, the prices gathered are \n";

		for (unsigned long i = 0; i < results.size(); i++)
		{
			for (unsigned long j = 0; j < results[i].size(); j++)
				cout << results[i][j] << " ";


			cout << "\n";
		}
	}

	{
		StatisticsMean gatherer;
		ConvergenceTable gathererTwo(gatherer);

		RandomParkMiller generator(1);
		AntiThetic GenTwo(generator);

		ExoticBSEngine theEngine(thePutDOption,
			rParam,
			dParam,
			VolParam,
			GenTwo,
			Spot);
		theEngine.DoSimulation(gathererTwo, NumberOfPaths);

		vector<vector<double>> results = gathererTwo.GetResultsSoFar();

		cout << "\nFor an Arithmetic Asian Digitl Put option, the prices gathered are \n";

		for (unsigned long i = 0; i < results.size(); i++)
		{
			for (unsigned long j = 0; j < results[i].size(); j++)
				cout << results[i][j] << " ";


			cout << "\n";
		}
	}

	//Geometric Asian Options
	GeometricAsian theGeoCall(times, Expiry, theCall);
	GeometricAsian theGeoPut(times, Expiry, thePut);

	{
		StatisticsMean gatherer;
		ConvergenceTable gathererTwo(gatherer);

		RandomParkMiller generator(1);
		AntiThetic GenTwo(generator);

		ExoticBSEngine theEngine(theGeoCall,
			rParam,
			dParam,
			VolParam,
			GenTwo,
			Spot);
		theEngine.DoSimulation(gathererTwo, NumberOfPaths);

		vector<vector<double>> results = gathererTwo.GetResultsSoFar();

		cout << "\nFor a Geometric Asian Call option, the prices gathered are \n";

		for (unsigned long i = 0; i < results.size(); i++)
		{
			for (unsigned long j = 0; j < results[i].size(); j++)
				cout << results[i][j] << " ";


			cout << "\n";
		}
	}

	{
		StatisticsMean gatherer;
		ConvergenceTable gathererTwo(gatherer);

		RandomParkMiller generator(1);
		AntiThetic GenTwo(generator);

		ExoticBSEngine theEngine(theGeoPut,
			rParam,
			dParam,
			VolParam,
			GenTwo,
			Spot);
		theEngine.DoSimulation(gathererTwo, NumberOfPaths);

		vector<vector<double>> results = gathererTwo.GetResultsSoFar();

		cout << "\nFor a Geometric Asian Put option, the prices gathered are \n";

		for (unsigned long i = 0; i < results.size(); i++)
		{
			for (unsigned long j = 0; j < results[i].size(); j++)
				cout << results[i][j] << " ";
			cout << "\n";
		}
	}

	//Knock-Out
	DiscreteKnockDownOut KnockDOP(times, Expiry, Rebate, LowBarrier, thePut);
	DiscreteKnockUpOut KnockUOC(times, Expiry, Rebate, UpBarrier, theCall);

	{
		StatisticsMean gatherer;
		ConvergenceTable gathererTwo(gatherer);

		RandomParkMiller generator(1);
		AntiThetic GenTwo(generator);

		ExoticBSEngine theEngine(KnockUOC,
			rParam,
			dParam,
			VolParam,
			GenTwo,
			Spot);
		theEngine.DoSimulation(gathererTwo, NumberOfPaths);

		vector<vector<double>> results = gathererTwo.GetResultsSoFar();

		cout << "\nFor a Knock Up-and-Out Call option, the prices gathered are \n";

		for (unsigned long i = 0; i < results.size(); i++)
		{
			for (unsigned long j = 0; j < results[i].size(); j++)
				cout << results[i][j] << " ";


			cout << "\n";
		}
	}

	{
		StatisticsMean gatherer;
		ConvergenceTable gathererTwo(gatherer);

		RandomParkMiller generator(1);
		AntiThetic GenTwo(generator);

		ExoticBSEngine theEngine(KnockDOP,
			rParam,
			dParam,
			VolParam,
			GenTwo,
			Spot);
		theEngine.DoSimulation(gathererTwo, NumberOfPaths);

		vector<vector<double>> results = gathererTwo.GetResultsSoFar();

		cout << "\nFor a Knock Dow-and-Out Put option, the prices gathered are \n";

		for (unsigned long i = 0; i < results.size(); i++)
		{
			for (unsigned long j = 0; j < results[i].size(); j++)
				cout << results[i][j] << " ";


			cout << "\n";
		}
	}

	double temp;
	cout << "\nType a number and press enter to quit\n";
	cin >> temp;

	return 0;
}

