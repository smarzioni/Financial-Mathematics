//Taken from Joshi's C++ Design Patterns..
#ifndef SIMPLEMC4_H
#define SIMPLEMC4_H
#include "Vanilla2.h"

double SimpleMonteCarlo3(
	const VanillaOption& TheOption,
	double Spot,
	double Vol,
	double r,
	unsigned long NumberOfPaths);
#endif

//Personal Comments. The object theOption is passed by reference. It is however
// a const reference, that means that it is not copied but can not be modified as well.
