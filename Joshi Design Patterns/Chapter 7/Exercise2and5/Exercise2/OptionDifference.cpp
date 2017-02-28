#include "OptionDifference.h"

MJArray UnionTimes(const MJArray& Times1, const MJArray& Times2)
{
	//Times1 and Times2 are suppose ordered increasingly.
	int N = Times1.size() + Times2.size();
	MJArray Times(N);
	int i = 0;
	int j = 0;
	bool Op1Ended = false;
	bool Op2Ended = false;

	if (i == Times1.size()) Op1Ended = true;
	if (j == Times2.size()) Op2Ended = true;

	int k = 0;
	while (i + j + k < N)
	{
		if (Op1Ended)
		{
			Times[i + j + k] = Times2[j];
			j++;
			if (j == Times2.size()) Op2Ended = true;
		}
		else
		{
			if (Op2Ended)
			{
				Times[i + j + k] = Times1[i];
				i++;
				if (i == Times1.size()) Op1Ended = true;
			}
			else
			{
				if ((Times1[i] > Times2[j]))
				{
					Times[i + j + k] = Times2[j];
					j++;
					if (j == Times2.size()) Op2Ended = true;
				}
				else
				{
					if (Times1[i] < Times2[j])
					{
						Times[i + j + k] = Times1[i];
						i++;
						if (i == Times1.size()) Op1Ended = true;
					}
					else //Times1[i] == Times2[j]
					{
						Times[i + j + k] = Times1[i];
						k--;
						j++;
						i++;
						if (j == Times2.size()) Op2Ended = true;
						if (i == Times1.size()) Op1Ended = true;
					}
				}
			}
		}
	}
}

OptionDifference::OptionDifference(Wrapper<PathDependent>& Option1_,
	Wrapper<PathDependent>& Option2_)
	:	Option1(Option1_), Option2(Option2_), 
	PathDependent(UnionTimes(Option1_->GetLookAtTimes(), Option2_->GetLookAtTimes))
{
	MJArray Possible1 = Option1->PossibleCashFlowTimes();
	MJArray Possible2 = Option2->PossibleCashFlowTimes();

	PossibleCashFlow = UnionTimes(Possible1, Possible2);

	for (unsigned long i = 0; i < Possible1.size(); i++)
	{
		int k = 0;
		while (PossibleCashFlow[k] != Possible1[i])	k++;
		TimeIndex1[i] = k;
	}

	for (unsigned long i = 0; i < Possible2.size(); i++)
	{
		int k = 0;
		while (PossibleCashFlow[k] != Possible2[i])	k++;
		TimeIndex2[i] = k;
	}

}

unsigned long OptionDifference::MaxNumberOfCashFlows() const
{
	return Option1->MaxNumberOfCashFlows() +Option2->MaxNumberOfCashFlows();
}

MJArray OptionDifference::PossibleCashFlowTimes() const
{
	return PossibleCashFlow;
}

unsigned long OptionDifference::CashFlows(const MJArray& SpotValues,
	std::vector<CashFlow>& GeneratedFlows) const
{
	std::vector<CashFlow> Cash1, Cash2;
	int N = Option1->CashFlows(SpotValues, Cash1) + Option2->CashFlows(SpotValues, Cash2);
	GeneratedFlows.resize(N);

	for (unsigned long i = 0; i < Cash1.size(); i++)
	{
		CashFlow ThisOne;
		ThisOne.Amount = Cash1[i].Amount;
		ThisOne.TimeIndex = TimeIndex1[Cash1[i].TimeIndex];
		GeneratedFlows.push_back(ThisOne);
	}

	for (unsigned long i = 0; i < Cash2.size(); i++)
	{
		CashFlow ThisOne;
		ThisOne.Amount = -Cash2[i].Amount;
		ThisOne.TimeIndex = TimeIndex2[Cash2[i].TimeIndex];
		GeneratedFlows.push_back(ThisOne);
	}

	//TO BE FINISHED

	return 1UL;
}

PathDependent* OptionDifference::clone() const
{
	return new OptionDifference(*this);
}