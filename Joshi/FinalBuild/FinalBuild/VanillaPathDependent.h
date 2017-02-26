#ifndef VANILLA_PATH_DEPENDENT_H
#define VANILLA_PATH_DEPENDENT_H

#include "PathDependent.h"
#include "PayOffBridge.h"

//This class implements Vanilla options as an inheruted class of PathDependent

class VanillaPathDependent : public PathDependent
{
public:
	VanillaPathDependent(const MJArray& LookAtTimes_,
		double DeliveryTime_,
		const PayOffBridge& ThePayOff_);
	virtual unsigned long MaxNumberOfCashFlows() const;
	virtual MJArray PossibleCashFlowTimes() const;
	virtual unsigned long CashFlows(const MJArray& SpotValues,
		std::vector<CashFlow>& GeneratedFlows) const;
	virtual ~VanillaPathDependent() {}
	virtual PathDependent* clone() const;
private:
	double DeliveryTime;
	PayOffBridge ThePayOff;
	unsigned long NumberOfTimes;
};
#endif // !PATH_DEPENDENT_ASIAN_H
