//Taken from Joshi's C++ Design Patterns..
#ifndef SIMPLEMC8_H
#define SIMPLEMC8_H

#include "Vanilla3.h"
#include "Parameters.h"
#include "MCStatistics.h"
#include "Random2.h"

void SimpleMonteCarlo6(
	const VanillaOption& TheOption,
	double Spot,
	const Parameters& Vol,
	const Parameters& r,
	unsigned long NumberOfPaths,
	StatisticsMC& gatherer,
	RandomBase& generator);
#endif

//Personal Comments. 
// This Simulation routine, instead of returning the mean, collects the relevant data 
// simulated into the gatherer. It will be the gatherer  the one required to produce
// the statistics we need.
// We are implementing here a Monte Carlo where I does not metter the nature of 
// the parameters used, as long as their are of type parameters and their Integrals can be
// computed
//The object theOption is passed by reference. It is however
// a const reference, that means that it is not copied but can not be modified as well.