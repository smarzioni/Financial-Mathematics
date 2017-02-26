#ifndef TERMINATOR_H
#define TERMINATOR_H

#include <vector>
#include "Wrapper.h"

//This is an answer to exercises 5.4 and 5.5.
//The class Terminator is the abstract type for a class containing terminating conditions
// for a cycle of Monte Carlo simulations. 
//In order to be used the simulations should be done while isTerminate() == false, and 
// every simulation cycle should end with UPDATE();

class Terminator 
{
public:
	Terminator() {}
	virtual void UPDATE() = 0;
	virtual bool isTerminate() const = 0;
	virtual Terminator* clone() const = 0;
	virtual ~Terminator() {}
private:
};

class Counter : public Terminator
{
public:
	Counter(unsigned long N_);
	virtual void UPDATE();
	virtual bool isTerminate() const;
	virtual Terminator* clone() const;
private:
	unsigned long N;
	unsigned long counter;
};

class DoubleTerminator : public Terminator
{
public:
	DoubleTerminator(std::vector<Wrapper<Terminator>>& Inners_);
	virtual void UPDATE();
	virtual bool isTerminate() const;
	virtual Terminator* clone() const;
private:
	std::vector<Wrapper<Terminator>> Inners;
};
#endif // !TERMINATOR_H
