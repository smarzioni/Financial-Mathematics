
#include "Halton.h"
#include "BaseChanges.h"
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const unsigned primes[95] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
	73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
	179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277,
	281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397,
	401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499 };


Halton::Halton(unsigned int dimension_, unsigned long seed_) : dimension(dimension_), Seed(seed_)
{
	if (Seed == 0)
		Seed = 1;

	if (dimension > 95)
		throw("\nOnly dimensions <= 95 are accepted by Halton.h\n");
	Basis.resize(dimension);
	SeedExpansions.resize(dimension);
	for (unsigned int i = 0; i < dimension; i++)
	{
		Basis[i] = primes[i];
		int p = log(Seed) / log(Basis[i]);
		SeedExpansions[i].resize(p + 1);
		SeedExpansions[i] = BaseExpansion(Seed, Basis[i]);
	}
}

void Halton::SetSeed(unsigned long Seed_)
{
	Seed = Seed_;
	if (Seed == 0)
		Seed = 1;
	for (unsigned int i = 0; i < dimension; i++)
	{
		int p = log(Seed) / log(Basis[i]);
		SeedExpansions[i].resize(p + 1);
		SeedExpansions[i] = BaseExpansion(Seed, Basis[i]);
	}
}

void Halton::SetDimension(unsigned int dim)
{
	dimension = dim;
	Seed = 1;
	Basis.resize(dimension);
	SeedExpansions.resize(dimension);
	for (unsigned int i = 0; i < dimension; i++)
	{
		Basis[i] = primes[i];
		int p = log(Seed) / log(Basis[i]);
		SeedExpansions[i].resize(p + 1);
		SeedExpansions[i] = BaseExpansion(Seed, Basis[i]);
	}
}

vector<vector<double>> Halton::GetNextHaltonPoints(unsigned int size)
{
	vector <vector<double>> sequence(size);
	int k = 0;

	while (k < size)
	{
		sequence[k].resize(dimension);

		for (int i = 0; i < dimension; i++)
		{
			sequence[k][i] = VanDerCorput(SeedExpansions[i], Basis[i]);
			SeedExpansions[i] = NextBaseExpansion(SeedExpansions[i], Basis[i]);
		}
		k++;
	}
	Seed = Seed + size;
	return sequence;
}

void Halton::Reset(unsigned int dimension_, unsigned long seed_)
{
	Seed = seed_;
	dimension = dimension_;

	if (Seed == 0)
		Seed = 1;

	if (dimension > 95)
		throw("\nOnly dimensions <= 95 are accepted by Halton.h\n");
	
	Basis.resize(dimension);
	SeedExpansions.resize(dimension);
	for (unsigned int i = 0; i < dimension; i++)
	{
		Basis[i] = primes[i];
		int p = log(Seed) / log(Basis[i]);
		SeedExpansions[i].resize(p + 1);
		SeedExpansions[i] = BaseExpansion(Seed, Basis[i]);
	}
}

LowDiscrepancyHalton::LowDiscrepancyHalton(unsigned long Dimensionality, unsigned long Seed) :
	RandomBase(Dimensionality), InnerGenerator(Dimensionality, Seed), InitialSeed(Seed)
{
}

RandomBase* LowDiscrepancyHalton::clone() const
{
	return new LowDiscrepancyHalton(*this);
}

void LowDiscrepancyHalton::GetUniforms(MJArray& variates)
{
	vector<double> VecVariates;
	VecVariates = (InnerGenerator.GetNextHaltonPoints(1))[0];
	for (unsigned long j = 0; j < GetDimensionality(); j++)
		variates[j] = VecVariates[j];
}

void LowDiscrepancyHalton::Skip(unsigned long numberOfPaths)
{
	MJArray tmp(GetDimensionality());
	for (unsigned long j = 0; j < numberOfPaths; j++)
		GetUniforms(tmp);
}

void LowDiscrepancyHalton::SetSeed(unsigned long Seed)
{
	InitialSeed = Seed;
	InnerGenerator.SetSeed(Seed);
}

void LowDiscrepancyHalton::Reset()
{
	InnerGenerator.Reset(GetDimensionality(), InitialSeed);
}

void LowDiscrepancyHalton::ResetDimensionality(unsigned long NewDimensionality)
{
	RandomBase::ResetDimensionality(NewDimensionality);
	InnerGenerator.Reset(GetDimensionality(), InitialSeed);
}
