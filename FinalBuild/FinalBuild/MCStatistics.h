#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>
/*
StatisticsMC is a base class designed to collect raw results from a Monte Carlo simulations 
(like the Payoff of a security at expiration) and to return some statistical elaboration of it
(like a the average or covariance matrix).
The user can  store results using the method DumpOneResult(double) and can recover the statiscs elaborated
using GetResultsSoFar()
*/
class StatisticsMC
{
public:
	StatisticsMC() {}

	virtual void DumpOneResult(double result) = 0;
	virtual std::vector<std::vector<double>> GetResultsSoFar() const = 0;
	virtual StatisticsMC* clone() const =0;
	virtual ~StatisticsMC() {}

private:
};

class StatisticsMean : public StatisticsMC
{
public:
	StatisticsMean();
	virtual void DumpOneResult(double result);
	virtual std::vector<std::vector<double>> GetResultsSoFar() const;
	virtual StatisticsMC* clone() const;
	
private:
	double RunningSum;
	unsigned long PathsDone;
};

#endif
