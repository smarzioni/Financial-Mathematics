
#include "Terminator.h"

using namespace std;

Counter::Counter(unsigned long N_)
	: N(N_), counter(0)
{
}

void Counter::UPDATE()
{
	counter++;
}

bool Counter::isTerminate() const
{
	bool result = (counter >= N) ? true : false;
	return result;
}

Terminator* Counter::clone() const
{
	return new Counter(*this);
}

DoubleTerminator::DoubleTerminator(vector<Wrapper<Terminator>>& Inners_)
{
	Inners = Inners_;
}

void DoubleTerminator::UPDATE()
{
	for (unsigned long i = 0; i < Inners.size(); i++)
		Inners[i]->UPDATE();
}

bool DoubleTerminator::isTerminate() const
{
	bool result = false;
	for (unsigned long i = 0; i < Inners.size(); i++)
		result = (result || Inners[i]->isTerminate());

	return result;
}

Terminator* DoubleTerminator::clone() const
{
	return new DoubleTerminator(*this);
}
