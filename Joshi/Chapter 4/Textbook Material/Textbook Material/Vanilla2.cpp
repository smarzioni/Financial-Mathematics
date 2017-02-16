#include "Vanilla2.h"

VanillaOption::VanillaOption(const PayOff& ThePayOff_, double Expiry_)
	:  Expiry(Expiry_)
{
	ThePayOffPtr = ThePayOff_.clone();
}

double VanillaOption::GetExpiry() const
{
	return Expiry;
}

double VanillaOption::OptionPayOff(double Spot) const
{
	return (*ThePayOffPtr)(Spot);
}

VanillaOption::VanillaOption(const VanillaOption& original)
{
	Expiry = original.GetExpiry();
	ThePayOffPtr = original.ThePayOffPtr->clone();
}

VanillaOption& VanillaOption::operator=(const VanillaOption& original)
{
	if (this != &original)
	{
		Expiry = original.GetExpiry();
		delete ThePayOffPtr;
		ThePayOffPtr = original.ThePayOffPtr->clone();
	}

	return *this;
}

VanillaOption::~VanillaOption() 
{
	delete ThePayOffPtr;
}

//Personal Comments. 
//In the default and copy constructor and the assignment operators is present the line 
// ThePayOffPtr = original.ThePayOffPtr->clone();
// This is important because  the clone method produce a NEW object out of scope.
// It is simple to make the mistake to just copy a pointer member in class, and the 
// having two classes, different in principle but pointing to the same object.
//Moreover, as the method clone() create an object with new, we need to destroy it
// ourselves when the destructor is invoked, explicitly typing
// delete ThePayOffPtr;
// which frees the allocated memory for the object pointed by ThePayOffPtr.