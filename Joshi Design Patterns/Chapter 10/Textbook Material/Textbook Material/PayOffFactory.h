#ifndef PAYOFF_FACTORY_H
#define PAYOFF_FACTORY_H

#include "PayOff3.h"
#include <map>
#include <string>

class PayOffFactory
{
public:
	typedef PayOff* (*CreatePayOffFunction)(double);
	//CreatePayOffFunction is a type of a pointer to functions: PayOff* f (double)

	static PayOffFactory& Instance();
	//A static function is accessible from the class without the need ti initialize an object.
	void RegisterPayOff(std::string, CreatePayOffFunction);
	PayOff* CreatePayOff(std::string PayOffId, double Strike);

	~PayOffFactory() {}

private:
	std::map<std::string, CreatePayOffFunction> TheCreatorFunctions;
	//This map is used to associate to each string a pointer to PayOff::operator()
	PayOffFactory() {};
	PayOffFactory(const PayOffFactory&) {}
	PayOffFactory& operator= (const PayOffFactory&) { return *this; }
	//We do not want the user to be able to create new intances of the PAyOffFactory.
	//The creation of the unique instance is handled by the static method Instance()
};

#endif //PAYOFF_FACTORY_H