#ifndef WRAPPER_H
#define WRAPPER_H
// This is a tempalte for a Wrapper class. The Wrapper behaves like a pinter T* BUT
// it owns the object pointed. So copy a wrapper creates a new copy of the object and
// the deletion of the pointed object is full responasability of the Wrapper.
//The class T is required to have a method clone();
template<class T>
class Wrapper
{
public:
	Wrapper()
	{
		DataPtr = 0;
	}

	Wrapper(const T& inner)
	{
		DataPtr = inner.clone();
	}
	
	~Wrapper()
	{
		if (DataPtr != 0)
			delete DataPtr;
	}

	Wrapper(const Wrapper<T>& original)
	{
		if (original.DataPtr != 0)
			DataPtr = original.DataPtr->clone();
		else
			DataPtr = 0;
	}

	Wrapper& operator=(const Wrapper<T>& original)
	{
		if (this != &original)
		{
			if (DataPtr != 0)
				delete DataPtr;
			
			DataPtr = (original.DataPtr != 0) ?
				original.DataPtr->clone() : 0;
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
};
#endif // !WRAPPER_H
