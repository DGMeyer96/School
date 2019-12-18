//Vector3.cpp : Vector3 class functions and external functions operating on Vector3

#include <math.h>
#include "Vector3.h"
#include "Point3.h"

Vector3::Vector3():XYZ()
{
}

Vector3::Vector3( double a[] ):XYZ( a )
{
}

Vector3::Vector3( double x0, double y0, double z0 ): XYZ( x0, y0, z0 )
{
}

Vector3::Vector3( const Vector3 &v )
{
  x = v.x;
  y = v.y;
  z = v.z;
}

Vector3 Vector3::operator + ( const Vector3 &v )
{
  Vector3 v1;
  v1.x = x + v.x;
  v1.y = y + v.y;
  v1.z = z + v.z;

  return v1;
}

Vector3 Vector3::operator - ( const Vector3 &v )
{
  Vector3 v1;
  v1.x = x - v.x;
  v1.y = y - v.y;
  v1.z = z - v.z;

  return v1;
}

//cross product
Vector3 Vector3::operator ^ ( const Vector3 &v )
{
  Vector3 v1;
  v1.x = y * v.z - z * v.y;
  v1.y = z * v.x - x * v.z;
  v1.z = x * v.y - y * v.x;

  return v1; 
}

//dot product
double Vector3::operator * ( const Vector3 &v )
{
  double d;
  d = x * v.x + y * v.y + z * v.z;

  return d;
}

//vector + point --> point
Point3 Vector3::operator + ( const Point3 &p )
{
  Point3 p1;

  p1.x = x + p.x;
  p1.y = y + p.y;
  p1.z = z + p.z;

  return p1;
}

double Vector3::magnitude()
{
  return sqrt(x * x + y * y + z * z );
}

void Vector3::normalize()
{
  double d = x*x + y*y + z*z;

  if ( d > 0 ) {
    d = sqrt ( d );
    x /= d;
    y /= d;
    z /= d;
  }
}

//------------------- external functions ---------------

//scalar times vector
Vector3 operator * ( double a, const Vector3 &v )
{
  Vector3 v1;
  v1.x = a * v.x;
  v1.y = a * v.y;
  v1.z = a * v.z;

  return v1;
}

Vector3 operator * ( const Vector3 &v, double a )
{
  return a * v;
}

void vector_normalize(double c[3]) 
{
    double l, m;

    l = (double)sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
    if ( fabs( (float) l) < 1.0e-10) {
        if ((c[0] >= c[1]) && (c[0] >= c[2])) {
            c[0] = 1.0;
            c[1] = c[2] = 0.0;
        } else
            if (c[1] >= c[2]) {
                c[1] = 1.0;
                c[0] = c[2] = 0.0;
            } else {
                c[2] = 1.0;
                c[0] = c[1] = 0.0;
            }
    } else {
        m = 1.0 / l;
        c[0] *= m;
        c[1] *= m;
        c[2] *= m;
    }
}

void vector_cross( double c[3], double a[3], double b[3]) 
{
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

/*
 *  Compute unit normal n of plane formed by three points a, b, c
 */
void plane_normal ( double n[3], double a[3], double b[3], double c[3])
{
    double u[3], v[3];

    //difference between two points is a vector
    for ( int i = 0; i < 3; i++ ) {
      u[i] = c[i] - b[i];
      v[i] = a[i] - b[i]; 
    }
    vector_cross ( n, u, v );
    vector_normalize ( n );
}

