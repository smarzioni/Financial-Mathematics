//Taken from Joshi's C++ Design Patterns..
#ifndef SIMPLEMC_H
#define SIMPLEMC_H
#include "PayOff1.h"

double SimpleMonteCarlo2(
	const PayOff& thePayOff,
	double Expiry,
	double Spot,
	double Vol,
	double r,
	unsigned long NumberOfPaths);
#endif

//Personal Comments. The object thePayoff is passed by reference. In particular it can
//be modified.

