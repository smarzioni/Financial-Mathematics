#ifndef BASE_CHANGES_H
#define BASE_CHANGES_H

#include <vector>
#include <cmath>

using namespace std;

//The following method computes the coefficients of k in base b and puts them into a vector
// {1, 5} == BaseExpansion(15, 10)
vector<unsigned int> BaseExpansion(unsigned int k, unsigned int b);

//The following function reconstructs an integer from its expansion in base b
int DecimalInteger(const vector<unsigned int>& expansion, unsigned int b);

//The following method return the expansion in base b of the integer following the integer A
// which is stored in the form of base b-expansion inside the vector expansion;
// This procedure is faster then BaseExpansion as it does not involve log and pow;
vector<unsigned int> NextBaseExpansion(const vector<unsigned int>& expansion, unsigned int b);

//The following function computes the Van der Corpurt number in (0,1) corresponding to the 
// base b expansion of an integer as stored in the vector expansion;
double VanDerCorput(const vector<unsigned int>& expansion, int b);

#endif // !BASE_CHANGES_H
