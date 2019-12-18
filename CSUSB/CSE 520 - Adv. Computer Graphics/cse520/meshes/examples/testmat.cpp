// testmat.cpp :  Sample program for testing Matrix class functions

#include "Matrix4.h"
#include "Matrix14.h"
#include "Matrix41.h"
#include "Matrix44.h"
#include <iostream>

int main()
{
  Matrix14 mat14;
  mat14.print();
  double a[] = {1, 2, 3, 4};
  mat14.set ( a ); 
  mat14.print();
  mat14.set ( 4, 3, 2, 1 ); 
  mat14.print();

  Matrix41 mat41;
  mat41.print();
  double b[] = {1, 2, 3, 4};
  mat41.set ( b ); 
  mat41.print();
  mat41.set ( 0.5, 1.0/3, 0.5, 1 ); 
  mat41.print();

  double d = mat14 * mat41;
  cout << "d = " << d << endl;
  Matrix44 mat44;
  mat44.print();
  //double a44[4][4] = { {2, 3, 0, 0}, {1, 4, 0, 0}, {0, 0, 3, 4}, {0, 0, 5, 6} };
  double a44[4][4] = { {2, 3, 0, 0}, {1, 4, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} };
  mat44.set ( &a44[0][0] );
  mat44.print();
  cout << "determinant=" << mat44.determinant();
  Matrix44 mi = mat44.inverse();
  mi.print();
  Matrix44 mp = mat44 * mi;
  mp.print();
  cout << "-------------";
  Matrix14 r0 (1, 2, 3, 4);
  Matrix14 r1 (4, 3, 2, 1);
  Matrix14 r2 (5, 6, 7, 8);
  Matrix14 r3 (8, 7, 6, 5);

  Matrix44 m44 ( r0, r1, r2, r3 );
  m44.print();
  Matrix41 c0 (1, 2, 3, 4);
  Matrix41 c1 (4, 3, 2, 1);
  Matrix41 c2 (5, 6, 7, 8);
  Matrix41 c3 (8, 7, 6, 5);

  Matrix44 mc44 ( c0, c1, c2, c3 );
  mc44.print();
  return 0;
}
