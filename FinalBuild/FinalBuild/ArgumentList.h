#ifndef ARGUMENT_LIST_H
#define ARGUMENT_LIST_H
#include <vector>
#include <map>
#include <string>
#include "Arrays.h"

std::string  MakeLowerCase(const std::string& input);
/*
Each argument stored in an ArgumentList has an unique identfying name. This is a lowercase string;
There can only be one argument for each name.
Each argument is of one type (between the types defined in ArgType);
*/

class ArgumentList
{
public:
	//constructor
	ArgumentList(std::string name);
	
	//Arguments Types definition
	enum ArgType
	{
		string, integer, floating, boolean, vectorDouble, mjarray, Alist
	};

	//Populate the list - methods
	void add(const std::string& name, const std::string& value);
	void add(const std::string& name, const int& value);
	void add(const std::string& name, const double& value);
	void add(const std::string& name, const bool& value);
	void add(const std::string& name, const std::vector<double>& value);
	void add(const std::string& name, const MJArray& value);
	void add(const std::string& name, const ArgumentList& value);

	//Retrive elements - methods
	std::string GetStringValue(const std::string& ArgumentName);
	int GetIntegerValue(const std::string& ArgumentName);
	double GetFloatingValue(const std::string& ArgumentName);
	bool GetBooleanValue(const std::string& ArgumentName);
	std::vector<double> GetVectorDoubleValue(const std::string& ArgumentName);
	MJArray GetMJArrayValue(const std::string& ArgumentName);
	ArgumentList GetAlistValue(const std::string& ArgumentName);

	//Retrive optional arguments
	bool GetIfPresent(const std::string& ArgumentName, std::string& Value);
	bool GetIfPresent(const std::string& ArgumentName, int& Value);
	bool GetIfPresent(const std::string& ArgumentName, double& Value);
	bool GetIfPresent(const std::string& ArgumentName, bool& Value);
	bool GetIfPresent(const std::string& ArgumentName, std::vector<double>& Value);
	bool GetIfPresent(const std::string& ArgumentName, MJArray& Value);
	bool GetIfPresent(const std::string& ArgumentName, ArgumentList& Value);

	//Public Utilities
	bool isPresent(const std::string& ArgumentName) const;
	bool isUsed(const std::string& ArgumentName) const;
	void throwErrorIfUnused(const std::string& ErrorId) const;
	std::string GetListName() const;
	const std::vector<std::pair<std::string, ArgType>>& GetArgumentsNameAndType() const; //return ArgumentNames
	
	

private:

	//Private utilities:
	void RegisterName(const std::string& ArgumentName, ArgType type);
	void MarkUsedArgument(const std::string& ArgumentName);

	//Since it can be used in many different context, each AegumentList can store a string name
	//for identification!
	std::string ListName;

	//vector of pairs: to each name of an argument associates its Type (from ArgType)
	std::vector <std::pair<std::string, ArgType>> ArgumentNames;

	//A binary tree listing all the names of the arguments stored in the object and a boolean;
	//The boolean is set to false when the argument is stored, and true one someone retrive it.
	std::map<std::string, bool> ArgumentsUsed;

	//This binary tree permits to retrive a ArgType of an argument from its name
	std::map<std::string, ArgType> Names;

	//Binary trees of arguments stored by type, ordered by name
	std::map<std::string, std::string> stringArguments;
	std::map<std::string, int> integerArguments;
	std::map<std::string, double> floatingArguments;
	std::map<std::string, bool> booleanArguments;
	std::map<std::string, std::vector<double>> vectorDoubleArguments;
	std::map<std::string, MJArray> mjarrayArguments;
	std::map<std::string, ArgumentList> listArguments;
};


#endif //!ARGUMENT_LIST_H