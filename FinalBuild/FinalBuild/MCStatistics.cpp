
#include "MCStatistics.h"
#include <algorithm>
#include <sstream>
#include <cmath>
//DEBUG
#include <iostream>

using namespace std;

string StatisticsMC::GetName() const
{
	return name;
}

void StatisticsMC::SetName(string name_)
{
	name = name_;
}

StatisticsMean::StatisticsMean()
	: RunningSum(0.0), PathsDone(0UL), StatisticsMC("Avarage")
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

Variance::Variance()
	: SquareDiffSum(0.0), PathsDone(0UL), resultSum(0.0), 
	StatisticsMC("Standard Deviation")
{
}

void Variance::DumpOneResult(double result)
{
	double PrevAverage;
	if (PathsDone == 0) 
		PrevAverage = 0;
	else
		PrevAverage = resultSum / static_cast<double>(PathsDone);
	
	PathsDone++;
	resultSum += result;
	double average = resultSum / static_cast<double>(PathsDone);
	SquareDiffSum += (result - average)*(result - PrevAverage);
}

vector<vector<double>> Variance::GetResultsSoFar() const
{
	//passing 1 in the constructor force to have a one dimensional vector
	vector<vector<double>> Results(1);

	//resizing force to have a 1x1 vector
	Results[0].resize(1);
	Results[0][0] = sqrt(SquareDiffSum / (PathsDone - 1));

	return Results;
}

StatisticsMC* Variance::clone() const
{
	return new Variance(*this);
}

FourMoments::FourMoments() : MomentsSums({ 0.0,0.0,0.0,0.0 }), PathsDone(0), 
StatisticsMC("First Four Moments")
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

ValueAtRisk::ValueAtRisk(double alpha_) : alpha(alpha_), 
StatisticsMC("Value-at-Risk")
{
	std::ostringstream ostr;
	ostr << GetName() << " " << alpha << " confidence";
	SetName(ostr.str());
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
	std::cout << "Vector Temps: \n";
	for (int i = 0; i < Temps.size(); i++)
		std::cout << Temps[i] << "  ";
	std::cout << "\npercent " << percent << "\nPaths Size " << Temps.size();

	double index = ceil(percent*(static_cast<double>(Temps.size())));

	//DEBUG
	std::cout << "\nProduct " << percent*(static_cast<double>(Temps.size()))
		<< "\n Ceil " << index << "\n(int) index " << static_cast<int>(index);

	results[0][0] = Temps[static_cast<int>(index)];
	return results;
}