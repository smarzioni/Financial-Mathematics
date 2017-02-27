//Taken from Joshi's C++ Design Patterns..
//Requires BlackScholesFormulas.cpp
//		   Normals.cpp
//		   BsCallClass.cpp


//Computes Volatility starting from the price of a vanilla european option.
//Uses Bisection Method.


#include "Bisection.h"
#include "BSCallClass.h"
#include "..\..\..\Appendices\Black-Scholes Formulas\BSFormulas\BSFormulas\BlackScholesFormulas.h"
#include <iostream>
#include <cmath>
#define RANGE_CHECKING

using namespace std;


int main()
{
	double Expiry;
	double Strike;
	double Spot;
	double r;
	double d; //dividend rates
	double Price;
	double low, high;
	double tolerance;

	cout << "\nEnter expiry time (in years)\n";
	cin >> Expiry;

	cout << "\nEnter strike price\n";
	cin >> Strike;

	cout << "\nEnter Spot price\n";
	cin >> Spot;

	cout << "\nEnter market price of the call option\n";
	cin >> Price;

	cout << "\nRisk-free interest rate (in decimal, e.g. 0.02 for 2\%)\n";
	cin >> r;

	cout << "\nDividend rate (in decimal, e.g. 0.02 for 2\%)\n";
	cin >> d;

	cout << "\nEnter lower guess for the Volatility (sigma, in decimals):\n";
	cin >> low;

	cout << "\nEnter higher guess for the Volatility (sigma, in decimals):\n";
	cin >> high;

	cout << "\nEnter error tolerance:\n";
	cin >> tolerance;
	
	BSCall theCall(r, d, Expiry, Spot, Strike);
	double Vol = Bisection(Price, low, high, tolerance, theCall);
	double  PriceTwo = BlackScholesCall(Spot, Strike, r, d, Vol, Expiry);

	cout << "\nImplied Volatility " << Vol << " Re-pricing: " << PriceTwo << endl;

	double temp;
	cout << "\nType a number and press enter to quit\n";
	cin >> temp;

	return 0;
}

