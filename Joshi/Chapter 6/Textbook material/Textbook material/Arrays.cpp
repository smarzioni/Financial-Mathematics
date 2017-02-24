#pragma warning (disable : 4996)
#include "Arrays.h"
#include <algorithm>
#include <numeric>

MJArray::MJArray(unsigned long size) : Size(size), Capacity(size)
{
	if (Size > 0)
	{
		ValuesPtr = new double[size];
		EndPtr = ValuesPtr + Size;
	}
	else
	{
		ValuesPtr = 0;
		EndPtr = 0;
	}
}

MJArray::MJArray(const MJArray& original) : Size(original.size()), Capacity(original.size())
{
	if (Size > 0)
	{
		ValuesPtr = new double[Size];
		EndPtr = ValuesPtr + Size;
		std::copy(original.ValuesPtr, original.EndPtr, ValuesPtr);
	}
	else
	{
		ValuesPtr = 0;
		EndPtr = 0;
	}
}

MJArray::~MJArray()
{
	if (ValuesPtr > 0)
		delete[] ValuesPtr;
}

MJArray& MJArray::operator=(const MJArray& original)
{
	if (&original == this)
		return *this;

	if (original.size() > Capacity)
	{
		if (Capacity > 0)
			delete[] ValuesPtr;
		ValuesPtr = new double[original.size()];
		Capacity = original.size();
	}

	Size = original.size();
	EndPtr = ValuesPtr + Size;

	std::copy(original.ValuesPtr, original.EndPtr, ValuesPtr);

	return *this;
}

void MJArray::resize(unsigned long newSize) 
{
	if (newSize > Capacity)
	{
		if (Capacity > 0)
			delete[] ValuesPtr;

		ValuesPtr = new double[newSize];

		Capacity = newSize;
	}
	Size = newSize;

	EndPtr = ValuesPtr + Size;
}

MJArray& MJArray::operator+=(const MJArray& operand)
{
#ifdef RANGE_CHECKING
	if (Size != operand.size())
		throw("\n+= requires operands of the same size");
#endif // RANGE_CHECKING
	for (unsigned long i = 0; i < Size; i++)
		ValuesPtr[i] += operand[i];

	return *this;
}

MJArray& MJArray::operator-=(const MJArray& operand)
{
#ifdef RANGE_CHECKING
	if (Size != operand.size())
		throw("\n-= requires operands of the same size");
#endif // RANGE_CHECKING
	for (unsigned long i = 0; i < Size; i++)
		ValuesPtr[i] -= operand[i];

	return *this;
}

MJArray& MJArray::operator*=(const MJArray& operand)
{
#ifdef RANGE_CHECKING
	if (Size != operand.size())
		throw("\n*= requires operands of the same size");
#endif // RANGE_CHECKING
	for (unsigned long i = 0; i < Size; i++)
		ValuesPtr[i] *= operand[i];

	return *this;
}

//REMARK: There is no check against division by 0;
MJArray& MJArray::operator/=(const MJArray& operand)
{
#ifdef RANGE_CHECKING
	if (Size != operand.size())
		throw("\n/= requires operands of the same size");
#endif // RANGE_CHECKING
	for (unsigned long i = 0; i < Size; i++)
		ValuesPtr[i] /= operand[i];

	return *this;
}

///////////////////////////////////////////////////

MJArray& MJArray::operator+=(const double& operand)
{
	for (unsigned long i = 0; i < Size; i++)
		ValuesPtr[i] += operand;
	
	return *this;
}

MJArray& MJArray::operator-=(const double& operand)
{
	for (unsigned long i = 0; i < Size; i++)
		ValuesPtr[i] -= operand;

	return *this;
}

MJArray& MJArray::operator*=(const double& operand)
{
	for (unsigned long i = 0; i < Size; i++)
		ValuesPtr[i] *= operand;

	return *this;
}

MJArray& MJArray::operator/=(const double& operand)
{
	for (unsigned long i = 0; i < Size; i++)
		ValuesPtr[i] /= operand;

	return *this;
}

MJArray& MJArray::operator=(const double& val)
{
	for (unsigned long i = 0; i < Size; i++)
		ValuesPtr[i] = val;

	return *this;
}

double MJArray::sum() const
{
	return std::accumulate(ValuesPtr, EndPtr, 0.0);
}

double MJArray::min() const
{
#ifdef RANGE_CHECKING
	if (Size == 0)
		throw("\nCannot take min of empty array");
#endif //RANGE_CHECKING
	double* tmp = ValuesPtr;
	double* endTmp = EndPtr;
	//I am not sure why he is not passing directly ValuesPtr and EndPtr.
	//I could not find any information regarding the behaviour of min_elemnt on its arguments.
	return *std::min_element(tmp, endTmp);
}

double MJArray::max() const
{
#ifdef RANGE_CHECKING
	if (Size == 0)
		throw("\nCannot take max of empty array");
#endif //RANGE_CHECKING
	double* tmp = ValuesPtr;
	double* endTmp = EndPtr;
	//I am not sure why he is not passing directly ValuesPtr and EndPtr.
	//I could not find any information regarding the behaviour of min_elemnt on its arguments.
	return *std::max_element(tmp, endTmp);
}

MJArray MJArray::apply(double f(double)) const
{
	MJArray result(size());
	std::transform(ValuesPtr, EndPtr, result.ValuesPtr, f);

	return result;
}