//TO BE TESTED
//We implement a class of Piecewise constant Parameters

#ifndef PIECEWISEPARAMETERS_H
#define PIECEWISEPARAMETERS_H

#include "Parameters.h"
#include <vector>

class ParametersPieceWise : public ParametersInner
{
public:
	ParametersPieceWise(int n,  double constant[],  double times[]);

	virtual ParametersInner* clone() const;
	virtual double Integral(double time1, double time2) const;
	virtual double IntegralSquare(double time1, double time2) const;

private:
	std::vector<double> Constant;
	std::vector<double> ConstantSquare;
	std::vector<double> Times;
};


#endif