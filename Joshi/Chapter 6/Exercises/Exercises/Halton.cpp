
#include "Halton.h"
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const unsigned primes[95] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
	73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
	179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277,
	281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397,
	401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499 };

//The following method computes the coefficients of k in base b and puts them into a vector
// {1, 5} == BaseExpansion(15, 10)
vector<unsigned int> BaseExpansion(unsigned int k, unsigned int b)
{
	int sign = 1;
	if (k == 0)
	{
		vector<unsigned int> Expansion(1);
		Expansion[0] = 0;
		return Expansion;
	}

	unsigned int maxPower = (log(k) / log(b));
	vector<unsigned int> Expansion(maxPower + 1);

	int q = pow(b, maxPower);
	for (int j = 0; j < Expansion.size(); j++)
	{
		Expansion[j] = k / q;
		k -= q * Expansion[j];
		q /= b;
	}
	return Expansion;
}

//The following function reconstructs an integer from its expansion in base b
int DecimalInteger(vector<unsigned int> expansion, unsigned int b)
{
	int k = 0;
	int q = 1;
	for (int j = expansion.size() - 1; j >= 0; j--)
	{
		k += q*expansion[j];
		q *= b;
	}
	return k;
}

//The following method return the expansion in base b of the integer following the integer A
// which is stored in the form of base b-expansion inside the vector expansion;
vector<unsigned int> NextBaseExpansion(vector<unsigned int> expansion, unsigned int b)
{
	int preSize = expansion.size();
	vector<unsigned int> NextExpansion;
	bool Remainding = true;
	for (int j = preSize - 1; j >= 0; j--)
	{
		if (Remainding)
		{
			if (expansion[j] == b - 1)
			{
				NextExpansion.push_back(0);
			}
			else
			{
				NextExpansion.push_back(expansion[j] + 1);
				Remainding = false;
			}
		}
		else 
		{
			NextExpansion.push_back(expansion[j]);
		}
	}

	if (Remainding) NextExpansion.push_back(1);
	reverse(NextExpansion.begin(), NextExpansion.end());

	return NextExpansion;
}

//The following function computes the Van der Corpurt number in (0,1) corresponding to the 
// base b expansion of an integer as stored in the vector expansion;
double VanDerCorput(vector<unsigned int> expansion, int b)
{
	double x = 0;
	double q = 1 / b;
	int m = expansion.size();
	for (int j = 0; j < m; j++)
	{
		x += expansion[m - j - 1] * q;
		q /= b;
	}
	return x;
}


Halton::Halton(unsigned int dimension_, unsigned long seed_) : dimension(dimension_), Seed(seed_)
{
	if (Seed == 0)
		Seed = 1;

	if (dimension > 95)
		throw("\nOnly dimensions <= 95 are accepted by Halton.h\n");
	for (int i = 0; i < dimension; i++)
	{
		Basis[i] = primes[i];
	}
}

void Halton::SetSeed(unsigned long Seed_)
{
	Seed = Seed_;
	if (Seed == 0)
		Seed = 1;
}

void Halton::SetDimension(unsigned int dim)
{
	dimension = dim;
	Seed = 1;
}

vector<vector<double>> Halton::GetNextHaltonPoints(int size)
{
	vector <vector<double>> sequence(size);
	vector<unsigned int> expansions;
	int k = Seed;

	while (k < Seed + size)
	{
		sequence[k - Seed].resize(dimension);

		for (int i = 0; i < dimension; i++)
		{
			expansions = BaseExpansion(k, Basis[i]);
			sequence[k - Seed][i] = VanDerCorput(expansions, Basis[i]);
		}

		k++;
	}

	Seed = Seed + size;
}

void Halton::Reset(unsigned int dimension_, unsigned long seed_)
{
	Seed = seed_;
	dimension = dimension_;

	if (Seed == 0)
		Seed = 1;

	if (dimension > 95)
		throw("\nOnly dimensions <= 95 are accepted by Halton.h\n");
	for (int i = 0; i < dimension; i++)
	{
		Basis[i] = primes[i];
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
