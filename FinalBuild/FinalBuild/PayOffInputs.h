#ifndef PAYOFF_INPUTS_H
#define PAYOFF_INPUTS_H

#include "ArgumentList.h"
#include <string>


class POInputs
{
public:
	POInputs();

	virtual ArgumentList operator() () = 0;
	virtual ~POInputs() {} 
	virtual POInputs* clone() const = 0;
protected:
	ArgumentList inputData;
};

class POCallInputs : public POInputs
{
public:
	POCallInputs(ArgumentList args);
	virtual ArgumentList operator() ();
	virtual ~POCallInputs() {}
	virtual POInputs* clone() const;
};


class POPutInputs : public POInputs
{
public:
	POPutInputs(ArgumentList args);
	virtual ArgumentList operator() ();
	virtual ~POPutInputs() {}
	virtual POInputs* clone() const;
};

class POSpreadInputs : public POInputs
{
public:
	POSpreadInputs(ArgumentList args);
	virtual ArgumentList operator() ();
	virtual ~POSpreadInputs() {}
	virtual POInputs* clone() const;
};

class PODoubleDInputs : public POInputs
{
public:
	PODoubleDInputs(ArgumentList args);
	virtual ArgumentList operator() ();
	virtual ~PODoubleDInputs() {}
	virtual POInputs* clone() const;
};

class PODCallInput : public POInputs
{
public:
	PODCallInput(ArgumentList args);
	virtual ArgumentList operator() ();
	virtual ~PODCallInput() {}
	virtual POInputs* clone() const;
};

class PODPutInput : public POInputs
{
public:
	PODPutInput(ArgumentList args);
	virtual ArgumentList operator() ();
	virtual ~PODPutInput() {}
	virtual POInputs* clone() const;
};


#endif //!PAYOFF_INPUTS_H