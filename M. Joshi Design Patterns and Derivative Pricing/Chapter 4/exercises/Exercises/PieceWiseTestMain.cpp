
//Just to test Piecewise Parameters integrals

#include <iostream>
#include "PiecewiseParameters.h"
using namespace std;

int main()
{
	int intervals;
	vector<double> times;
	vector<double> constants;
	double temp;
	double t1, t2;

	cout << "Type the number of pieces \n";
	cin >> intervals;


	cout << "\nInsert the starting point of the first piece\n";
	cin >> temp;
	times.push_back(temp);


	for (int i = 0; i < intervals; i++)
	{
		cout << "\nInsert the constant value in this piece: \n";
		cin >> temp;
		constants.push_back(temp);

		cout << "\nInsert the starting point of the next piece: \n";
		cin >> temp;
		times.push_back(temp);
	}

	ParametersPieceWise thePWfunction(constants, times);

	cout << "\nInsert integration exteremes \n" << "t1: ";
	cin >> t1;
	cout << "t2: ";
	cin >> t2;

	cout << "\nThe integrations result in \n";
	cout << "Integral: " << thePWfunction.Integral(t1, t2);
	cout << "\nIntegral Squares: " << thePWfunction.IntegralSquare(t1, t2);

	cout << "\nType a number and press enter to quit\n";
	cin >> temp;

	return 0;
}