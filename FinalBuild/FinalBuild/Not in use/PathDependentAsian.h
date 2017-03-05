#ifndef PATH_DEPENDENT_ASIAN_H
#define PATH_DEPENDENT_ASIAN_H

#include "PathDependent.h"
#include "PayOffBridge.h"

/*
This derived class provides an implementation of an arithmetic Asian option as a PathDependent class
The payoff of the option is specified by the PayOffBridge Object ThePayOff.
*/

class PathDependentAsian : public PathDependent
{
public:
	PathDependentAsian(const MJArray& LookAtTimes_, 
		double DeliveryTime_, 
		const PayOffBridge& ThePayOff_);
	virtual unsigned long MaxNumberOfCashFlows() const;
	virtual MJArray PossibleCashFlowTimes() const;
	virtual unsigned long CashFlows(const MJArray& SpotValues, 
		std::vector<CashFlow>& GeneratedFlows) const;
	virtual ~PathDependentAsian() {}
	virtual PathDependent* clone() const; 
private:
	double DeliveryTime;
	PayOffBridge ThePayOff;
	unsigned long NumberOfTimes;
};
#endif // !PATH_DEPENDENT_ASIAN_H
