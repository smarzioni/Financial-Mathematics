#ifndef PARK_MILLER_H
#define PARK_MILLER_H

#include "Random2.h"

/* ParkMiller is a class for uniform random number generation which follows Park Miller algorithm.
*/

class ParkMiller
{
public:
	ParkMiller(long seed = 1);

	long GetOneRandomInteger();
	void SetSeed(long Seed);

	static unsigned long Max();
	static unsigned long Min();

private:
	long Seed;
};

/* RandomParkMiller is a class derived from RanddomBase which implements the generation of Monte Carlo paths
	starting with ParkMiller as inner generator for uniforms.
*/

class RandomParkMiller : public RandomBase
{
public:
	RandomParkMiller(unsigned long Dimensionality, unsigned long Seed = 1);

	virtual RandomBase* clone() const;
	virtual void GetUniforms(MJArray& variates); // Returns Unif(0,1) extremes excluded
	virtual void Skip(unsigned long numberOfPaths);
	virtual void SetSeed(unsigned long Seed);
	virtual void Reset();
	virtual void ResetDimensionality(unsigned long NewDimensionality);

private:
	ParkMiller InnerGenerator;
	unsigned long InitialSeed;
	double Reciprocal; //Reciprocal of (1+ RandMax)
};
#endif // !PARK_MILLER_H
