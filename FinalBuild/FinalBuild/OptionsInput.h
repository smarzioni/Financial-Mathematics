#ifndef OPTIONS_INPUT_H
#define OPTIONS_INPUT_H

#include "Arrays.h"
#include "ArgumentList.h"
#include <string>

class OptionsInput
{
public:
	OptionsInput();

	virtual ArgumentList operator() () = 0;
	virtual ~OptionsInput() {}
	virtual OptionsInput* clone() const = 0;
protected:
	ArgumentList inputData;
};


//Vanilla European option
class EuropeanInput : public OptionsInput
{
public:
	EuropeanInput(ArgumentList args);

	virtual ArgumentList operator() ();
	virtual ~EuropeanInput() {}
	virtual OptionsInput* clone() const;
};

//Arithmetic Asian option
class ArithmeticAsianInput : public OptionsInput
{
public:
	ArithmeticAsianInput(ArgumentList args);

	virtual ArgumentList operator() ();
	virtual ~ArithmeticAsianInput() {}
	virtual OptionsInput* clone() const;
};

//Geometric Asian option
class GeometricAsianInput : public OptionsInput
{
public:
	GeometricAsianInput(ArgumentList args);

	virtual ArgumentList operator() ();
	virtual ~GeometricAsianInput() {}
	virtual OptionsInput* clone() const;
};

//Knock up and out option
class UpAndOutInput : public OptionsInput
{
public:
	UpAndOutInput(ArgumentList args);

	virtual ArgumentList operator() ();
	virtual ~UpAndOutInput() {}
	virtual OptionsInput* clone() const;
};

//Knock down and out option
class DownAndOutInput : public OptionsInput
{
public:
	DownAndOutInput(ArgumentList args);

	virtual ArgumentList operator() ();
	virtual ~DownAndOutInput() {}
	virtual OptionsInput* clone() const;
};

//Knock up and In option
class UpAndInInput : public OptionsInput
{
public:
	UpAndInInput(ArgumentList args);

	virtual ArgumentList operator() ();
	virtual ~UpAndInInput() {}
	virtual OptionsInput* clone() const;
};

//Knock down and In option
class DownAndInInput : public OptionsInput
{
public:
	DownAndInInput(ArgumentList args);

	virtual ArgumentList operator() ();
	virtual ~DownAndInInput() {}
	virtual OptionsInput* clone() const;
};

#endif // !OPTIONS_INPUT_H
