#include "Random2.h"
#include "Normals.h"
#include "Arrays.h"

using namespace std;

RandomBase::RandomBase(unsigned long Dimensionality_) : Dimensionality(Dimensionality_)
{
}

void RandomBase::GetGaussians(MJArray& variates)
{
	GetUniforms(variates);
	for (unsigned long i = 0; i < Dimensionality; i++)
	{
		double x = variates[i];
		variates[i] = InverseCumulativeNormal(x);
	}
}

void RandomBase::ResetDimensionality(unsigned long NewDimensionality)
{
	Dimensionality = NewDimensionality;
}

