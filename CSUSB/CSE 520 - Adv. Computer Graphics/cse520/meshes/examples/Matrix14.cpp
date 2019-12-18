// Matrix14.cpp

#include "Matrix14.h"
#include "Matrix41.h"
#include "Matrix44.h"
#include <iostream>
#include <math.h>

Matrix14::Matrix14():Matrix4()
{
}

Matrix14::Matrix14 (  double x, double y, double z, double w ):
	Matrix4 ( x, y, z, w )
{
}

Matrix14::Matrix14 ( const Point3 &p ):Matrix4 ( p )
{
}

Matrix14::Matrix14 ( const Vector3 &v ) : Matrix4 ( v )
{
}

Matrix41 Matrix14::transpose()
{
  Matrix41 mat41;

  for ( int i = 0; i < 4; i++ )
    mat41.m[i] = m[i];

  return mat41;
}

double Matrix14::operator * ( const Matrix41 &mat )     //(1x4)(4x1) --> (1x1)
{
  double d = 0;
  for ( int i = 0; i < 4; i++ )
    d += m[i] * mat.m[i];

  return d;
}

Matrix14 Matrix14::operator * ( const Matrix44 &mat )  //(1x4)(4x4) --> (1x4)
{
  Matrix14 mat14;    //elements initialize to 0

  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 4; j++ )
      mat14.m[i] += m[j] * mat.m[j][i]; 

  return mat14;
}

void Matrix14::print()
{

  double a; 
  cout << "\n( ";
  for ( int i = 0; i < 3; i++ ) {
    a = m[i];
    if ( fabs ( a ) < 1e-12 ) a = 0;
    cout << a <<  ", ";
  }
  a = m[3];
  if ( fabs ( a ) < 1e-12 ) a = 0;
  cout << a << " )" << endl;
}
