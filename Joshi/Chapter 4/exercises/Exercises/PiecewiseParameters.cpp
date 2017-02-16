//TO BE TESTED
#include "PiecewiseParameters.h"

ParametersPieceWise::ParametersPieceWise(int n, double constant[],  double times[])
{	
	Times[0] = times[0];
	for (int i = 0; i < n; i++)
	{
		Times[i+1] = times[i+1];
		Constant[i] = constant[i];
		ConstantSquare[i] = Constant[i] * Constant[i];
	}
}

ParametersInner* ParametersPieceWise::clone() const
{
	return new ParametersPieceWise(*this);
}

double ParametersPieceWise::Integral(double time1, double time2) const
{
	double integrate = 0;

	if (time1 < Times[0] || time2 > *Times.end())
		throw("\nExtremes exceeds definition of function.\n");

	int i = 0;
	while (Times[i] < time1) ++i;
	
	integrate += Constant[i - 1] * (Times[i] - time1);
	i++;

	for (; Times[i] < time2; ++i)
	{
		integrate += Constant[i-1] * (Times[i] - Times[i-1]);
	}

	integrate += Constant[i] * (time2 - Times[i - 1]);
	
	return integrate;

}

double ParametersPieceWise::IntegralSquare(double time1, double time2) const
{
	double integrate = 0;

	if (time1 < Times[0] || time2 > *Times.end())
		throw("\nExtremes exceeds definition of function.\n");

	int i = 0;
	while (Times[i] < time1) ++i;

	integrate += ConstantSquare[i - 1] * (Times[i] - time1);
	i++;

	for (; Times[i] < time2; ++i)
	{
		integrate += ConstantSquare[i - 1] * (Times[i] - Times[i - 1]);
	}

	integrate += ConstantSquare[i] * (time2 - Times[i - 1]);

	return integrate;
}