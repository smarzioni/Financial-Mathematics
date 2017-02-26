#ifndef CONVERGENCE_TABLE_H
#define CONVERGENCE_TABLE_H

#include "MCStatistics.h"
#include "Wrapper.h"

//This is a decoration class for any class inherited from MCStatistics". The method ResultsSoFar() will return
// the statistics collected in the Inner class at different times along the simulation (every power of 10 paths).

class ConvergenceTable :public StatisticsMC
{
public:
	ConvergenceTable(const Wrapper<StatisticsMC>& Inner_);

	virtual StatisticsMC* clone() const;
	virtual void DumpOneResult(double result);
	virtual std::vector<std::vector<double>> GetResultsSoFar() const;

private:
	Wrapper<StatisticsMC> Inner;
	std::vector<std::vector<double>> ResultsSoFar;
	unsigned long StoppingPoint;
	unsigned long PathsDone;
};


#endif