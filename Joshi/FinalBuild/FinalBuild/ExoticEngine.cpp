#include "ExoticEngine.h"
#include <cmath>
ExoticEngine::ExoticEngine(const Wrapper<PathDependent>& TheProduct_, const Parameters& r_)
	: TheProduct(TheProduct_), r(r_), Discounts(TheProduct_->PossibleCashFlowTimes())
{
	//discounts are precomputed at each possible time of a cash flows. Notice that it is responsability
	// of PossibleCashFlowTime() to produce such list of times ordered such that 
	// Discounts[i] contains the discount to apply to a cash flow with member TimeIndex == i.
	for (unsigned long i = 0; i < Discounts.size(); i++)
		Discounts[i] = exp(-r.Integral(0.0, Discounts[i]));

	TheseCashFlows.resize(TheProduct->MaxNumberOfCashFlows());
}

void ExoticEngine::DoSimulation(StatisticsMC& TheGatherer, unsigned long NumberOfPaths)
{
	MJArray SpotValues(TheProduct->GetLookAtTimes().size());

	TheseCashFlows.resize(TheProduct->MaxNumberOfCashFlows());
	double thisValue;

	for (unsigned long i = 0; i < NumberOfPaths; ++i)
	{
		GetOnePath(SpotValues); 
		//Generates a path of spot values
		thisValue = DoOnePAth(SpotValues); 
		//Paths of Spot Values are used to compute cash flows, stored in TheseCashFlows
		TheGatherer.DumpOneResult(thisValue);
		//The Gatherer will store cash flows for this simulation.
	}

	return;
}

double ExoticEngine::DoOnePAth(const MJArray& SpotValues) const
{
	unsigned long NumbersFlows = TheProduct->CashFlows(SpotValues, TheseCashFlows);
	//the line above contains the instruction to write into TheseCashFlows
	double Value = 0.0;
	
	for (unsigned i = 0; i < NumbersFlows; ++i)
		Value += TheseCashFlows[i].Amount * Discounts[TheseCashFlows[i].TimeIndex];

	return Value;
}