// Matrix4.cpp

#include "Matrix4.h"

Matrix4::Matrix4()
{
  m[0] = m[1] = m[2] = m[3] = 0.0;
}

Matrix4::Matrix4 (  double x, double y, double z, double w )
{
  m[0] = x;  m[1] = y;  m[2] = z;  m[3] = w;
}

Matrix4::Matrix4 (  const double a[3], double w )
{
  for ( int i = 0; i < 3; i++ )
    m[i] = a[i];
  m[3] = w;
}

Matrix4::Matrix4 ( const Point3 &p )
{
  m[0] = p.x;  m[1] = p.y;  m[2] = p.z;
  m[3] = 1;	
}

Matrix4::Matrix4 ( const Vector3 &v )
{
  m[0] = v.x;  m[1] = v.y;  m[2] = v.z;
  m[3] = 0;
}

void Matrix4::set ( double x, double y, double z, double w )
{
  m[0] = x;  m[1] = y;  m[2] = z;  m[3] = w;
}

void Matrix4::set (  const double a[3], double w )
{
  for ( int i = 0; i < 3; i++ )
    m[i] = a[i];
  m[3] = w;
}

void Matrix4::set ( const double a[4] )
{
  for ( int i = 0; i < 4; i++ )
    m[i] = a[i];
}

void Matrix4::get3 ( double a[3] )
{
  for ( int i = 0; i < 3; i++ )
    a[i] = m[i];
}

void Matrix4::get4 ( double a[4] )
{
  for ( int i = 0; i < 4; i++ )
    a[i] = m[i];
}

XYZ Matrix4::getXYZ()
{
   XYZ xyz (m[0], m[1], m[2]);

   return xyz;
}

bool Matrix4::isVector3()
{
  if ( m[3] == 0 )
    return true;
  else
    return false;
}

//Get 3D point (x/w, y/w, z/w)
Point3 Matrix4::getPoint3()
{
   Point3 p(9999, 9999, 9999);
   if ( !isVector3() ){
     p.set ( m[0] / m[3], m[1] / m[3], m[2] / m[3] ); 
   }
   return p;
}

Matrix4 Matrix4::operator + ( const Matrix4 &mat )
{
  Matrix4 a;

  for ( int i = 0; i < 4; i++ )
    a.m[i] = m[i] + mat.m[i];

  return a;
}

Matrix4 Matrix4::operator - ( const Matrix4 &mat )
{
  Matrix4 a;

  for ( int i = 0; i < 4; i++ )
    a.m[i] = m[i] - mat.m[i];

  return a;
}

Matrix4 Matrix4::operator * ( const double d )
{
  Matrix4 a;

  for ( int i = 0; i < 4; i++ )
    a.m[i] = m[i] * d;

  return a; 
}

