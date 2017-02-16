//Taken from Joshi's C++ Design Patterns..
//Requires DoubleDigitals.cpp
//		   PayOff2.cpp
//		   Random1.cpp
//		   SimpleMC3.cpp
//		   Vanilla1.cpp

#include "SimpleMC3.h"
#include "DoubleDigital.h"
#include "Vanilla1.h"
#include <iostream>

using namespace std;


int main()
{
	double Expiry;
	double Low, Up;
	double Spot;
	double Vol;
	double r;
	unsigned long NumberOfPaths;
	cout << "\nEnter expiry time (in years)\n";
	cin >> Expiry;

	cout << "\nEnter lower strike barrier\n";
	cin >> Low;

	cout << "\nEnter Upper strike barrier\n";
	cin >> Up;

	cout << "\nEnter Spot price\n";
	cin >> Spot;

	cout << "\nEnter volatility (in decimal, e.g. 0.2 for 20\%)\n";
	cin >> Vol;

	cout << "\nRisk-free interest rate (in decimal, e.g. 0.02 for 2\%)\n";
	cin >> r;

	cout << "\nNumber of Simulations?\n";
	cin >> NumberOfPaths;

	PayOffDoubleDigital thePayOff(Low, Up);

	VanillaOption theOption(thePayOff, Expiry);

	double result = SimpleMonteCarlo3(
		theOption,
		Spot,
		Vol,
		r,
		NumberOfPaths);

	cout << "\nthe Monte-Carlo price of a Double Digital  is "
		<< result << "\n";

	int temp;
	cout << "\nType something and press enter to quit\n";
	cin >> temp;

	return 0;
}

