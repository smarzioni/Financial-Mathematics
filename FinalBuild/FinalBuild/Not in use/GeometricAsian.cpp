#include "GeometricAsian.h"

GeometricAsian::GeometricAsian(const MJArray& LookAtTimes_,
	double DeliveryTime_,
	const PayOffBridge& ThePayOff_)
	:
	PathDependent(LookAtTimes_),
	DeliveryTime(DeliveryTime_),
	ThePayOff(ThePayOff_),
	NumberOfTimes(LookAtTimes_.size())
{
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
	double geoMean =  pow(prod, 1.0 / static_cast<double>(NumberOfTimes));

	GeneratedFlows[0].TimeIndex = 0UL;
	GeneratedFlows[0].Amount = ThePayOff(geoMean);

	return 1UL;
}

PathDependent* GeometricAsian::clone() const
{
	return new GeometricAsian(*this);
}