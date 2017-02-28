#ifndef OPTION_DIFFERENCE_H
#define OPTION_DIFFERENCE_H

#include "..\..\TextBook material\TextBook material\PathDependent.h"
#include "..\..\TextBook material\TextBook material\PayOffBridge.h"
#include "..\..\TextBook material\TextBook material\Wrapper.h" 
#include <vector>

/* The Class OptionDifference is defined by two path-dependent options and pays the difference in 
	PayOff of Option1 minus Option2.
*/

class OptionDifference : public PathDependent
{
public:
	OptionDifference(Wrapper<PathDependent>& Option1_, Wrapper<PathDependent>& Option2_);
	virtual unsigned long MaxNumberOfCashFlows() const;
	virtual MJArray PossibleCashFlowTimes() const;
	virtual unsigned long CashFlows(const MJArray& SpotValues,
		std::vector<CashFlow>& GeneratedFlows) const;
	virtual ~OptionDifference() {}
	virtual PathDependent* clone() const;
private:
	Wrapper<PathDependent> Option1;
	Wrapper<PathDependent> Option2;
	/* TimeIndex1 and 2 converts the TimeIndex arguments of the cashFlows of option1 (and 2)
	 to the TimeIndex of the Corresponding CashFlow at ofOptionDifference*/
	std::vector<unsigned long> TimeIndex1;
	std::vector<unsigned long> TimeIndex2;
	MJArray PossibleCashFlow;
};
#endif // !OPTION_DIFFERENCE_H
