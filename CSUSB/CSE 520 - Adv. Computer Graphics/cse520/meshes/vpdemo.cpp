//vpdemo:   Program demonstrating vector and point operations

#include <iostream>
#include "Vector3.h"
#include "Point3.h"

using namespace std;

int main()
{
  Vector3 v1 ( 1.0, 2.0, 4.0 );  //a vector
  XYZ a;		//an XYZ object
  a = v1.getXYZ ();	//get XYZ object of v1
  cout << "v1 = "; 
  v1.print();		//prints  (x, y, z) values
  Vector3 v2 ( 2.0, 4.0,  6.0 );
  cout << "v2 = ";
  v2.print();		//prints (x, y, z) values of v2
  Vector3 v3 ( v2 );	//contruct v2 from v2
  v3.normalize();	//normalize v3
  cout << "v3 = ";
  v3.print();		//now v3 is a unit vector
  cout << "magnitude of v3 is ";
  cout << v3.magnitude() << endl;	//magnitude should be 1
  
  Vector3 v4 = v2 + v1;	//addition of two vectors
  cout << "v2 + v1 = ";
  v4.print();
  Vector3 v5 = v2 - v1; //subtraction of two vectors
  cout << "v2 - v1 = ";
  v5.print();
  Vector3 v6 = v1 ^ v2;
  cout << "v1 X v2 = ";
  v6.print();
  double d = v1 * v2;
  cout << "Dot product of v1 and v2 is " << d << endl;
  Vector3 v7 = 3 * v1;
  cout << " 3 * v1 = ";
  v7.print();

  Point3 p1 ( 0.0, 1.0, 2.0 );
  cout << "Point p1 = ";
  p1.print();
  Point3 p2 = v1 + p1;
  cout << "v1 + p1 is the point ";
  p2.print();

  return 0;
}
