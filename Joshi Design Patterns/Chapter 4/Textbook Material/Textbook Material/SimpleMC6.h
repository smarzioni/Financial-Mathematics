//Taken from Joshi's C++ Design Patterns..
#ifndef SIMPLEMC6_H
#define SIMPLEMC6_H
#include "Vanilla3.h"
#include "Parameters.h"

double SimpleMonteCarlo4(
	const VanillaOption& TheOption,
	double Spot,
	const Parameters& Vol,
	const Parameters& r,
	unsigned long NumberOfPaths);
#endif

//Personal Comments. 
// We are implementing here a Monte Carlo where I does not metter the nature of 
// the parameters used, as long as their are of type parameters and their Integrals can be
// computed
//The object theOption is passed by reference. It is however
// a const reference, that means that it is not copied but can not be modified as well.