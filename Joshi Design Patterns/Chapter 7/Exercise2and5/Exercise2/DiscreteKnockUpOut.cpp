#include "DiscreteKnockUpOut.h"

DiscreteKnockUpOut::DiscreteKnockUpOut(const MJArray& LookAtTimes_,
	double DeliveryTime_,
	double Rebate_,
	double UpBarrier_,
	const PayOffBridge& ThePayOff_)
	:
	PathDependent(LookAtTimes_),
	DeliveryTime(DeliveryTime_),
	Rebate(Rebate_),
	UpBarrier(UpBarrier_),
	ThePayOff(ThePayOff_),
	NumberOfTimes(LookAtTimes_.size())
{
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
		GeneratedFlows[0].Amount = ThePayOff(SpotValues[SpotValues.size() -1]);
		GeneratedFlows[0].TimeIndex = SpotValues.size() - 1;
	}

	return 1UL;
}

PathDependent* DiscreteKnockUpOut::clone() const
{
	return new DiscreteKnockUpOut(*this);
}