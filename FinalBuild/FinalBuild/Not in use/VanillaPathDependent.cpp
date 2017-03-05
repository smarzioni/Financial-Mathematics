#include "VanillaPathDependent.h"

VanillaPathDependent::VanillaPathDependent(const MJArray& LookAtTimes_,
	double DeliveryTime_,
	const PayOffBridge& ThePayOff_)
	:
	PathDependent(LookAtTimes_),
	DeliveryTime(DeliveryTime_),
	ThePayOff(ThePayOff_),
	NumberOfTimes(LookAtTimes_.size())
{
}

unsigned long VanillaPathDependent::MaxNumberOfCashFlows() const
{
	return 1UL;
}

MJArray VanillaPathDependent::PossibleCashFlowTimes() const
{
	MJArray tmp(1UL);
	tmp[0] = DeliveryTime;
	return tmp;
}

unsigned long VanillaPathDependent::CashFlows(const MJArray& SpotValues,
	std::vector<CashFlow>& GeneratedFlows) const
{
	//independently from the look-at-times specified by the user, for a vanilla Option
	// only the final Spot value is necessary.
	GeneratedFlows[0].TimeIndex = 0UL;
	GeneratedFlows[0].Amount = ThePayOff(SpotValues[SpotValues.size() - 1]);

	return 1UL;
}

PathDependent* VanillaPathDependent::clone() const
{
	return new VanillaPathDependent(*this);
}