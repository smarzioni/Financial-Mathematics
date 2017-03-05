
//This header defines an array class called MJArray which has a similar (subset of) interface of
// the class valarray from the STD Library. It will hovever make Range Checkings, impossible 
// for valarray. These checks have negative impact on speed, and can be deactivated in MJArray
// defining the global contant RANGE_CHECKING.
//For compatibility reasons, defining the macro USE_VAL_ARRAY will replace the definition of MJArray
// with the definition of valrray from the standard library. 
#ifndef MJARRAYS_H
#define MJARRAYS_H
#define RANGE_CHECKING
#pragma warning(disable : 4996)
#ifdef USE_VAL_ARRAY

#include <valarray>
typedef std::valarray<double> MJArray;

#else // if USE_VAL_ARRAY not defined

class MJArray
{
public:
	explicit MJArray(unsigned long size = 0); 
	//explicit keyword avoids implicit constructor conversions

	MJArray(const MJArray& original);
	~MJArray();

	MJArray& operator= (const MJArray& original);
	MJArray& operator= (const double& val);

	MJArray& operator+= (const MJArray& operand);
	MJArray& operator-= (const MJArray& operand);
	MJArray& operator*= (const MJArray& operand);
	MJArray& operator/= (const MJArray& operand);

	MJArray& operator+= (const double& operand);
	MJArray& operator-= (const double& operand);
	MJArray& operator*= (const double& operand);
	MJArray& operator/= (const double& operand);

	MJArray apply(double f(double)) const;

	inline double operator[](unsigned long i) const;
	inline double& operator[](unsigned long i);

	inline unsigned long size() const;

	void resize(unsigned long newSize);
	//resize() won't preserve the content of the object!

	double sum() const;
	double min() const;
	double max() const;
	double prod() const;

private:
	double* ValuesPtr;
	double* EndPtr;

	unsigned long Size;
	unsigned long Capacity;
};

inline double MJArray::operator[](unsigned long i) const
{
#ifdef RANGE_CHECKING
	if (i >= Size)
	{
		throw("\nIndex out of range");
	}
#endif
	return ValuesPtr[i];
}

inline double& MJArray::operator[](unsigned long i)
{
#ifdef RANGE_CHECKING
	if (i >= Size)
	{
		throw("\nIndex out of range\n");
	}
#endif

	return ValuesPtr[i];
}

inline unsigned long MJArray::size() const
{
	return Size;
}

#endif
#endif
