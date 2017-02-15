//Taken from Joshi's C++ Design Patterns..
//Requires PayOff1.cpp
//		   Random1.cpp
//		   SimpleMC.cpp

#include "SimpleMC.h"
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

	PayOff callPayOff(Strike, PayOff::call);
	PayOff putPayOff(Strike, PayOff::put);



	double resultCall = SimpleMonteCarlo2(
		callPayOff,
		Expiry,
		Spot,
		Vol,
		r,
		NumberOfPaths);

	double resultPut = SimpleMonteCarlo2(
		putPayOff,
		Expiry,
		Spot,
		Vol,
		r,
		NumberOfPaths);
	cout << "\nthe Monte-Carlo price of a Call is "
		<< resultCall
		<< "\nthe Monte-Carlo price of a Put is "
		<< resultPut << "\n";

	int temp;
	cout << "\nType something and press enter to quit\n";
	cin >> temp;
	return 0;
}