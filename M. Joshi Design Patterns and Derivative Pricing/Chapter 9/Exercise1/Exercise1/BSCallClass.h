#ifndef BS_CALL_CLASS_H
#define BS_CALL_CLASS_H
/*The Class BSCall is just an objec-Function with underlying the classic Black-Scholes formula 
 for pricing a call option. However the object function trates all the variables 
 except the Vol (sigma) as parameters while Vol is used as actual variable.
 In this way our solvers will be able to solve with respect to right variable.*/

class BSCall
{
public:
	BSCall(double r_, double d_, double T_, double Spot_, double Strike_);
	double operator()(double Vol) const;
private:
	double r;
	double d;
	double T;
	double Spot;
	double Strike;
};

#endif // !BS_CALL_CLASS_H
