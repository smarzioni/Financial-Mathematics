#include "Arrays.h"
#include <iostream>


int main()
{
	MJArray a(3);
	a[0] = 2;
	a[1] = 3;
	a[2] = 8;

	std::cout << "\n" << a.prod() << "\n";

	std::cin >> a[0];

}