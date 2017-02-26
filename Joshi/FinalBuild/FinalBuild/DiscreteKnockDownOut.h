#ifndef DISCRETE_KNOCK_DOWN_OUT_H
#define DISCRETE_KNOCK_DOWN_OUT_H

#include "PathDependent.h"
#include "PayOffBridge.h"

class DiscreteKnockDownOut : public PathDependent
{
public:
	DiscreteKnockDownOut(const MJArray& LookAtTimes_,
		double DeliveryTime_,
		double Rebate_,
		double DownBarrier_,
		const PayOffBridge& ThePayOff_);
	virtual unsigned long MaxNumberOfCashFlows() const;
	virtual MJArray PossibleCashFlowTimes() const;
	virtual unsigned long CashFlows(const MJArray& SpotValues,
		std::vector<CashFlow>& GeneratedFlows) const;
	virtual ~DiscreteKnockDownOut() {}
	virtual PathDependent* clone() const;
private:
	double DeliveryTime;
	PayOffBridge ThePayOff;
	unsigned long NumberOfTimes;
	double Rebate; //amount paid at knock out
	double DownBarrier; //Knock Down-and-Out barrier
};
#endif // !DISCRETE_KNOCK_OUT_H
