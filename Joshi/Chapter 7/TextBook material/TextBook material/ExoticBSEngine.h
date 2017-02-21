#ifndef EXOTIC_BS_ENGINE_H
#define EXOTIC_BS_ENGINE_H

#include "ExoticEngine.h"
#include "Random2.h"
/*This Class computes Stock Value S(t_k) for a partition {t_k}_k of the interval [0,T] following
	the Black Scholes model dS(t) = (R(t) - D(t))*S(t)dt + sigma(t)*S(t) dW_t */

class ExoticBSEngine : public ExoticEngine
{
public:
	ExoticBSEngine(const Wrapper<PathDependent>& TheProduct_,
		const Parameters& R_,
		const Parameters& D_,
		const Parameters& Vol_,
		const Wrapper<RandomBase>& TheGenerator_,
		double Spot_);
	virtual void GetOnePath(MJArray& SpotValues);
	virtual ~ExoticBSEngine() {}

private:
	Wrapper<RandomBase> TheGenerator;
	MJArray Drifts; //(R(t_k) - D(t_k) - 0.5 sigma^2(t_k))
	MJArray StandardDeviations; //sigma(t_k)
	double LogSpot; //log(S_0)
	unsigned long NumberOfTimes; //cardinality of the partition {t_k}_k
	MJArray Variates;
};

#endif // !EXOTIC_BS_ENGINE_H
