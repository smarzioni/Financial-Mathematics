#include <iostream>
#include "Halton.h"
#include "BaseChanges.h"
#include <vector>

using namespace std;

int main() {
	Halton generator(1, 1);

	vector<double> points(100);

	for (int l = 0; l < 100; l++)
	{
		points[l] = (generator.GetNextHaltonPoints(1))[0][0];
	}

	for (int i = 0; i < 100; i++)
	{
		cout << points[i] << endl;
	}
	/*
	int x = 15;
	vector<unsigned int> digits = BaseExpansion(x, 2);
	for (int i = 0; i < digits.size(); i++)
	{
		cout << " " << digits[i];
	}
	cout << endl;

	cout << DecimalInteger(digits, 2) << endl;

	vector<unsigned int> digitsSucc = NextBaseExpansion(digits, 2);
	for (int i = 0; i < digits.size(); i++)
	{
		cout << " " << digitsSucc[i];
	}
	cout << endl;

	cout << DecimalInteger(digitsSucc, 2) << endl;

	cout << "Van der Corput\n";
	cout << x << ": " << VanDerCorput(digits, 2) << endl;
	cout << x + 1  << ": " << VanDerCorput(digitsSucc, 2) << endl;
	*/
	int temp;
	cin >> temp;
}