#ifndef SEVERAL_STATISTICS_H
#define SEVERAL_STATISTICS_H

#include <vector>
#include "MCStatistics.h"
#include "Wrapper.h"

class SeveralStats : public StatisticsMC
{
public:
	SeveralStats(std::vector<Wrapper<StatisticsMC>>& Inners_);

	virtual void DumpOneResult(double result);
	virtual std::vector<std::vector<double>> GetResultsSoFar() const;
	virtual StatisticsMC* clone() const;

private:
	std::vector<Wrapper<StatisticsMC>> Inners;
};

#endif // !SEVERAL_STATISTICS_H
