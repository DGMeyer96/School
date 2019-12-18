#include <iostream>

using namespace std;

void dotProduct(int a[], int b[])
{
	cout << "A.B = ";
	//cout << "(Ax * Bx) + (Ay * By) + (Az * Bz) = " << endl;
	cout << (a[0] * b[0]) << " + " << (a[1] * b[1]) << " + " << (a[2] * b[2]) << " = ";

	cout << " " << (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]) << endl;
}

void crossProduct(int a[], int b[])
{
	cout << "A X B = ";
	cout << (a[1] * b[2] - a[2] * b[1]) << "i + " << (a[2] * b[0] - a[0] * b[2]) << "j + " << (a[0] * b[1] - a[1] * b[0]) << "k" << endl;

	cout << "B X A = ";
	cout << (b[1] * a[2] - b[2] * a[1]) << "i + " << (b[2] * a[0] - b[0] * a[2]) << "j + " << (b[0] * a[1] - b[1] * a[0]) << "k" << endl;
}

void findNormal(int p1[], int p2[], int p3[])
{
	cout << "The normal to the plane through the points: " << endl;
	cout << "( " << p1[0] << ", " << p1[1] << ", " << p1[2] << " ) ";
	cout << "( " << p2[0] << ", " << p2[1] << ", " << p2[2] << " ) ";
	cout << "( " << p3[0] << ", " << p3[1] << ", " << p3[2] << " ) " << endl;

	cout << "A = p2 - p1 = ( " << (p2[0] - p1[0]) << ", " << (p2[1] - p1[1]) << ", " << (p2[2] - p1[2]) << " )" << endl;
	int a[3] = { p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2] };
	cout << "B = p3 - p1 = ( " << (p3[0] - p1[0]) << ", " << (p3[1] - p1[1]) << ", " << (p3[2] - p1[2]) << " )" << endl;
	int b[3] = { p3[0] - p1[0], p3[1] - p1[1], p3[2] - p1[2] };

	cout << "N = A X B = ";
	cout << (a[1] * b[2] - a[2] * b[1]) << "i + " << (a[2] * b[0] - a[0] * b[2]) << "j + " << (a[0] * b[1] - a[1] * b[0]) << "k" << endl;
}

int main()
{
	int a[3] = { 3, 0, 2 };
	int b[3] = { 4, 1, 8 };

	int p1[3] = { 1, 1, 1 };
	int p2[3] = { 1, 2, 1 };
	int p3[3] = { 3, 0, 4 };

	crossProduct(a, b);
	dotProduct(a, b);
	findNormal(p1, p2, p3);

	

	return 0;
}