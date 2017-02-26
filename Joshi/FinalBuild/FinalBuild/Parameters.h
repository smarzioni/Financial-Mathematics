#ifndef PARAMETERS_H
#define PARAMETERS_H

//ParametersInner is an abstract class for a parameters of a model.
// In the end it is a an abstract class for integrable and square integrable functions on finite intervals.
// The definition requires that integral and square integrals in finite intervals are implemented by the class.
class ParametersInner
{
public:
	ParametersInner() {}

	virtual ParametersInner* clone() const = 0;
	virtual double Integral(double time1, double time2) const = 0;
	virtual double IntegralSquare(double time1, double time2) const = 0;
	
	virtual ~ParametersInner() {}
	
private:
};

//Parameters is the Bridge Class for the abstract class ParametersInner.
//Moreover it includes two metods (Mean and RootMeanSquare) that can be defined uniquely
// for any well defined Parameter.
class Parameters
{
public:
	Parameters(const ParametersInner& innerObject);
	Parameters(const Parameters& original);
	Parameters& operator=(const Parameters& original);
	virtual ~Parameters();

	inline double Integral(double time1, double time2) const;
	inline double IntegralSquare(double time1, double time2) const;

	double Mean(double time1, double time2) const;
	double RootMeanSquare(double time1, double time2) const;

private:
	ParametersInner* InnerObjectPtr;
};

inline double Parameters::Integral(double time1, double time2) const
{
	return InnerObjectPtr->Integral(time1, time2);
}

inline double Parameters::IntegralSquare(double time1, double time2) const
{
	return InnerObjectPtr->IntegralSquare(time1, time2);
}

//ParameterConstant is a derived Class of PArametersInner which implements
// a parameter constant in time. It should be used together with the Bridge Class 
// Parameters.
class ParametersConstant : public ParametersInner
{
public:
	ParametersConstant(double constant);

	virtual ParametersInner* clone() const;
	virtual double Integral(double time1, double time2) const;
	virtual double IntegralSquare(double time1, double time2) const;

private:
	double Constant;
	double ConstantSquare;
};
#endif // !PARAMETERS_H
