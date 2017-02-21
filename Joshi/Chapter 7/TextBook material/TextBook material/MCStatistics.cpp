
#include "MCStatistics.h"

using namespace std;

StatisticsMean::StatisticsMean()
	: RunningSum(0.0), PathsDone(0UL) //0UL specify that it is an unsigned long to be assigned
{
}

void StatisticsMean::DumpOneResult(double result)
{
	PathsDone++;
	RunningSum += result;
}

vector<vector<double>> StatisticsMean::GetResultsSoFar() const
{
	//passing 1 in the constructor force to have a one dimensional vector
	vector<vector<double>> Results(1); 

	//resizing force to have a 1x1 vector
	Results[0].resize(1);
	Results[0][0] = RunningSum / PathsDone;

	return Results;
}

StatisticsMC* StatisticsMean::clone() const
{
	return new StatisticsMean(*this);
}