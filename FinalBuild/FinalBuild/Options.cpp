#include "Options.h"

PathDependent::PathDependent(ArgumentList args) :
	ThePayOff(args.isPresent("payoff") ? args.GetPayOffValue("payoff")
		: throw("\nNo Payoff was passed to the option\n"))
{
	if (args.GetListName() != "option")
		throw("Arguments of a PathDependent expected to be in a \"option\" structure");
	LookAtTimes = args.GetMJArrayValue("times");
}

const MJArray& PathDependent::GetLookAtTimes() const
{
	return LookAtTimes;
}

//EUROPEANS

European::European(ArgumentList args)
	:
	PathDependent(args)
{
	if (args.GetStringValue("name") != "european")
		throw("Non-european option argument passed to a European");
	DeliveryTime = args.GetFloatingValue("delivery");
	NumberOfTimes = GetLookAtTimes().size();
}

unsigned long European::MaxNumberOfCashFlows() const
{
	return 1UL;
}

MJArray European::PossibleCashFlowTimes() const
{
	MJArray tmp(1UL);
	tmp[0] = DeliveryTime;
	return tmp;
}

unsigned long European::CashFlows(const MJArray& SpotValues,
	std::vector<CashFlow>& GeneratedFlows) const
{
	//independently from the look-at-times specified by the user, for a vanilla Option
	// only the final Spot value is necessary.
	GeneratedFlows[0].TimeIndex = 0UL;
	GeneratedFlows[0].Amount = ThePayOff(SpotValues[SpotValues.size() - 1]);

	return 1UL;
}

PathDependent* European::clone() const
{
	return new European(*this);
}

//ARITHMETIC ASIAN

ArithmeticAsian::ArithmeticAsian(ArgumentList args)
	:
	PathDependent(args)
{
	if (args.GetStringValue("name") != "arithmetic-asian")
		throw("Non-arithmetic-asian option argument passed to an arithmetic-asian option");
	DeliveryTime = args.GetFloatingValue("delivery");
	NumberOfTimes = GetLookAtTimes().size();
}

unsigned long ArithmeticAsian::MaxNumberOfCashFlows() const
{
	return 1UL;
}

MJArray ArithmeticAsian::PossibleCashFlowTimes() const
{
	MJArray tmp(1UL);
	tmp[0] = DeliveryTime;
	return tmp;
}

unsigned long ArithmeticAsian::CashFlows(const MJArray& SpotValues,
	std::vector<CashFlow>& GeneratedFlows) const
{
	double sum = SpotValues.sum();
	double mean = sum / NumberOfTimes;

	GeneratedFlows[0].TimeIndex = 0UL;
	GeneratedFlows[0].Amount = ThePayOff(mean);

	return 1UL;
}

PathDependent* ArithmeticAsian::clone() const
{
	return new ArithmeticAsian(*this);
}

//GEOMETRIC ASIAN OPTION

GeometricAsian::GeometricAsian(ArgumentList args)
	:
	PathDependent(args)
{
	if (args.GetStringValue("name") != "geometric-asian")
		throw("Non-geometric-asian option argument passed to a geometric-asian option");
	DeliveryTime = args.GetFloatingValue("delivery");
	NumberOfTimes = GetLookAtTimes().size();
}

unsigned long GeometricAsian::MaxNumberOfCashFlows() const
{
	return 1UL;
}

MJArray GeometricAsian::PossibleCashFlowTimes() const
{
	MJArray tmp(1UL);
	tmp[0] = DeliveryTime;
	return tmp;
}

unsigned long GeometricAsian::CashFlows(const MJArray& SpotValues,
	std::vector<CashFlow>& GeneratedFlows) const
{
	double prod = SpotValues.prod();
	double geoMean = pow(prod, 1.0 / static_cast<double>(NumberOfTimes));

	GeneratedFlows[0].TimeIndex = 0UL;
	GeneratedFlows[0].Amount = ThePayOff(geoMean);

	return 1UL;
}

PathDependent* GeometricAsian::clone() const
{
	return new GeometricAsian(*this);
}

//KNOCK UP-AND-OUT

DiscreteKnockUpOut::DiscreteKnockUpOut(ArgumentList args)
	:
	PathDependent(args)
{
	if (args.GetStringValue("name") != "knock-up-n-out")
		throw("Non-knock-up-n-out option argument passed to a knock-up-n-out option");
	
	DeliveryTime = args.GetFloatingValue("delivery");
	Rebate = args.GetFloatingValue("rebate");
	UpBarrier = args.GetFloatingValue("up-barrier");

	NumberOfTimes = GetLookAtTimes().size();
}

unsigned long DiscreteKnockUpOut::MaxNumberOfCashFlows() const
{
	return 1UL;
}

MJArray DiscreteKnockUpOut::PossibleCashFlowTimes() const
{
	MJArray tmp = GetLookAtTimes();
	return tmp;
}

unsigned long DiscreteKnockUpOut::CashFlows(const MJArray& SpotValues,
	std::vector<CashFlow>& GeneratedFlows) const
{
	//This code assume that GetLookAtTimes().size() == SpotValues.size();
	// It is responsability of the rest of the engine to gaurantee that.
	// however if SpotValues.size() == PossibleCashFlowTimes() than that should be assured.
	bool knockOut = false;
	for (unsigned long i = 0; (i < SpotValues.size()) && (!knockOut); i++)
	{
		if (SpotValues[i] > UpBarrier)
		{
			knockOut = true;
			GeneratedFlows[0].Amount = Rebate;
			GeneratedFlows[0].TimeIndex = i;
		}
	}

	if (!knockOut)
	{
		GeneratedFlows[0].Amount = ThePayOff(SpotValues[SpotValues.size() - 1]);
		GeneratedFlows[0].TimeIndex = SpotValues.size() - 1;
	}

	return 1UL;
}

PathDependent* DiscreteKnockUpOut::clone() const
{
	return new DiscreteKnockUpOut(*this);
}

//KNOCK DOWN-AND-OUT

DiscreteKnockDownOut::DiscreteKnockDownOut(ArgumentList args)
	:
	PathDependent(args)
{
	if (args.GetStringValue("name") != "knock-down-n-out")
		throw("Non-knock-down-n-out option argument passed to a knock-down-n-out option");

	DeliveryTime = args.GetFloatingValue("delivery");
	Rebate = args.GetFloatingValue("rebate");
	LowBarrier = args.GetFloatingValue("low-barrier");

	NumberOfTimes = GetLookAtTimes().size();
}

unsigned long DiscreteKnockDownOut::MaxNumberOfCashFlows() const
{
	return 1UL;
}

MJArray DiscreteKnockDownOut::PossibleCashFlowTimes() const
{
	MJArray tmp = GetLookAtTimes();
	return tmp;
}

unsigned long DiscreteKnockDownOut::CashFlows(const MJArray& SpotValues,
	std::vector<CashFlow>& GeneratedFlows) const
{
	//This code assume that GetLookAtTimes().size() == SpotValues.size();
	// It is responsability of the rest of the engine to gaurantee that.
	// however if SpotValues.size() == PossibleCashFlowTimes() than that should be assured.
	bool knockOut = false;
	for (unsigned long i = 0; (i < SpotValues.size()) && (!knockOut); i++)
	{
		if (SpotValues[i] < LowBarrier)
		{
			knockOut = true;
			GeneratedFlows[0].Amount = Rebate;
			GeneratedFlows[0].TimeIndex = i;
		}
	}

	if (!knockOut)
	{
		GeneratedFlows[0].Amount = ThePayOff(SpotValues[SpotValues.size() - 1]);
		GeneratedFlows[0].TimeIndex = SpotValues.size() - 1;
	}

	return 1UL;
}

PathDependent* DiscreteKnockDownOut::clone() const
{
	return new DiscreteKnockDownOut(*this);
}


//KNOCK UP-AND-IN

DiscreteKnockUpIn::DiscreteKnockUpIn(ArgumentList args)
	:
	PathDependent(args)
{
	if (args.GetStringValue("name") != "knock-up-n-in")
		throw("Non-knock-up-n-in option argument passed to a knock-up-n-in option");

	DeliveryTime = args.GetFloatingValue("delivery");
	Rebate = args.GetFloatingValue("rebate");
	UpBarrier = args.GetFloatingValue("up-barrier");

	NumberOfTimes = GetLookAtTimes().size();

}

unsigned long DiscreteKnockUpIn::MaxNumberOfCashFlows() const
{
	return 1UL;
}

MJArray DiscreteKnockUpIn::PossibleCashFlowTimes() const
{
	MJArray tmp(1UL);
	tmp[0] = DeliveryTime;
	return tmp;
}

unsigned long DiscreteKnockUpIn::CashFlows(const MJArray& SpotValues,
	std::vector<CashFlow>& GeneratedFlows) const
{
	bool knockIn = false;
	for (unsigned long i = 0; (i < SpotValues.size()) && (!knockIn); i++)
	{
		if (SpotValues[i] > UpBarrier)
			knockIn = true;
	}

	if (knockIn)
	{
		GeneratedFlows[0].Amount = ThePayOff(SpotValues[SpotValues.size() - 1]);
		GeneratedFlows[0].TimeIndex = 0UL;
	}
	else
	{
		GeneratedFlows[0].Amount = Rebate;
		GeneratedFlows[0].TimeIndex = 0UL;
	}

	return 1UL;
}

PathDependent* DiscreteKnockUpIn::clone() const
{
	return new DiscreteKnockUpIn(*this);
}

//KNOCK DOWN-AND-IN

DiscreteKnockDownIn::DiscreteKnockDownIn(ArgumentList args)
	:
	PathDependent(args)
{
	if (args.GetStringValue("name") != "knock-down-n-in")
		throw("Non-knock-down-n-in option argument passed to a knock-down-n-in option");

	DeliveryTime = args.GetFloatingValue("delivery");
	Rebate = args.GetFloatingValue("rebate");
	LowBarrier = args.GetFloatingValue("low-barrier");

	NumberOfTimes = GetLookAtTimes().size();

}

unsigned long DiscreteKnockDownIn::MaxNumberOfCashFlows() const
{
	return 1UL;
}

MJArray DiscreteKnockDownIn::PossibleCashFlowTimes() const
{
	MJArray tmp(1UL);
	tmp[0] = DeliveryTime;
	return tmp;
}

unsigned long DiscreteKnockDownIn::CashFlows(const MJArray& SpotValues,
	std::vector<CashFlow>& GeneratedFlows) const
{
	bool knockIn = false;
	for (unsigned long i = 0; (i < SpotValues.size()) && (!knockIn); i++)
	{
		if (SpotValues[i] < LowBarrier)
			knockIn = true;
	}

	if (knockIn)
	{
		GeneratedFlows[0].Amount = ThePayOff(SpotValues[SpotValues.size() - 1]);
		GeneratedFlows[0].TimeIndex = 0UL;
	}
	else
	{
		GeneratedFlows[0].Amount = Rebate;
		GeneratedFlows[0].TimeIndex = 0UL;
	}

	return 1UL;
}

PathDependent* DiscreteKnockDownIn::clone() const
{
	return new DiscreteKnockDownIn(*this);
}