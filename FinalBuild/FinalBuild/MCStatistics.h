#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>
#include <string>

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
	StatisticsMC(std::string name_) : name(name_) {};
	virtual void DumpOneResult(double result) = 0;
	virtual std::vector<std::vector<double>> GetResultsSoFar() const = 0;
	virtual StatisticsMC* clone() const =0;
	virtual ~StatisticsMC() {}
	virtual std::string GetName() const;
protected:
	virtual void SetName(std::string name_);
private:
	std::string name;
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


class Variance : public StatisticsMC
{
public:
	Variance();
	virtual void DumpOneResult(double result);
	virtual std::vector<std::vector<double>> GetResultsSoFar() const;
	virtual StatisticsMC* clone() const;
private:
	double resultSum;
	double SquareDiffSum;
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

#endif
