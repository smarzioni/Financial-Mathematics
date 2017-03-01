#ifndef ARG_LIST_FACTORY_HELPER_H
#define ARG_LIST_FACTORY_HELPER_H

#include <string>
#include "ArgListFactory.h"


/* The FactoryHelper<TBase, TDerive>(string id)  constructor register a new type of Creator nella 
	Factory legata a TBase. The new Creator has key the string id and CreatorTFunction specified
	by the return type TDerive*  for the pointed function.
	*/
template<class TBase, class TDerived>
class FactoryHelper
{
public:
	FactoryHelper(std::string);
	static TBase* create(const ArgumentList&);
	~FactoryHelper() {}
};

template<class TBase, class TDerived>
FactoryHelper<TBase, TDerived>::FactoryHelper(std::string id_)
{
	std::string id = MakeLowerCase(id_);
	FactoryInstance<TBase>().RegisterClass(id, FactoryHelper<TBase, TDerived>::create);
}

template<class TBase, class TDerived>
TBase* FactoryHelper<TBase, TDerived>::create(const ArgumentList& Input_)
{
	return new TDerived(Input_);
}
#endif // !ARG_LIST_FACTORY_HELPER
