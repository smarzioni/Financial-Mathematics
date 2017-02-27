#include "PayOffFactory.h"
#include <iostream>

using namespace std;

void PayOffFactory::RegisterPayOff(string PayOffId, CreatePayOffFunction CreatorFunction)
{
	TheCreatorFunctions.insert(pair<string, CreatePayOffFunction>(PayOffId, CreatorFunction));
}

PayOff* PayOffFactory::CreatePayOff(string PayOffId, double Strike)
{
	map<string, CreatePayOffFunction>::const_iterator i = TheCreatorFunctions.find(PayOffId);

	if (i == TheCreatorFunctions.end())
	{
		cout << PayOffId << " is an unknown payoff\n";
		return NULL;
	}
	return (i->second)(Strike);
	//(i->second) is of type CreatePayOffFunction, so it is a function pointer to some function
	//PayOff* f(double Strike)
}

PayOffFactory& PayOffFactory::Instance()
{
	static PayOffFactory theFactory;
	return theFactory;
}
//static PayOffFactory theFactory creates an object of class PayOffFactory which is static with
// respect to this class, i.e. it is unique. Any other call to the method Instance() will return
// a reference to the same object theFactory.
// This, together with the Constructors of PayOffFactory being private, make theFactor effectively
// the unique object of class PayOffFactory that can exists.
