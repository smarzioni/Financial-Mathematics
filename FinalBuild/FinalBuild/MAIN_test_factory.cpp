//Taken from Joshi's C++ Design Patterns..
//Requires PayOff.cpp
//		   PayOffBridge.cpp
//		   ArgumentList.cpp
//		   PayOffRegistration.cpp

#include "PayOff.h"
#include "PayOffInputs.h"
#include "ArgListFactoryHelper.h"
#include "ArgListFactory.h"
#include "ArgumentList.h"
#include <string>
#include <iostream>

using namespace std;


int main()
{
	double Strike;
	double Spot;
	string optionType;

	ArgumentList InputArg("payoff-input");
	cout << "\nEnter PayOff type. Choose between \n" 
		<< FactoryInstance<POInputs>().GetKnownTypes();
	cin >> optionType;
	InputArg.add("name", optionType);

	POInputs* POInputsPtr = FactoryInstance<POInputs>().CreateT(InputArg);
	ArgumentList args("payoff");
	if (POInputsPtr != NULL)
	{
		args = POInputsPtr->operator()();
		delete POInputsPtr;
	}

	cout << "\nEnter spot price at expiration\n";
	cin >> Spot;


	PayOff* PayOffPtr = FactoryInstance<PayOff>().CreateT(args);
	if (PayOffPtr != NULL)
	{
		cout << "\n" << PayOffPtr->operator()(Spot) << "\n";
		delete PayOffPtr;
	}
	else throw("NULLPTR at PayOff");

	int temp;
	cout << "\nType something and press enter to quit\n";
	cin >> temp;
	return 0;
}