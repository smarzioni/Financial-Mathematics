#ifndef ANTITHETIC_H
#define ANTITHETIC_H

#include "Random2.h"
#include "Wrapper.h"

//AntiThetic is a decoration for a random Path Generator of type inherited from RandomBase.
// It makes the the generation antithetic providing a uniform (1 - u) after every uniform u.
// As a consequence, every normal X will be followed by the normal -X.

class AntiThetic : public RandomBase
{
public:
	AntiThetic(const Wrapper<RandomBase>& innerGenerator);

	virtual RandomBase* clone() const;
	virtual void GetUniforms(MJArray& variates);
	virtual void Skip(unsigned long numberOfPaths);
	virtual void SetSeed(unsigned long Seed);
	virtual void ResetDimensionality(unsigned long NewDimensionality);
	virtual void Reset();

private:
	Wrapper<RandomBase> InnerGenerator;
	bool OddEven;
	MJArray NextVariates;
};

#endif // !ANTITHETIC_H
