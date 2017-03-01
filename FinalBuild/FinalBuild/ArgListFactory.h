#ifndef ARG_LIST_FACTORY_H
#define ARG_LIST_FACTORY_H

#include "ArgumentList.h"
#include <map>
#include <string>

template<class T>
class ArgListFactory;

template<class T>
ArgListFactory<T>& FactoryInstance()
{
	static ArgListFactory<T> object;
	return object;
}

template<typename T>
class ArgListFactory
{
public:
	friend ArgListFactory<T>& FactoryInstance<>();
	//friend and decleared outside of the class: this function has access to private parts
	// of ArgListFactory<T> but it can be called outside an object

	typedef T* (*CreateTFunction) (const ArgumentList&);
	//CreateTFunction is the type a function pointer to functions of type 
	// T* f(const ArgumentList&)
	//A factory stores couples of keywords and such pointers

	void RegisterClass(std::string ClassId, CreateTFunction);
	//RegisterClass register the couble <ClassId, CreateTFunction> in the Factory.
	// Recall that CreateTFunction is function pointer to T* f(const ArgumentList&)

	T* CreateT(ArgumentList args);
	//this method returns a pointer to a newly initiated object of type T created in agreements
	// with the arguments args

	~ArgListFactory() {};
private:
	std::map<std::string, CreateTFunction> TheCreators;
	std::string KnownTypes;
	ArgListFactory() {} //private default constructor
	ArgListFactory(const ArgListFactory&) {} //private copy constructor
	ArgListFactory& operator=  (const ArgListFactory&) {return *this}
	//private Assignement overload
};

template<typename T>
void ArgListFactory<T>::RegisterClass(std::string ClassId_, CreateTFunction Creator)
{
	std::string  ClassId = MakeLowerCase(ClassId_);
	TheCreators.insert(std::pair<std::string, CreateTFunction>(ClassId, Creator));
	KnownTypes += " " + ClassId;
}

template<typename T>
T* ArgListFactory<T>::CreateT(ArgumentList args)
{
	std::string Id = args.GetStringValue("name");
	//"name" is a key in args expected to return a string key for TheCreators
	// Such key will provide the specific creator we were looking for 
	if (TheCreators.find(Id) == TheCreators.end())
		throw(Id + " is an unknown class. Known types are " + KnownTypes);
	return (TheCreators.find(Id)->second)(args);
}

//easy access function
template<class T>
T* GetFromFactory(const ArgumentList& args)
{
	return FactoryInstance<T>().CreateT(args);
}

#endif //!ARG_LIST_FACTORY_H