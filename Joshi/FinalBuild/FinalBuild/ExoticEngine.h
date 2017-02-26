#ifndef  EXOTIC_ENGINE_H
#define EXOTIC_ENGINE_H

#include "Wrapper.h"
#include "Parameters.h"
#include "MCStatistics.h"
#include "PathDependent.h"
#include <vector>

/*This class is the basic engine for Monte Carlo Simulations. 
The output of the simulation is collected in the StatisticsMC object TheGatherer.
The only pure virtual method is GetOnePath(MJArray& SpotValues) which needs to be implemented in some 
derived class. This leave space for use different models in different derivations, as the SpotValues
are effectively computed by this method. ExoticBSEngine.h implement a derived class which follows 
the Black-Scholes model.
*/

class ExoticEngine
{
public:
	ExoticEngine(const Wrapper<PathDependent>& TheProduct_, const Parameters& r_);

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
