//TO BE TESTED
#include "PiecewiseParameters.h"

ParametersPieceWise::ParametersPieceWise(std::vector<double> constant, std::vector<double> times)
{	
	std::vector<double>::iterator i = times.begin();

	for(; i != times.end(); i++)
		Times.push_back(*i);

	std::vector<double>::iterator j = constant.begin();
	for (; j != constant.end(); j++)
	{
		Constant.push_back(*j);
		ConstantSquare.push_back((*j)*(*j));
	}
}

ParametersInner* ParametersPieceWise::clone() const
{
	return new ParametersPieceWise(*this);
}

double ParametersPieceWise::Integral(double time1, double time2) const
{
	double integrate = 0;
	int orientation = 1;
	int steps = 0;

	//check for correct orientation
	if (time1 > time2)
	{
		double temp = time2;
		time2 = time1;
		time1 = temp;
		orientation = -1;
	}

	//check for trivial extremes
	if (time1 == time2) return 0;

	//check for out of range extremes
	if (time1 < Times.front() || time2 > Times.back())
		throw("\nExtremes exceeds definition of function.\n");

	std::vector<double>::const_iterator it = Times.begin();
	std::vector<double>::const_iterator jt = Constant.begin();

	std::vector<double> subTimes;
	std::vector<double> subConst;

	subTimes.push_back(time1);

	if (time1 == *it)
	{
		subConst.push_back(*jt); 
		it++;
	}
	else
	{
		for (; *it < time1; ++it) { steps++; }
		std::advance(jt, steps - 1);
		subConst.push_back(*jt);
	}
	jt++;

	//*it >= time1; *it <= time2 by hypothesis
	for (; *it < time2; it++)
	{
		subTimes.push_back(*it);
		subConst.push_back(*jt);
		jt++;
	}
	subTimes.push_back(time2);
	//Construction of integration vectors subTimes and subConsts ends here.

	//Compute Integrals

	std::vector<double>::const_iterator pt = subTimes.begin();
	std::vector<double>::const_iterator qt = subConst.begin();

	for (; qt != subConst.end(); pt++, qt++)
		integrate += *qt *(*std::next(pt) - *pt);
	
	return orientation * integrate;

}

double ParametersPieceWise::IntegralSquare(double time1, double time2) const
{
	double integrate = 0;
	int orientation = 1;
	int steps = 0;

	//check for correct orientation
	if (time1 > time2)
	{
		double temp = time2;
		time2 = time1;
		time1 = temp;
		orientation = -1;
	}

	//check for trivial extremes
	if (time1 == time2) return 0;

	//check for out of range extremes
	if (time1 < Times.front() || time2 > Times.back())
		throw("\nExtremes exceeds definition of function.\n");

	std::vector<double>::const_iterator it = Times.begin();
	std::vector<double>::const_iterator jt = ConstantSquare.begin();

	std::vector<double> subTimes;
	std::vector<double> subConst;

	subTimes.push_back(time1);

	if (time1 == *it)
	{
		subConst.push_back(*jt);
		it++;
	}
	else
	{
		for (; *it < time1; ++it) { steps++; }
		std::advance(jt, steps - 1);
		subConst.push_back(*jt);
	}
	jt++;

	//*it >= time1; *it <= time2 by hypothesis
	for (; *it < time2; it++)
	{
		subTimes.push_back(*it);
		subConst.push_back(*jt);
		jt++;
	}
	subTimes.push_back(time2);
	//Construction of integration vectors subTimes and subConsts ends here.

	//Compute Integrals

	std::vector<double>::const_iterator pt = subTimes.begin();
	std::vector<double>::const_iterator qt = subConst.begin();

	for (; qt != subConst.end(); pt++, qt++)
		integrate += *qt *(*std::next(pt) - *pt);

	return orientation * integrate;
}