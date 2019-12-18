//Point3.cpp : class Point3 member functions

#include "Point3.h"
#include "Vector3.h"

Point3::Point3():XYZ()
{
}

Point3::Point3( double x0, double y0, double z0 ): XYZ( x0, y0, z0 )
{
}

Point3::Point3( double a[] ): XYZ ( a )
{
}

Point3::Point3( const Point3 &p )
{
  x = p.x;
  y = p.y;
  z = p.z;
}

Vector3 Point3::operator - ( const Point3 &p )
{
  Vector3 v1;

  v1.x = x - p.x;
  v1.y = y - p.y;
  v1.z = z - p.z;

  return v1;
}

Point3 Point3::operator + ( const Vector3 &v )
{
  Point3 p1;

  p1.x = x + v.x;
  p1.y = y + v.y;
  p1.z = z + v.z;

  return p1;
}
