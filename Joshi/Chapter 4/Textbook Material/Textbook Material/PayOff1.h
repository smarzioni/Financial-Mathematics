//Taken from Joshi's C++ Design Patterns...
#ifndef PAYOFF_H
#define PAYOFF_H

class PayOff
{
public:
	enum OptionType {call, put};
	PayOff(double Strike_, OptionType TheOptionType_);
	double operator()(double spot) const;

private:
	double Strike;
	OptionType TheOptionsType;
};

#endif

//PERSONAL COMMENTS: Forst class defined in the book.
//OptionType is anew type admitting two values, put and call. Compared to C, in C++ writing 
//'enum OptionType' shoul implicitly put a typedef in front.
//The operator() is overloaded so that, after having created an opject, e.g.
//PayOff thisPO(Strike, PayOff::call)
//Future use of thisPO(Strike) want admit a second argument. This is a screen against
// changing the OptionType, something that we do not want to happen.
//The overloaded operator( double Spot) is declared const: in this way any object of 
//class PayOff won't be able to modify the object itself with this operator.
//In particular it is possible to create const objects of type PayOff.