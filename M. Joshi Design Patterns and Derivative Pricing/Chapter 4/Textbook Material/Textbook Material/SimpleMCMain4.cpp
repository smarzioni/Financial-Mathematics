//Taken from Joshi's C++ Design Patterns..
//Requires PayOff2.cpp
//		   Random1.cpp
//		   SimpleMC2.cpp

#include "SimpleMC2.h"
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

	unsigned long optionType;

	cout << "\nenter 0 for a call price, ptherwise for a put price ";
	cin >> optionType;
	
	PayOff* thePayOffPtr;

	if (optionType == 0)
		thePayOffPtr = new PayOffCall(Strike);
	else
		thePayOffPtr = new PayOffPut(Strike);

	//The method needs an object of type PayOff as argument to maje pass by refernce. 
	//*thePayOffPtr is the object pointed by thePayOffPtr.
	double result = SimpleMonteCarlo2(
		*thePayOffPtr,			
		Expiry,
		Spot,
		Vol,
		r,
		NumberOfPaths);

	cout << "\nthe Monte-Carlo price  is "
		<< result << "\n";

	int temp;
	cout << "\nType something and press enter to quit\n";
	cin >> temp;

	delete thePayOffPtr;
	return 0;
}

//Personal Comments. If inside the if else statement we used
// PayOffCall = thePayOff(Strike);
// instead of  thePayOffPtr = new PayOffCall(Strike);
// the object would have been destroyed at the end of the if statement.
// Recall, indeed, that in C/C++ anything has a scope corresponding to the 
// inner nested area in which it is defined, and it will be destroyed once such
// area is left. The Pointer thePayOffPtr is created before the if statement.
//Secondly a pointer to a base class can point ot any of its derived classes
// as we do with thePayOffPtr.
//The operator new allocates the memory for an object specified on the right and
// gives back a pointer to it. There is no scope for an object allocated with new,
// therefore we need to free the memory explicitly with the instruction 
// delete thePayOffPtr;