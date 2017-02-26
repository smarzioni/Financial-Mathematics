#ifndef RANDOM2_H
#define RANDOM2_H

#include "Arrays.h"

/* The class RandmBase is the base class to generate random paths in the Monte Carlo simulation.
	The generation is multidimensional, of dimension Dimensionality;
	GetUniforms(MJArray& variates) writes a dimensionality-tuple of uniforms iid into variates.
	GetGaussian(MJArray& variates) writes a dimensionality-tuple of normals iid into variates.
	Skip(N) runs, but not register, N iterations of GetUniforms() (and GetGaussians());
	REMARK: The path generation is deterministic: if we start two different objects of the same 
		RandomBase class with same Seed and same Dimensionality they will produce the same sequence of 
		random paths.
*/

class RandomBase
{
public:
	RandomBase(unsigned long Dimensionality_);

	inline unsigned long GetDimensionality() const;

	virtual RandomBase* clone() const = 0;
	virtual void GetUniforms(MJArray&  variates) = 0;
	virtual void Skip(unsigned long numberOfPaths) = 0;
	virtual void SetSeed(unsigned long Seed) = 0;
	virtual void Reset() = 0;
	virtual void GetGaussians(MJArray& variates);
	virtual void ResetDimensionality(unsigned long NewDimensionality);

private:
	unsigned long Dimensionality;
};

inline unsigned long RandomBase::GetDimensionality() const
{
	return Dimensionality;
}

#endif