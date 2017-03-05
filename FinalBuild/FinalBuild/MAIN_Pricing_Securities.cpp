
/*Requires:
	ArgumentList.cpp
	AntiThetic.cpp
	FactoryRegistration.cpp
	Arrays.cpp
	ConvergenceTable.cpp
	ConvergenceTable.cpp
	PayOff.cpp
	PayOffInputs.cpp
	ExoticEngine.cpp
	ExoticBSEngine.cpp
	Normals.cpp
	ParkMiller.cpp
	Random2.cpp
	Parameters.cpp
	Options.cpp
	OptionsInput.cpp
	SeveralStatistics.cpp
	MCStatistics.cpp
*/

#include "ArgumentList.h"
#include "ArgListFactory.h"
#include "ArgListFactoryHelper.h"
#include "Arrays.h"
#include "AntiThetic.h"
#include "ConvergenceTable.h"
#include "PayOff.h"
#include "PayOffInputs.h"
#include "Wrapper.h"
#include "ExoticEngine.h"
#include "ExoticBSEngine.h"
#include "Normals.h"
#include "ParkMiller.h"
#include "Random2.h"
#include "Parameters.h"
#include "Options.h"
#include "OptionsInput.h"
#include "MCStatistics.h"
#include "SeveralStatistics.h"

#include <sstream>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	double Spot;
	double Vol;
	double r;
	double d; //dividend rates,  (r-d) = drift
	unsigned long NumberOfPaths;
	string optionType, payoffType;

	//OPTION CREATION
	ArgumentList OptionInputArg("option-input");
	cout << "\nEnter Option type. Choose between \n"
		<< FactoryInstance<OptionsInput>().GetKnownTypes() << endl;
	cin >> optionType;
	OptionInputArg.add("name", optionType);

	OptionsInput* OptionInputPtr = FactoryInstance<OptionsInput>().CreateT(OptionInputArg);
	ArgumentList OptionArgs("option");
	if (OptionInputPtr != NULL)
	{
		OptionArgs = OptionInputPtr->operator()();
		delete OptionInputPtr;
	}

	PathDependent* OptionPtr = FactoryInstance<PathDependent>().CreateT(OptionArgs);
	if (OptionPtr == NULL) throw("\nPathDependent* was null from Factory\n");
	
	//END OPTION CREATION. STORED IN *OptionPtr

	//Rest of The input
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

	cout << "\nEnter number of simulations to run (suggested 1000 -- 1000000)\n";
	cin >> NumberOfPaths;
	
	StatisticsMean MeanGatherer;
	ConvergenceTable MeanTable(MeanGatherer);

	Variance sigmaGatherer;
	//ValueAtRisk VaRGatherer(0.95);
	
	vector<Wrapper<StatisticsMC>> Stats;
	Stats.push_back(MeanTable);
	Stats.push_back(sigmaGatherer);
	//Stats.push_back(VaRGatherer);
	SeveralStats statGatherer(Stats);

	RandomParkMiller generator(1);
	AntiThetic GenTwo(generator);

	ExoticBSEngine theEngine(*OptionPtr,
		rParam,
		dParam,
		VolParam,
		GenTwo,
		Spot);
	theEngine.DoSimulation(statGatherer, NumberOfPaths);

	vector<vector<double>> results = statGatherer.GetResultsSoFar();

	cout << "\nThe simulations Returns the following statistics for the security\n";
	cout << (statGatherer.GetOutputStream()).str();
	/*
	for (unsigned long i = 0; i < results.size(); i++)
	{
		for (unsigned long j = 0; j < results[i].size(); j++)
			cout << results[i][j] << " ";


		cout << "\n";
	}*/
	
	double temp;
	cout << "\nType a number and press enter to quit\n";
	cin >> temp;
}