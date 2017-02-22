#ifndef HALTON_H
#define HALTON_H

#include "..\..\Textbook material\Textbook material\Random2.h"
#include <vector>

/*Generator for a sequence of Halton points in (0,1). It will use automatically the first 'dimension'
 prime numbers.
 Seed is the starting point in the Halton sequence and is updated at each point generation. 
 Use it only for LOW dimension, anyway this script works only for dimension <= 95.
 The method GetNextHaltonPoints generates the elements from seed to seed + size -1 */

class Halton
{
public:
	Halton(unsigned int dimension, unsigned long seed = 1);

	std::vector<std::vector<double>> GetNextHaltonPoints(int size);
	//Return Halton points points under in a vector of dimensions vector [size][dimension] 
	void SetSeed(unsigned long Seed);
	void SetDimension(unsigned int dim);
	void Reset(unsigned int dimension, unsigned long seed = 1);

private:
	unsigned long Seed;
	unsigned int dimension;
	std::vector<unsigned int> Basis;

};

class LowDiscrepancyHalton : public RandomBase
{
public:
	LowDiscrepancyHalton(unsigned long Dimensionality, unsigned long Seed = 1);

	virtual RandomBase* clone() const;
	virtual void GetUniforms(MJArray& variates); // Returns Unif(0,1) extremes excluded
	virtual void Skip(unsigned long numberOfPaths);
	virtual void SetSeed(unsigned long Seed);
	virtual void Reset();
	virtual void ResetDimensionality(unsigned long NewDimensionality);

private:
	Halton InnerGenerator;
	unsigned long InitialSeed;
};
#endif // !HALTON_H
