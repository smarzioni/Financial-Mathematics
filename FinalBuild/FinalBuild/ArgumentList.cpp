#include "ArgumentList.h"
#include <algorithm>

//Utilities Definition

//Functions

std::string MakeLowerCase(const std::string& input)
{
	std::string output;
	output.resize(input.size());
	std::transform(input.begin(), input.end(), output.begin(), tolower);
	return output;
}

//private:
void ArgumentList::RegisterName(const std::string& ArgumentName, ArgType type)
{
	ArgumentNames.push_back(std::make_pair(ArgumentName, type));
	//map::insert return a pair; the second element of such pair is bool. Such bool is equal to false
	// if the insertion failed due to a duplicate key.
	if (!(Names.insert(*ArgumentNames.rbegin()).second))
		throw("Same argument name used twice " + ArgumentName + " in List " + GetListName());

	ArgumentsUsed.insert(std::pair<std::string, bool>(ArgumentName, false));
}

void ArgumentList::MarkUsedArgument(const std::string& ArgumentName)
{
	std::string name = MakeLowerCase(ArgumentName);
	ArgumentsUsed.find(ArgumentName)->second = true;
}

//public:

bool ArgumentList::isPresent(const std::string& ArgumentName) const
{
	std::string name = MakeLowerCase(ArgumentName);
	return (Names.find(name) != Names.end());
}

bool ArgumentList::isUsed(const std::string& name_) const
{
	std::string name = MakeLowerCase(name_);
	return !((ArgumentsUsed.find(name))->second);
}

void ArgumentList::throwErrorIfUnused(const std::string& ErrorId) const
{
	std::map<std::string, bool>::const_iterator it;
	std::string unusedNames = "";
	for (it = ArgumentsUsed.begin(); it != ArgumentsUsed.end(); it++)
	{
		if (!it->second) unusedNames += it->first + ", ";
	}
	if (unusedNames != "")
		throw("Error" + ErrorId + "Unused arguments in " + ListName + ": \n" + unusedNames);
}

std::string ArgumentList::GetListName() const
{
	return ListName;
}

const std::vector<std::pair<std::string, ArgumentList::ArgType>>& ArgumentList::GetArgumentsNameAndType() const
{
	return ArgumentNames;
}

//constructor
ArgumentList::ArgumentList(std::string ListName_) : ListName(ListName_) {}

//Add methods definition

void ArgumentList::add(const std::string& name, const std::string& value)
{
	std::string Lname = MakeLowerCase(name);
	stringArguments.insert(std::make_pair(Lname, value));

	ArgType type = string;
	RegisterName(Lname, type);
}

void ArgumentList::add(const std::string& name, const int& value)
{
	std::string Lname = MakeLowerCase(name);
	integerArguments.insert(std::make_pair(Lname, value));

	ArgType type = integer;
	RegisterName(Lname, type);
}

void ArgumentList::add(const std::string& name, const double& value)
{
	std::string Lname = MakeLowerCase(name);
	floatingArguments.insert(std::make_pair(Lname, value));

	ArgType type = floating;
	RegisterName(Lname, type);
}

void ArgumentList::add(const std::string& name, const bool& value)
{
	std::string Lname = MakeLowerCase(name);
	booleanArguments.insert(std::make_pair(Lname, value));

	ArgType type = boolean;
	RegisterName(Lname, type);
}

void ArgumentList::add(const std::string& name, const std::vector<double>& value)
{
	std::string Lname = MakeLowerCase(name);
	vectorDoubleArguments.insert(std::make_pair(Lname, value));

	ArgType type = vectorDouble;
	RegisterName(Lname, type);
}

void ArgumentList::add(const std::string& name, const MJArray& value)
{
	std::string Lname = MakeLowerCase(name);
	mjarrayArguments.insert(std::make_pair(Lname, value));

	ArgType type = mjarray;
	RegisterName(Lname, type);
}

void ArgumentList::add(const std::string& name, const ArgumentList& value)
{
	std::string Lname = MakeLowerCase(name);
	listArguments.insert(std::make_pair(Lname, value));

	ArgType type = Alist;
	RegisterName(Lname, type);
}
///////////////////////////////////////////////////////////////////////

//Retrive Methods definition

std::string ArgumentList::GetStringValue(const std::string& ArgumentName)
{
	std::string name = MakeLowerCase(ArgumentName);
	std::map<const std::string, std::string>::const_iterator retrive = stringArguments.find(name);

	if (retrive == stringArguments.end())
		throw("Impossible to find string argument " + ArgumentName + " in list" + ListName);

	MarkUsedArgument(name);
	return retrive->second;
}

int ArgumentList::GetIntegerValue(const std::string& ArgumentName)
{
	std::string name = MakeLowerCase(ArgumentName);
	std::map<const std::string, int>::const_iterator retrive = integerArguments.find(name);

	if (retrive == integerArguments.end())
		throw("Impossible to find integer " + ArgumentName + " in list" + ListName);

	MarkUsedArgument(name);
	return retrive->second;
}

double ArgumentList::GetFloatingValue(const std::string& ArgumentName)
{
	std::string name = MakeLowerCase(ArgumentName);
	std::map<const std::string, double>::const_iterator retrive = floatingArguments.find(name);

	if (retrive == floatingArguments.end())
		throw("Impossible to find floating " + ArgumentName + " in list" + ListName);

	MarkUsedArgument(name);
	return retrive->second;
}

bool ArgumentList::GetBooleanValue(const std::string& ArgumentName)
{
	std::string name = MakeLowerCase(ArgumentName);
	std::map<const std::string, bool>::const_iterator retrive = booleanArguments.find(name);

	if (retrive == booleanArguments.end())
		throw("Impossible to find boolean " + ArgumentName + " in list" + ListName);

	MarkUsedArgument(name);
	return retrive->second;
}

std::vector<double> ArgumentList::GetVectorDoubleValue(const std::string& ArgumentName)
{
	std::string name = MakeLowerCase(ArgumentName);
	std::map<const std::string, std::vector<double>>::const_iterator retrive 
		= vectorDoubleArguments.find(name);

	if (retrive == vectorDoubleArguments.end())
		throw("Impossible to find vector " + ArgumentName + " in list" + ListName);

	MarkUsedArgument(name);
	return retrive->second;
}

MJArray ArgumentList::GetMJArrayValue(const std::string& ArgumentName)
{
	std::string name = MakeLowerCase(ArgumentName);
	std::map<const std::string, MJArray>::const_iterator retrive = mjarrayArguments.find(name);

	if (retrive == mjarrayArguments.end())
		throw("Impossible to find MjArray " + ArgumentName + " in list" + ListName);

	MarkUsedArgument(name);
	return retrive->second;
}

ArgumentList ArgumentList::GetAlistValue(const std::string& ArgumentName)
{
	std::string name = MakeLowerCase(ArgumentName);
	std::map<const std::string, ArgumentList>::const_iterator retrive = listArguments.find(name);

	if (retrive == listArguments.end())
		throw("Impossible to find child list " + ArgumentName + " in parent list" + ListName);

	MarkUsedArgument(name);
	return retrive->second;
}

///////////////////////////////////////////////////////////////////////
//GET IF PRESENT DEFINITIONS

bool ArgumentList::GetIfPresent(const std::string& ArgumentName, std::string& Value)
{
	if (isPresent(ArgumentName))
	{
		Value = GetStringValue(ArgumentName);
		return true;
	}
	else
		return false;
}

bool ArgumentList::GetIfPresent(const std::string& ArgumentName, int& Value)
{
	if (isPresent(ArgumentName))
	{
		Value = GetIntegerValue(ArgumentName);
		return true;
	}
	else
		return false;
}

bool ArgumentList::GetIfPresent(const std::string& ArgumentName, double& Value)
{
	if (isPresent(ArgumentName))
	{
		Value = GetFloatingValue(ArgumentName);
		return true;
	}
	else
		return false;
}

bool ArgumentList::GetIfPresent(const std::string& ArgumentName, bool& Value)
{
	if (isPresent(ArgumentName))
	{
		Value = GetBooleanValue(ArgumentName);
		return true;
	}
	else
		return false;
}

bool ArgumentList::GetIfPresent(const std::string& ArgumentName, std::vector<double>& Value)
{
	if (isPresent(ArgumentName))
	{
		Value = GetVectorDoubleValue(ArgumentName);
		return true;
	}
	else
		return false;
}

bool ArgumentList::GetIfPresent(const std::string& ArgumentName, MJArray& Value)
{
	if (isPresent(ArgumentName))
	{
		Value = GetMJArrayValue(ArgumentName);
		return true;
	}
	else
		return false;
}

bool ArgumentList::GetIfPresent(const std::string& ArgumentName, ArgumentList& Value)
{
	if (isPresent(ArgumentName))
	{
		Value = GetAlistValue(ArgumentName);
		return true;
	}
	else
		return false;
}