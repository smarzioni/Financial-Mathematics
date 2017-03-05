#include "PayOffInputs.h"
#include "ArgListFactory.h"
#include "ArgumentList.h"
#include <iostream>

using namespace std;

POInputs::POInputs() 
{
	inputData = ArgumentList("payoff");
}

POCallInputs::POCallInputs(ArgumentList args) 
{
	if (args.GetListName() != "payoff-input")
		throw("Arguments of PayOffCall expected to be in a \"payoff\" structure");
	if (args.GetStringValue("name") != "call")
		throw("Non-call payoff argument passed to a PayOfCall");
	inputData.add("name", static_cast<std::string>("call"));
}

ArgumentList POCallInputs::operator() () 
{
	double Strike;
	
	cout << "\nEnter the Strike price\n";
	cin >> Strike;
	inputData.add("strike", Strike);

	return inputData;
}

POInputs* POCallInputs::clone() const
{
	return new POCallInputs(*this);
}

//PUT INPUT

POPutInputs::POPutInputs(ArgumentList args)
{
	if (args.GetListName() != "payoff-input")
		throw("Arguments of PayOffCall expected to be in a \"payoff\" structure");
	if (args.GetStringValue("name") != "put")
		throw("Non-put payoff argument passed to a PayOfPut");
	inputData.add("name", static_cast<std::string>("put"));
}

ArgumentList POPutInputs::operator() ()
{
	double Strike;

	cout << "\nEnter the Strike price\n";
	cin >> Strike;
	inputData.add("strike", Strike);

	return inputData;
}

POInputs* POPutInputs::clone() const
{
	return new POPutInputs(*this);
}

//Spread INPUT

POSpreadInputs::POSpreadInputs(ArgumentList args)
{
	if (args.GetListName() != "payoff-input")
		throw("Arguments of PayOffSpread expected to be in a \"payoff\" structure");
	if (args.GetStringValue("name") != "spread")
		throw("Non-spread payoff argument passed to a POSpreadInputs");
	inputData.add("name", static_cast<std::string>("spread"));
}

ArgumentList POSpreadInputs::operator() ()
{
	double Volume1, Volume2;
	std::string payoff1, payoff2;
	ArgumentList InputArgs1("payoff-input");
	ArgumentList InputArgs2("payoff-input");

	cout << "\nEnter the type of the first PayOff\n" 
		<< FactoryInstance<POInputs>().GetKnownTypes();
	cin >> payoff1;

	InputArgs1.add("name", payoff1);

	POInputs* POInputsPtr1 = FactoryInstance<POInputs>().CreateT(InputArgs1);
	ArgumentList args1("payoff");
	if (POInputsPtr1 != NULL)
	{
		args1 = POInputsPtr1->operator()();
		delete POInputsPtr1;
	}

	cout << "\nEnter the voulume of the first PayOff\n";
	cin >> Volume1;

	cout << "\nEnter the type of the second PayOff\n"
		<< FactoryInstance<POInputs>().GetKnownTypes();
	cin >> payoff2;

	InputArgs2.add("name", payoff2);

	POInputs* POInputsPtr2 = FactoryInstance<POInputs>().CreateT(InputArgs2);
	ArgumentList args2("payoff");
	if (POInputsPtr2 != NULL)
	{
		args2 = POInputsPtr2->operator()();
		delete POInputsPtr2;
	}

	cout << "\nEnter the voulume of the second PayOff\n";
	cin >> Volume2;

	inputData.add("volume1", Volume1);
	inputData.add("volume2", Volume2);
	inputData.add("payoff1", args1);
	inputData.add("payoff2", args2);

	return inputData;
}

POInputs* POSpreadInputs::clone() const
{
	return new POSpreadInputs(*this);
}

//INPUTS DOUBLE DIGITALS

PODoubleDInputs::PODoubleDInputs(ArgumentList args)
{
	if (args.GetListName() != "payoff-input")
		throw("Arguments of PayOffCall expected to be in a \"payoff\" structure");
	if (args.GetStringValue("name") != "double-digital")
		throw("Non-double-digital payoff argument passed to a PODoubleDInputs");
	inputData.add("name", static_cast<std::string>("double-digital"));
}

ArgumentList PODoubleDInputs::operator() ()
{
	double UpperStrike;
	double LowerStrike;

	cout << "\nEnter the Upper Bound for the Double Digital\n";
	cin >> UpperStrike;
	inputData.add("up-strike", UpperStrike);

	cout << "\nEnter the Lower Bound for the Double Digital\n";
	cin >> LowerStrike;

	while (LowerStrike > UpperStrike)
	{
		cout << "\n Lower Strike  can not be higher the Upper Strike\n";
		cout << "\nEnter the Lower Bound for the Double Digital\n";
		cin >> LowerStrike;
	}

	inputData.add("low-strike", LowerStrike);

	return inputData;
}

POInputs* PODoubleDInputs::clone() const
{
	return new PODoubleDInputs(*this);
}

//INPUTS DIGITAL CALL

PODCallInput::PODCallInput(ArgumentList args)
{
	if (args.GetListName() != "payoff-input")
		throw("Arguments of PayOffCall expected to be in a \"payoff\" structure");
	if (args.GetStringValue("name") != "digital-call")
		throw("Non-digital-call payoff argument passed to a PODCallInput");
	inputData.add("name", static_cast<std::string>("digital-call"));
}

ArgumentList PODCallInput::operator() ()
{
	double Strike;

	cout << "\nEnter the Strike price\n";
	cin >> Strike;
	inputData.add("strike", Strike);

	return inputData;
}

POInputs* PODCallInput::clone() const
{
	return new PODCallInput(*this);
}

//INPUTS DIGITAL PUT

PODPutInput::PODPutInput(ArgumentList args)
{
	if (args.GetListName() != "payoff-input")
		throw("Arguments of PayOffCall expected to be in a \"payoff\" structure");
	if (args.GetStringValue("name") != "digital-put")
		throw("Non-digital-put payoff argument passed to a PODPutInput");
	inputData.add("name", static_cast<std::string>("digital-put"));
}

ArgumentList PODPutInput::operator() ()
{
	double Strike;

	cout << "\nEnter the Strike price\n";
	cin >> Strike;
	inputData.add("strike", Strike);

	return inputData;
}

POInputs* PODPutInput::clone() const
{
	return new PODPutInput(*this);
}