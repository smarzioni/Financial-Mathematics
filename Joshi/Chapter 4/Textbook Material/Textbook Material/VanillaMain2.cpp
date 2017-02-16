//Taken from Joshi's C++ Design Patterns..
//Requires DoubleDigital2.cpp
//		   PayOff3.cpp
//		   Random1.cpp
//		   SimpleMC4.cpp
//		   Vanilla2.cpp

#include "SimpleMC4.h"
#include "DoubleDigital2.h"
#include "Vanilla2.h"
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

	cout << "\nRisk-free interest rate (in decimal, e.g. 0.02 for 2\%)\n";
	cin >> r;

	cout << "\nNumber of Simulations?\n";
	cin >> NumberOfPaths;

	PayOffCall thePayOff(Strike);

	VanillaOption theOption(thePayOff, Expiry);

	double result = SimpleMonteCarlo3(
		theOption,
		Spot,
		Vol,
		r,
		NumberOfPaths);

	cout << "\nthe Monte-Carlo price of a Call Option is "
		<< result << "\n";

	//We test the re-definition of the copy constructor
	VanillaOption secondOption(theOption); 

	result = SimpleMonteCarlo3(
		secondOption,
		Spot,
		Vol,
		r,
		NumberOfPaths);

	cout << "\nthe (second) Monte-Carlo price of a Call Option is "
		<< result << "\n";

	PayOffPut otherPayOff(Strike);
	VanillaOption thirdOption(otherPayOff, Expiry);
	theOption = thirdOption; //Here we test the assignment operator we defined

	result = SimpleMonteCarlo3(
		theOption,
		Spot,
		Vol,
		r,
		NumberOfPaths);

	cout << "\nthe  Monte-Carlo price of a Put Option is "
		<< result << "\n";

	double temp;
	cout << "\nType a number and press enter to quit\n";
	cin >> temp;

	return 0;
}

