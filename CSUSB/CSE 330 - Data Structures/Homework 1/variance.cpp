/*****************************************************************
*Daniel Meyer
*variance.cpp
*10/4/17
*Homework 1
*Problem 8, Page 21
*CSE 330
*Fall 2017
*****************************************************************/

#include <iostream>
#include <math.h>

using namespace std;

float average(float float_array[], int size);
float variance(float float_array[], int size);

int main()
{
	float float_array[100];
	int size = 0;

	while (!cin.eof())
	{
		cin >> float_array[size];
		size++;
	}

	if (size > 0 && size < 100)
		cout << variance(float_array, size);

        cout << endl;

	return 0;
}

float average(float float_array[], int size)
{
	float sum = 0;

	for (int i = 0; i < size; i++) {
		sum += float_array[i];
	}

	return sum / size;
}

float variance(float float_array[], int size)
{
	float sum = 0;
	float variance;
	float avg = average(float_array, size);

	for (int i = 0; i < size; i++) {
		sum += pow((float_array[i] - avg), 2.0);
	}

	return variance = sum / (size - 1);
}
