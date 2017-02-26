#include "OptionDifference.h"

MJArray UnionTimes(const MJArray& Times1, const MJArray& Times2)
{
	int N = Times1.size() + Times2.size();
	MJArray Times(N);
	int i = 0;
	int j = 0;
	bool Op1Ended = false;
	bool Op2Ended = false;

	if (i == Times1.size()) Op1Ended = true;
	if (j == Times2.size()) Op2Ended = true;

	while (i + j < N)
	{
		if (Op1Ended)
		{
			Times[i + j] = Times2[j];
			j++;
			if (j == Times2.size()) Op2Ended = true;
		}
		else
		{
			if (Op2Ended)
			{
				Times[i + j] = Times1[i];
				i++;
				if (i == Times1.size()) Op1Ended = true;
			}
			else
			{
				if ((Times1[i] >= Times2[j]))
				{
					Times[i + j] = Times2[j];
					j++;
					if (j == Times2.size()) Op2Ended = true;
				}
				else //(Times1[i] < Times2[j])
				{
					Times[i + j] = Times1[i];
					i++;
					if (i == Times1.size()) Op1Ended = true;
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
}

unsigned long OptionDifference::MaxNumberOfCashFlows() const
{
	return Option1->MaxNumberOfCashFlows() +Option2->MaxNumberOfCashFlows();
}

MJArray OptionDifference::PossibleCashFlowTimes() const
{
	MJArray tmp = UnionTimes(Option1->PossibleCashFlowTimes(), Option2->PossibleCashFlowTimes());
	return tmp;
}

unsigned long OptionDifference::CashFlows(const MJArray& SpotValues,
	std::vector<CashFlow>& GeneratedFlows) const
{
	std::vector<CashFlow> Cash1, Cash2;
	int N = Option1->CashFlows(SpotValues, Cash1) + Option2->CashFlows(SpotValues, Cash2);
	std::vector<CashFlow> CashFinal;

	//DA FINIRE

	return 1UL;
}

PathDependent* OptionDifference::clone() const
{
	return new OptionDifference(*this);
}