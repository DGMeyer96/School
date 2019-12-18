// Matrix41.cpp

#include "Matrix41.h"
#include "Matrix14.h"
#include "Matrix44.h"
#include <math.h>

Matrix41::Matrix41():Matrix4()
{
}

Matrix41::Matrix41 (  double x, double y, double z, double w ):
	Matrix4 ( x, y, z, w )
{
}

Matrix41::Matrix41 (  const double a[3],  double w ):
	Matrix4 ( a, w )
{
}

Matrix41::Matrix41 ( const Point3 &p ):Matrix4 ( p )
{
}

Matrix41::Matrix41 ( const Vector3 &v ) : Matrix4 ( v )
{
}

Matrix14 Matrix41::transpose()
{
  Matrix14 mat14;

  for ( int i = 0; i < 4; i++ )
    mat14.m[i] = m[i];

  return mat14;
}

Matrix44 Matrix41::operator * ( const Matrix14 &mat14 )     //(4x1)(1x4) --> (4x4)
{
  Matrix44 mat44;
  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 4; j++ )
      mat44.m[i][j] = m[i] * mat14.m[j];

  return mat44;
}

void Matrix41::print()
{
  double a;

  for ( int i = 0; i < 4; i++ ) {
    a = m[i];
    if ( fabs ( a ) < 1e-12 ) a = 0;
    cout << "\n( " << a << " )";
  }
  cout  << endl;
}

