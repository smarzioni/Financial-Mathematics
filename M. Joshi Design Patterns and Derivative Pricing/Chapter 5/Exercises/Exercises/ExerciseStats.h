//Extra statiscs gatherer frome exercises 5.1 and 5.2
#ifndef EXERCISE_STATS_H
#define EXERCISE_STATS_H

#include "MCStatistics.h"

class FourMoments : public StatisticsMC
{
public:
	FourMoments();
	virtual void DumpOneResult(double result);
	virtual std::vector<std::vector<double>> GetResultsSoFar() const;
	virtual StatisticsMC* clone() const;
private:
	std::vector<double> MomentsSums;
	int PathsDone;
};

class ValueAtRisk : public StatisticsMC
{
public:
	ValueAtRisk(double alpha_);
	virtual void DumpOneResult(double result);
	virtual std::vector<std::vector<double>> GetResultsSoFar() const;
	virtual StatisticsMC* clone() const;
private:
	double alpha; //Confidence level (like 0.95)
	std::vector<double> endPaths;
};
#endif // !EXERCISE_STATS_H
