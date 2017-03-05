
#include "SeveralStatistics.h"

using namespace std;

SeveralStats::SeveralStats(vector<Wrapper<StatisticsMC>>& Inners_) :StatisticsMC("Collection")
{
	Inners = Inners_;
	vector<Wrapper<StatisticsMC>>::const_iterator it = Inners.begin();
	for (; it != Inners.end(); it++)
	{
		Names.push_back((*it)->GetName());
	}
	
}

void SeveralStats::DumpOneResult(double result)
{
	for (unsigned long i = 0; i < Inners.size(); i++)
		Inners[i]->DumpOneResult(result);
}

std::ostringstream SeveralStats::GetOutputStream() const
{
	std::ostringstream output;
	unsigned long k = 0;
	
	while (k < Inners.size())
	{
		output << Inners[k]->GetName() << std::endl;
		vector<vector<double>> results = Inners[k]->GetResultsSoFar();
		for (unsigned long i = 0; i < results.size(); i++)
		{
			for (unsigned long j = 0; j < results[i].size(); j++)
				output << results[i][j] << " ";

			output << std::endl;
		}
		k++;
		output << "\n";
	}
	return output;
}

vector<vector<double>> SeveralStats::GetResultsSoFar() const
{
	vector<vector<double>> results;
	for (unsigned long k = 0; k < Inners.size(); k++)
	{
		vector<vector<double>> Temp(Inners[k]->GetResultsSoFar());
		for (unsigned long i = 0; i < Temp.size(); i++)
		{
			//Temp[i].push_back(k);
			results.push_back(Temp[i]);
		}
	}
	return results;
}

StatisticsMC* SeveralStats::clone() const
{
	return new SeveralStats(*this);
}