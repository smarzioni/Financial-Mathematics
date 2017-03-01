#include <iostream>
#include <string>
#include <vector>
#include "Arrays.h"
#include "ArgumentList.h"
#pragma warning(disable : 4996)

using namespace std;

int main()
{
	vector<double> vec = { 0.5, 0.38 };
	MJArray mja(1);
	mja[0] = 89.3;
	ArgumentList Lista("Prova");
	string value = "valore";

	//add elements to Lista;
	Lista.add("stringa", value);
	Lista.add("Integer", -45);
	Lista.add("Integer2", 80);
	Lista.add("Float", 0.045);
	Lista.add("Bool", true);
	Lista.add("vector", vec);
	Lista.add("array", mja);
	ArgumentList Lista2("Contiene");
	Lista2.add("lista", Lista);


	//decleare empty variables
	int int1 = 0, int2 = 0;
	double floa = 0.0;
	string str1 ="";
	ArgumentList Lista3("teemp");
	//bool bol;
	//vector<double> vc2;
	//MJArray mja2;

	cout <<"\nIs Present 'stringa' " << Lista.isPresent("stringa");
	if(Lista.GetIfPresent("stringa", str1))
		cout << "\nstringa is present: e vale " << str1;
	if (Lista.GetIfPresent("integer", int1))
		cout << "\nInteger is present: e vale " << int1;
	cout << "\nInteger2 has value " << Lista.GetIntegerValue("integer2");
	if (Lista.GetIfPresent("float", floa))
		cout << "\nfloat is present: e vale " << floa;

	cout << "\n\nIs Present 'lista' " << Lista2.isPresent("lista");
	if (Lista2.GetIfPresent("lista", Lista3))
		cout << "\n lista is present: e si chiama " << Lista3.GetListName();

	cout << "\nIs Present 'stringa' " << Lista3.isPresent("stringa");
	if (Lista3.GetIfPresent("stringa", str1))
		cout << "\nstringa is present: e vale " << str1;
	if (Lista3.GetIfPresent("integer", int1))
		cout << "\nInteger is present: e vale " << int1;
	cout << "\nInteger2 has value " << Lista3.GetIntegerValue("integer2");
	if (Lista3.GetIfPresent("float", floa))
		cout << "\nfloat is present: e vale " << floa;

	cin >> int1;
	return 0;
}