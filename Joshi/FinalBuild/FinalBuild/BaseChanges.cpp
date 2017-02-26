
#include "BaseChanges.h"
#include <vector>
#include <cmath>

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
	for (unsigned int j = 0; j < Expansion.size(); j++)
	{
		Expansion[j] = k / q;
		k -= q * Expansion[j];
		q /= b;
	}
	return Expansion;
}

//The following function reconstructs an integer from its expansion in base b
int DecimalInteger(const vector<unsigned int>& expansion, unsigned int b)
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
vector<unsigned int> NextBaseExpansion(const vector<unsigned int>& expansion, unsigned int b)
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
double VanDerCorput(const vector<unsigned int>& expansion, int b)
{
	double x = 0;
	double q = 1.0 / static_cast<double>(b);
	int m = expansion.size();
	for (int j = 0; j < m; j++)
	{
		x += static_cast<double>(expansion[m - j - 1]) * q;
		q /= b;
	}
	return x;
}