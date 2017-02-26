//Taken from Joshi's C++ Design Patterns..
//Requires PayOff3.cpp
//		   PayOffBridge.cpp
//		   PayOffFactory.cpp
//		   PayOffRegistration.cpp

#include "PayOff3.h"
#include "PayOffBridge.h"
#include "PayOffFactory.h"
#include "PayOffConstructible.h"
#include <string>
#include <iostream>

using namespace std;


int main()
{
	double Strike;
	double Spot;
	string optionType;


	cout << "\nEnter strike price\n";
	cin >> Strike;

	cout << "\nEnter option Type name (\"call\" or \"put\") \n";
	cin >> optionType;

	cout << "\nEnter spot price at expiration\n";
	cin >> Spot;

	PayOff* PayOffPtr = PayOffFactory::Instance().CreatePayOff(optionType, Strike);
	if (PayOffPtr != NULL)
	{
		cout << "\n" << PayOffPtr->operator()(Spot) << "\n";
		delete PayOffPtr;
	}

	int temp;
	cout << "\nType something and press enter to quit\n";
	cin >> temp;
	return 0;
}