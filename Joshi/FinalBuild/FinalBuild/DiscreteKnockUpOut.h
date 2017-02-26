#ifndef DISCRETE_KNOCK_UP_OUT_H
#define DISCRETE_KNOCK_UP_OUT_H

#include "PathDependent.h"
#include "PayOffBridge.h"

class DiscreteKnockUpOut : public PathDependent
{
public:
	DiscreteKnockUpOut(const MJArray& LookAtTimes_,
		double DeliveryTime_,
		double Rebate_,
		double UpBarrier_,
		const PayOffBridge& ThePayOff_);
	virtual unsigned long MaxNumberOfCashFlows() const;
	virtual MJArray PossibleCashFlowTimes() const;
	virtual unsigned long CashFlows(const MJArray& SpotValues,
		std::vector<CashFlow>& GeneratedFlows) const;
	virtual ~DiscreteKnockUpOut() {}
	virtual PathDependent* clone() const;
private:
	double DeliveryTime;
	PayOffBridge ThePayOff;
	unsigned long NumberOfTimes;
	double Rebate; //amount paid at knock out
	double UpBarrier; //Knock Up-and-Out barrier
};
#endif // !DISCRETE_KNOCK_OUT_H
