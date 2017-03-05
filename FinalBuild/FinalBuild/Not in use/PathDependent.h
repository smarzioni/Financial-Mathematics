#ifndef PATH_DEPENDENT_H
#define PATH_DEPENDENT_H

#include "Arrays.h"
#include <vector>

/* A CashFlow is a class (but works like a struct) containing two memebers: the amount of the cash flow 
	and an integer index. The index is such that it points to the time the cash flow happened inside the array 
	returned by the method PossibleCashFlowTimes() of a PathDependent Option.
A PathDependent is a base class for any path dependent option.
	GetLookAtTimes() returns an array containing the timesat which the option price is registered.
	MaxNumberOfCashFlows() returns the maximum number of cash flows that can happen in a simulation
	PossibleCashFlowTimes() return an array of the times of possible cash flow. These are in general more than
		the  MaxNumberOfCashFlows()
	CashFlows(SpotValues, &GeneratedFlows) will register the cash flows in GeneratedFlows using the Spot values
		provided in SpotValues. It returns the number of cash flows.
	The constructo recieves the argument LookAtTimes, an array containing the times the Spot price should 
		be registered.
*/
class CashFlow
{
public:
	double Amount;
	unsigned long TimeIndex;

	CashFlow(unsigned long TimeIndex_ = 0UL, double Amount_ = 0.0)
		: TimeIndex(TimeIndex_), Amount(Amount_) {};
};

class PathDependent
{
public:
	PathDependent(const MJArray& LookAtTimes);

	const MJArray& GetLookAtTimes() const;

	virtual unsigned long MaxNumberOfCashFlows() const = 0;
	virtual MJArray PossibleCashFlowTimes() const = 0;
	virtual unsigned long CashFlows(const MJArray& SpotValues,
		std::vector<CashFlow>& GeneratedFlows) const = 0;
	virtual PathDependent* clone() const = 0;
	virtual ~PathDependent() {}
private:
	MJArray LookAtTimes;
};

#endif // !PATH_DEPENDENT_H
