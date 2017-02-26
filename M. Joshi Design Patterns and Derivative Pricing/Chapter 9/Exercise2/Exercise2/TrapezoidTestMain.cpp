
#include "Trapezoid.h"
#include <iostream>
#include <cmath>
//This script test the trapezoid integration inside Trapezoid.h


using namespace std;

class TestFunction
{
public:
	TestFunction() {}
	inline double operator() (double x) const;
};

inline double TestFunction::operator() (double x) const
{
	return x*x;
}

int main()
{
	TestFunction f;
	for(int n = 0; n < 15; n++)
		cout << endl << n << " : " << Trapezoid<TestFunction>(f, 0, 1, n) << endl;

	double temp;
	cin >> temp;
}