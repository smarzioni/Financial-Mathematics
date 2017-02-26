#include "ExerciseStats.h"
#include <cmath>
#include <algorithm>
//DEBUG:
#include <iostream>

using namespace std;

FourMoments::FourMoments() : MomentsSums({ 0.0,0.0,0.0,0.0 }), PathsDone(0)
{
}

void FourMoments::DumpOneResult(double result)
{
	for (int i = 0; i < 4; i++)
		MomentsSums[i] += pow(result, i + 1);

	PathsDone++;
}


vector<vector<double>> FourMoments::GetResultsSoFar() const
{
	vector<vector<double>> result(1);
	result[0].resize(4);

	for (int i = 0; i < 4; i++)
		result[0][i] = MomentsSums[i] / PathsDone;

	return result;
}

StatisticsMC* FourMoments::clone() const
{
	return new FourMoments(*this);
}

ValueAtRisk::ValueAtRisk(double alpha_) :  alpha(alpha_)
{
	endPaths.resize(0);
}

StatisticsMC* ValueAtRisk::clone() const
{
	return new ValueAtRisk(*this);
}

void ValueAtRisk::DumpOneResult(double result)
{
	endPaths.push_back(result);
}

vector<vector<double>> ValueAtRisk::GetResultsSoFar() const
{
	vector < vector<double>> results(1);
	results[0].resize(1);

	if (alpha < 0 || alpha > 1) throw("\nAlpha should be in (0,1)\n");
	double percent = 1 - alpha;
	
	vector<double> Temps(endPaths);
	sort(Temps.begin(), Temps.end());

	//DEBUG
	//cout << "Vector Temps: \n";
	//for (int i = 0; i < Temps.size(); i++)
	//	cout << Temps[i] << "  ";
	//std::cout << "\npercent " << percent << "\nPaths Size " << Temps.size();

	double index = ceil(percent*(static_cast<double>(Temps.size())));

	//DEBUG
	//std::cout << "\nProduct " << percent*(static_cast<double>(Temps.size()))
	//	<< "\n Ceil " << index << "\n(int) index " << static_cast<int>(index);

	results[0][0] = -Temps[static_cast<int>(index)];
	return results;
}


