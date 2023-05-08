#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "myUpdatedMatrixClass.h"

using namespace std;

int main()
{
	Matrix2D intMatrix1;
	Matrix2D intMatrix2;

	string fileName1, fileName2;

	cin >> fileName1 >> fileName2;

	ifstream file;
	file.open(fileName1.c_str());
    if (!file.is_open())
	{
		cout << "File not found." << endl;
		return 0;
	}
	file >> intMatrix1;
	file.clear();
	file.close();

	file.open(fileName2.c_str());
	if (!file.is_open())
	{
		cout << "File not found." << endl;
		return 0;
	}
	file >> intMatrix2;
	file.clear();
	file.close();

	cout << intMatrix1 + intMatrix2 << endl;

	cout << endl;
	intMatrix1 += intMatrix2;

	cout << intMatrix1 << endl;

	Matrix2D newOne = intMatrix2 + intMatrix1;

	cout << newOne << endl;

	intMatrix1 = newOne;
	
	if (!intMatrix1.isEmpty())
		intMatrix1.SetIndex(0, 0, 10000);

	cout << intMatrix1 << endl;

	if (!intMatrix1.isEmpty())
		cout << newOne.GetIndex(0, 0) << endl;

	return 0;
}
