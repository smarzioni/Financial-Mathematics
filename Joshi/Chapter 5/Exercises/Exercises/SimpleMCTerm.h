//Taken from Joshi's C++ Design Patterns..
#ifndef SIMPLEMCTERM_H
#define SIMPLEMCTERM_H

#include "Terminator.h"
#include "Vanilla3.h"
#include "Parameters.h"
#include "MCStatistics.h"

void SimpleMonteCarlo5(
	const VanillaOption& TheOption,
	double Spot,
	const Parameters& Vol,
	const Parameters& r,
	Terminator& term,
	StatisticsMC& gatherer);
#endif

//Personal Comments. 
// This Simulation routine, instead of returning the mean, collects the relevant data 
// simulated into the gatherer. It will be the gatherer  the one required to produce
// the statistics we need.
// We are implementing here a Monte Carlo where I does not metter the nature of 
// the parameters used, as long as their are of type parameters and their Integrals can be
// computed
//The object theOption is passed by reference. It is however
// a const reference, that means that it is not copied but can not be modified as well.#pragma once
