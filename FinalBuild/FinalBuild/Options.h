#ifndef OPTIONS_H
#define OPTIONS_H

#include "ArgumentList.h"
#include "Arrays.h"
#include "PayOff.h"
#include <vector>

/* A CashFlow is a class (but works like a struct) containing two memebers: the amount of the cash flow
and an integer index. The index is such that it points to the time the cash flow happened inside the array
returned by the method PossibleCashFlowTimes() of a PathDependent Option.
A PathDependent is a base class for any path dependent option.
GetLookAtTimes() returns an array containing the timesat which the option price is registered.
MaxNumberOfCashFlows() returns the maximum number of cash flows that can happen in a simulation
PossibleCashFlowTimes() return an array of the times of possible cash flow. These are in general more than
the  MaxNumberOfCashFlows()
CashFlows(SpotValues, &GeneratedFlows) will register the cash flows in GeneratedFlows using the Spot values
provided in SpotValues. It returns the number of cash flows.
The constructo recieves the argument LookAtTimes, an array containing the times the Spot price should
be registered.
*/

class CashFlow
{
public:
	double Amount;
	unsigned long TimeIndex;

	CashFlow(unsigned long TimeIndex_ = 0UL, double Amount_ = 0.0)
		: TimeIndex(TimeIndex_), Amount(Amount_) {};
};

class PathDependent
{
public:
	PathDependent(ArgumentList args);

	const MJArray& GetLookAtTimes() const;

	virtual unsigned long MaxNumberOfCashFlows() const = 0;
	virtual MJArray PossibleCashFlowTimes() const = 0;
	virtual unsigned long CashFlows(const MJArray& SpotValues,
		std::vector<CashFlow>& GeneratedFlows) const = 0;
	virtual PathDependent* clone() const = 0;
	virtual ~PathDependent() {}
protected:
	PayOffBridge ThePayOff;
private:
	MJArray LookAtTimes;
};

//This class implements Vanilla options as an inherited class of PathDependent

class European : public PathDependent
{
public:
	European(ArgumentList args);

	virtual unsigned long MaxNumberOfCashFlows() const;
	virtual MJArray PossibleCashFlowTimes() const;
	virtual unsigned long CashFlows(const MJArray& SpotValues,
		std::vector<CashFlow>& GeneratedFlows) const;
	virtual ~European() {}
	virtual PathDependent* clone() const;
private:
	double DeliveryTime;
	unsigned long NumberOfTimes;
};

//Arithmetic Asian Option
class ArithmeticAsian : public PathDependent
{
public:
	ArithmeticAsian(ArgumentList args);

	virtual unsigned long MaxNumberOfCashFlows() const;
	virtual MJArray PossibleCashFlowTimes() const;
	virtual unsigned long CashFlows(const MJArray& SpotValues,
		std::vector<CashFlow>& GeneratedFlows) const;
	virtual ~ArithmeticAsian() {}
	virtual PathDependent* clone() const;
private:
	double DeliveryTime;
	unsigned long NumberOfTimes;
};

//Geometric Asian Option

class GeometricAsian : public PathDependent
{
public:
	GeometricAsian(ArgumentList args);

	virtual unsigned long MaxNumberOfCashFlows() const;
	virtual MJArray PossibleCashFlowTimes() const;
	virtual unsigned long CashFlows(const MJArray& SpotValues,
		std::vector<CashFlow>& GeneratedFlows) const;
	virtual ~GeometricAsian() {}
	virtual PathDependent* clone() const;
private:
	double DeliveryTime;
	unsigned long NumberOfTimes;
};

//Knock Up-and-Out Option
class DiscreteKnockUpOut : public PathDependent
{
public:
	DiscreteKnockUpOut(ArgumentList args);
	virtual unsigned long MaxNumberOfCashFlows() const;
	virtual MJArray PossibleCashFlowTimes() const;
	virtual unsigned long CashFlows(const MJArray& SpotValues,
		std::vector<CashFlow>& GeneratedFlows) const;
	virtual ~DiscreteKnockUpOut() {}
	virtual PathDependent* clone() const;
private:
	double DeliveryTime;
	unsigned long NumberOfTimes;
	double Rebate; //amount paid at knock out
	double UpBarrier; //Knock Up-and-Out barrier
};

//Knock Down-and-Out Option
class DiscreteKnockDownOut : public PathDependent
{
public:
	DiscreteKnockDownOut(ArgumentList args);
	virtual unsigned long MaxNumberOfCashFlows() const;
	virtual MJArray PossibleCashFlowTimes() const;
	virtual unsigned long CashFlows(const MJArray& SpotValues,
		std::vector<CashFlow>& GeneratedFlows) const;
	virtual ~DiscreteKnockDownOut() {}
	virtual PathDependent* clone() const;
private:
	double DeliveryTime;
	unsigned long NumberOfTimes;
	double Rebate; //amount paid at knock out
	double LowBarrier; //Knock Down-and-Out barrier
};

//Knock Up-and-In Option
class DiscreteKnockUpIn : public PathDependent
{
public:
	DiscreteKnockUpIn(ArgumentList args);
	virtual unsigned long MaxNumberOfCashFlows() const;
	virtual MJArray PossibleCashFlowTimes() const;
	virtual unsigned long CashFlows(const MJArray& SpotValues,
		std::vector<CashFlow>& GeneratedFlows) const;
	virtual ~DiscreteKnockUpIn() {}
	virtual PathDependent* clone() const;
private:
	double DeliveryTime;
	unsigned long NumberOfTimes;
	double Rebate; //amount paid if not Knock in
	double UpBarrier; //Knock Up-and-In barrier
};


//Knock Down-and-In Option
class DiscreteKnockDownIn : public PathDependent
{
public:
	DiscreteKnockDownIn(ArgumentList args);
	virtual unsigned long MaxNumberOfCashFlows() const;
	virtual MJArray PossibleCashFlowTimes() const;
	virtual unsigned long CashFlows(const MJArray& SpotValues,
		std::vector<CashFlow>& GeneratedFlows) const;
	virtual ~DiscreteKnockDownIn() {}
	virtual PathDependent* clone() const;
private:
	double DeliveryTime;
	unsigned long NumberOfTimes;
	double Rebate; //amount paid if not Knock in
	double LowBarrier; //Knock Down-and-In barrier
};
#endif // !OPTIONS_H
