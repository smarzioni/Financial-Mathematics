#ifndef COUNTED_WRAPPER_H
#define COUNTED_WRAPPER_H
//EXERCISE 5.6 of Joshi's book.
//The class T is required to have a method clone();
template<class T>
class CountedWrapper
{
public:
	Wrapper()  //FATTA
	{
		DataPtr = 0;
		*CountPtr= 0;
	}

	Wrapper(const T& inner) //FATTA
	{
		DataPtr = inner.clone();
		*CountPtr = 1;
	}

	~Wrapper()
	{
		if (DataPtr != 0) DecreaseCounter();
	}

	unsigned long GetCounter() //FATTA
	{
		return *CountPtr;
	}

	void IncreaseCounter()   //FATTA
	{
		(*CountPtr)++;
	}

	void DecreaseCounter()
	{
		if (DataPtr != 0)
		{
			(*CountPtr)--;
			if (*CountPtr <= 0) 
			{
				delete DataPtr;
			}
		}
		else *CountPtr = 0;
	}

	Wrapper(const Wrapper<T>& original) // FATTA
	{
		if (original.DataPtr != 0)
		{
			DataPtr = original.DataPtr;
			original.IncreaseCounter();
			CountPtr = original.CountPtr;
		}
		else
		{
			DataPtr = 0;
			counter = 0;
		}
	}

	Wrapper& operator=(const Wrapper<T>& original)
	{
		if (this != &original)
		{
			if (DataPtr != 0)
			{
				DecreaseCounter();
			}

			DataPtr = (original.DataPtr != 0) ?
				original.DataPtr : 0;
			CountPtr = (original.DataPtr != 0) ?
				original.CountPtr : 0;

			IncreaseCounter();
		}

		return *this;
	}

	T& operator*()
	{
		return *DataPtr;
	}

	const T& operator*() const
	{
		return *DataPtr;
	}

	const T* const operator->() const
	{
		return DataPtr;
	}

	T* operator->()
	{
		return DataPtr;
	}
private:
	T* DataPtr;
	unsigned long* CountPtr;
};
#endif // !WRAPPER_H

