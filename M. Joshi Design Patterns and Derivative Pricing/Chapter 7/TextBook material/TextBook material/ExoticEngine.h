#ifndef  EXOTIC_ENGINE_H
#define EXOTIC_ENGINE_H

#include "Wrapper.h"
#include "Parameters.h"
#include "MCStatistics.h"
#include "PathDependent.h"
#include <vector>

class ExoticEngine
{
public:
	ExoticEngine(const Wrapper<PathDependent>& TheProduct_, const Parameters&r_);

	virtual void GetOnePath(MJArray& SpotValues) = 0;
	void DoSimulation(StatisticsMC& TheGatherer, unsigned long NumberOfPaths);
	virtual ~ExoticEngine() {}
	double DoOnePAth(const MJArray& SpotValues) const;

private:
	Wrapper<PathDependent> TheProduct;
	Parameters r;
	MJArray Discounts;
	mutable std::vector<CashFlow> TheseCashFlows;
};

#endif // ! EXOTIC_ENGINE_H

// A mutable data memeber in an object can be changed by const methods of the object.
// Here it is used because we do not want to initialize new vectors of cash flow all the times.
// Initialize a vector is dynamic allocation and requires a lot of time. Doing it once far all could
// be a good idea.
