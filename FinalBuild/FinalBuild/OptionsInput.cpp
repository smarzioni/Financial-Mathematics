#include "OptionsInput.h"
#include "PayOffInputs.h"
#include "ArgListFactory.h"
#include <string>
#include <iostream>

using namespace std;

OptionsInput::OptionsInput()
{
	inputData = ArgumentList("option");

	//PAYOFF CREATION

	string payoffType;
	ArgumentList POInputArg("payoff-input");

	cout << "\nEnter PayOff type. Choose between \n"
		<< FactoryInstance<POInputs>().GetKnownTypes() << endl;
	cin >> payoffType;
	POInputArg.add("name", payoffType);

	POInputs* POInputsPtr = FactoryInstance<POInputs>().CreateT(POInputArg);
	ArgumentList PayOffArgs("payoff");
	if (POInputsPtr != NULL)
	{
		PayOffArgs = POInputsPtr->operator()();
		delete POInputsPtr;
	}
	else throw("\nPOInput* was null\n");

	PayOff* PrePayOffPtr = FactoryInstance<PayOff>().CreateT(PayOffArgs);
	if (PrePayOffPtr == NULL)  throw("\nPayOff* was NULL\n");

	PayOffBridge* ThePayOffPtr = new PayOffBridge(*PrePayOffPtr);
	delete PrePayOffPtr;

	inputData.add("payoff", *ThePayOffPtr);
}

//EUROPEAN INPUT

EuropeanInput::EuropeanInput(ArgumentList args)
{
	if (args.GetListName() != "option-input")
		throw("Arguments of EuropeanInput expected to be in a \"option-input\" structure");
	if (args.GetStringValue("name") != "european")
		throw("Non-european option argument passed to a EuropeanInput");
	inputData.add("name", static_cast<std::string>("european"));
}

ArgumentList EuropeanInput::operator() ()
{
	double Expiry;
	MJArray times(1);

	cout << "\Enter Delivery date for the option Payoff (time difference in years)\n";
	cin >> Expiry;
	inputData.add("delivery", Expiry);

	times[0] = Expiry;
	inputData.add("times", times);

	return inputData;
}

OptionsInput* EuropeanInput::clone() const
{
	return new EuropeanInput(*this);
}

//ARITHMETIC ASIAN INPUT

ArithmeticAsianInput::ArithmeticAsianInput(ArgumentList args)
{
	if (args.GetListName() != "option-input")
		throw("Arguments of ArithemeticAsianInput expected to be in a \"option-input\" structure");
	if (args.GetStringValue("name") != "arithmetic-asian")
		throw("Non-arithmetic-asian option argument passed to a ArithmeticAsianInput");
	inputData.add("name", static_cast<std::string>("arithmetic-asian"));
}

ArgumentList ArithmeticAsianInput::operator() ()
{
	double Expiry;
	unsigned long NumberOfDates;
	MJArray times(1);

	cout << "\Enter Delivery date for the option Payoff (time difference in years)\n";
	cin >> Expiry;
	inputData.add("delivery", Expiry);

	cout << "\nEnter Number of days in which register Stock price (1 corresponds to a Vanilla option)?\n";
	cin >> NumberOfDates;
	times.resize(NumberOfDates);
	
	for (unsigned i = 0; i < NumberOfDates; i++)
		times[i] = (i + 1.0)*Expiry / NumberOfDates;
	inputData.add("times", times);

	return inputData;
}

OptionsInput* ArithmeticAsianInput::clone() const
{
	return new ArithmeticAsianInput(*this);
}

//GEOMETRIC ASIAN INPUT

GeometricAsianInput::GeometricAsianInput(ArgumentList args)
{
	if (args.GetListName() != "option-input")
		throw("Arguments of GeometricAsianInput expected to be in a \"option-input\" structure");
	if (args.GetStringValue("name") != "geometric-asian")
		throw("Non-geometric-asian option argument passed to a GeometricAsianInput");
	inputData.add("name", static_cast<std::string>("geometric-asian"));
}

ArgumentList GeometricAsianInput::operator() ()
{
	double Expiry;
	unsigned long NumberOfDates;
	MJArray times(1);

	cout << "\Enter Delivery date for the option Payoff (time difference in years)\n";
	cin >> Expiry;
	inputData.add("delivery", Expiry);

	cout << "\nEnter Number of days in which register Stock price (1 correspond to a Vanilla option)?\n";
	cin >> NumberOfDates;
	times.resize(NumberOfDates);

	for (unsigned i = 0; i < NumberOfDates; i++)
		times[i] = (i + 1.0)*Expiry / NumberOfDates;
	inputData.add("times", times);

	return inputData;
}

OptionsInput* GeometricAsianInput::clone() const
{
	return new GeometricAsianInput(*this);
}


//Knock UP AND OUT INPUT

UpAndOutInput::UpAndOutInput(ArgumentList args)
{
	if (args.GetListName() != "option-input")
		throw("Arguments of UpAndOutInput expected to be in a \"option-input\" structure");
	if (args.GetStringValue("name") != "knock-up-n-out")
		throw("Non-knock-up-n-out option argument passed to a UpAndOutInput");
	inputData.add("name", static_cast<std::string>("knock-up-n-out"));
}

ArgumentList UpAndOutInput::operator() ()
{
	double Expiry, Rebate, UpBarrier;
	unsigned long NumberOfDates;
	MJArray times(1);

	cout << "\Enter Delivery date for the option Payoff (time difference in years)\n";
	cin >> Expiry;
	inputData.add("delivery", Expiry);

	cout << "\Enter Rebate amount at Knock out\n";
	cin >> Rebate;
	inputData.add("rebate", Rebate);

	cout << "\Enter upper barrier price  (for Knock out)\n";
	cin >> UpBarrier;
	inputData.add("up-barrier", UpBarrier);

	cout << "\nEnter Number of days in which register Stock price (i.e. sample size of time discretization)?\n";
	cin >> NumberOfDates;
	times.resize(NumberOfDates);

	for (unsigned i = 0; i < NumberOfDates; i++)
		times[i] = (i + 1.0)*Expiry / NumberOfDates;
	inputData.add("times", times);

	return inputData;
}

OptionsInput* UpAndOutInput::clone() const
{
	return new UpAndOutInput(*this);
}

//Knock Down AND OUT INPUT

DownAndOutInput::DownAndOutInput(ArgumentList args)
{
	if (args.GetListName() != "option-input")
		throw("Arguments of DownAndOutInput expected to be in a \"option-input\" structure");
	if (args.GetStringValue("name") != "knock-Down-n-out")
		throw("Non-knock-down-n-out option argument passed to a DownAndOutInput");
	inputData.add("name", static_cast<std::string>("knock-down-n-out"));
}

ArgumentList DownAndOutInput::operator() ()
{
	double Expiry, Rebate, UpBarrier;
	unsigned long NumberOfDates;
	MJArray times(1);

	cout << "\Enter Delivery date for the option Payoff (time difference in years)\n";
	cin >> Expiry;
	inputData.add("delivery", Expiry);

	cout << "\Enter Rebate amount at Knock out\n";
	cin >> Rebate;
	inputData.add("rebate", Rebate);

	cout << "\Enter lower barrier price  (for Knock out)\n";
	cin >> UpBarrier;
	inputData.add("low-barrier", UpBarrier);

	cout << "\nEnter Number of days in which register Stock price (i.e. sample size of time discretization)?\n";
	cin >> NumberOfDates;
	times.resize(NumberOfDates);

	for (unsigned i = 0; i < NumberOfDates; i++)
		times[i] = (i + 1.0)*Expiry / NumberOfDates;
	inputData.add("times", times);

	return inputData;
}

OptionsInput* DownAndOutInput::clone() const
{
	return new DownAndOutInput(*this);
}

//Knock UP AND In INPUT

UpAndInInput::UpAndInInput(ArgumentList args)
{
	if (args.GetListName() != "option-input")
		throw("Arguments of UpAndInInput expected to be in a \"option-input\" structure");
	if (args.GetStringValue("name") != "knock-up-n-in")
		throw("Non-knock-up-n-in option argument passed to a UpAndInInput");
	inputData.add("name", static_cast<std::string>("knock-up-n-in"));
}

ArgumentList UpAndInInput::operator() ()
{
	double Expiry, Rebate, UpBarrier;
	unsigned long NumberOfDates;
	MJArray times(1);

	cout << "\Enter Delivery date for the option Payoff (time difference in years)\n";
	cin >> Expiry;
	inputData.add("delivery", Expiry);

	cout << "\Enter Rebate amount if not knocks in\n";
	cin >> Rebate;
	inputData.add("rebate", Rebate);

	cout << "\Enter upper barrier price  (for Knocking in)\n";
	cin >> UpBarrier;
	inputData.add("up-barrier", UpBarrier);

	cout << "\nEnter Number of days in which register Stock price (i.e. sample size of time discretization)?\n";
	cin >> NumberOfDates;
	times.resize(NumberOfDates);

	for (unsigned i = 0; i < NumberOfDates; i++)
		times[i] = (i + 1.0)*Expiry / NumberOfDates;
	inputData.add("times", times);

	return inputData;
}

OptionsInput* UpAndInInput::clone() const
{
	return new UpAndInInput(*this);
}

//Knock DOWN AND IN INPUT

DownAndInInput::DownAndInInput(ArgumentList args)
{
	if (args.GetListName() != "option-input")
		throw("Arguments of DownAndInInput expected to be in a \"option-input\" structure");
	if (args.GetStringValue("name") != "knock-down-n-in")
		throw("Non-knock-down-n-in option argument passed to a DownAndInInput");
	inputData.add("name", static_cast<std::string>("knock-down-n-in"));
}

ArgumentList DownAndInInput::operator() ()
{
	double Expiry, Rebate, UpBarrier;
	unsigned long NumberOfDates;
	MJArray times(1);

	cout << "\Enter Delivery date for the option Payoff (time difference in years)\n";
	cin >> Expiry;
	inputData.add("delivery", Expiry);

	cout << "\Enter Rebate amount if not knocks in\n";
	cin >> Rebate;
	inputData.add("rebate", Rebate);

	cout << "\Enter low barrier price  (for Knocking in)\n";
	cin >> UpBarrier;
	inputData.add("low-barrier", UpBarrier);

	cout << "\nEnter Number of days in which register Stock price (i.e. sample size of time discretization)?\n";
	cin >> NumberOfDates;
	times.resize(NumberOfDates);

	for (unsigned i = 0; i < NumberOfDates; i++)
		times[i] = (i + 1.0)*Expiry / NumberOfDates;
	inputData.add("times", times);

	return inputData;
}

OptionsInput* DownAndInInput::clone() const
{
	return new DownAndInInput(*this);
}