#include "PayOffDefs.h"


PayOffCall::PayOffCall(ArgumentList args)
{
	//std::cout << "\nDEBUG: Call Called\n";
	if (args.GetListName() != "payoff")
		throw("Arguments of PayOffCall expected to be in a \"payoff\" structure");
	if (args.GetStringValue("name") != "call")
		throw("Non-call payoff argument passed to a PayOfCall");
	Strike = args.GetFloatingValue("strike");
	args.throwErrorIfUnused("PayOffCall");
}

double PayOffCall::operator () (double Spot) const
{
	return max(Spot - Strike, 0.0);
}

PayOff* PayOffCall::clone() const
{
	return new PayOffCall(*this);
}

PayOffPut::PayOffPut(ArgumentList args)
{
	//std::cout << "\nDEBUG: Put Calle\n";
	if (args.GetListName() != "payoff")
		throw("Arguments of PayOffPutt expected to be in a \"payoff\" structure");
	if (args.GetStringValue("name") != "put")
		throw("Non-put payoff argument passed to a PayOfPut");
	Strike = args.GetFloatingValue("strike");
	args.throwErrorIfUnused("PayOffPut");
}

double PayOffPut::operator() (double Spot) const
{
	return max(Strike - Spot, 0.0);
}

PayOff* PayOffPut::clone() const
{
	return new PayOffPut(*this);
}


PayOffSpread::PayOffSpread(ArgumentList args)
{
//DEBUG
//std::cout << "\nDEBUG: Entered Spread Constructor\n";

if (args.GetListName() != "payoff")
throw("Arguments of PayOffSpread expected to be in a \"payoff\" structure");
if (args.GetStringValue("name") != "spread")
throw("Non-put payoff argument passed to a PayOfPut");
//DEBUG
//std::cout << "is present arg1? " << args.isPresent("payoff1");
//std::cout << "is present arg2? " << args.isPresent("payoff2");

if (!args.GetIfPresent("volume1", Volume1)) Volume1 = 1.0;
if (!args.GetIfPresent("volume2", Volume2)) Volume2 = -1.0;

ArgumentList args1 = args.GetAlistValue("payoff1");
ArgumentList args2 = args.GetAlistValue("payoff2");


payoff1 = Wrapper<PayOff>(*GetFromFactory<PayOff>(args1));
payoff2 = Wrapper<PayOff>(*GetFromFactory<PayOff>(args2));

args.throwErrorIfUnused("PayOffSpread");
}

double PayOffSpread::operator() (double Spot) const
{
return Volume1*(*payoff1)(Spot) + Volume2*(*payoff2)(Spot);
}

PayOff* PayOffSpread::clone() const
{
return new PayOffSpread(*this);
}


PayOffDoubleDigital::PayOffDoubleDigital(ArgumentList args)
{
	if (args.GetListName() != "payoff")
		throw("Arguments of PayOffDoubleDigital expected to be in a \"payoff\" structure");
	if (args.GetStringValue("name") != "double-digital")
		throw("Non-double-digital payoff argument passed to a PayOfDoubleDigital");
	LowerLevel = args.GetFloatingValue("low-strike");
	UpperLevel = args.GetFloatingValue("up-strike");
	args.throwErrorIfUnused("DoubleDigital");
}

double PayOffDoubleDigital::operator () (double Spot) const
{
	if (Spot <= LowerLevel)
		return 0;
	if (Spot >= UpperLevel)
		return 0;

	return 1;
}

PayOff* PayOffDoubleDigital::clone() const
{
	return new PayOffDoubleDigital(*this);
}

PayOffDigitalCall::PayOffDigitalCall(ArgumentList args)
{
	if (args.GetListName() != "payoff")
		throw("Arguments of PayOffDigitalCall expected to be in a \"payoff\" structure");
	if (args.GetStringValue("name") != "digital-call")
		throw("Non-digital-call payoff argument passed to a PayOfDigitalCall");
	Strike = args.GetFloatingValue("strike");
	args.throwErrorIfUnused("PayOffDigitalCall");
}

double PayOffDigitalCall::operator () (double Spot) const
{
	if (Spot <= Strike)
		return 0;

	return 1;
}

PayOff* PayOffDigitalCall::clone() const
{
	return new PayOffDigitalCall(*this);
}

PayOffDigitalPut::PayOffDigitalPut(ArgumentList args)
{
	if (args.GetListName() != "payoff")
		throw("Arguments of PayOffDigitalPut expected to be in a \"payoff\" structure");
	if (args.GetStringValue("name") != "digital-put")
		throw("Non-digital-put payoff argument passed to a PayOfDigitalPut");
	Strike = args.GetFloatingValue("strike");
	args.throwErrorIfUnused("PayOffDigitalPall");
}

double PayOffDigitalPut::operator () (double Spot) const
{
	if (Spot >= Strike)
		return 0;

	return 1;
}

PayOff* PayOffDigitalPut::clone() const
{
	return new PayOffDigitalPut(*this);
}