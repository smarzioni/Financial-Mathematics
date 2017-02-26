
#include "SeveralStatistics.h"

using namespace std;

SeveralStats::SeveralStats(vector<Wrapper<StatisticsMC>>& Inners_)
{
	Inners = Inners_;
}

void SeveralStats::DumpOneResult(double result)
{
	for (unsigned long i = 0; i < Inners.size(); i++)
		Inners[i]->DumpOneResult(result);
}

vector<vector<double>> SeveralStats::GetResultsSoFar() const
{
	vector<vector<double>> results;
	for (unsigned long k = 0; k < Inners.size(); k++)
	{
		vector<vector<double>> Temp(Inners[k]->GetResultsSoFar());
		for (unsigned long i = 0; i < Temp.size(); i++)
		{
			Temp[i].push_back(k);
			results.push_back(Temp[i]);
		}
	}
	return results;
}

StatisticsMC* SeveralStats::clone() const
{
	return new SeveralStats(*this);
}