#include "XYZ.h"

XYZ::XYZ()
{
  x = y = z = 0;
}

XYZ::XYZ( double x0, double y0, double z0 )
{
  x = x0;  y = y0;  z = z0;
}

XYZ::XYZ( double a[] )
{
  x = a[0];  y = a[1];  z = a[2];
}

void XYZ::set( double x0, double y0, double z0 )
{
  x = x0;  y = y0;  z = z0;
}

/*
XYZ &XYZ::getXYZ( XYZ &xyz )
{
  xyz.set ( x, y, z );
  
  return xyz;
}
*/

XYZ XYZ::getXYZ()
{
  XYZ a( x, y, z );
  
  return a;
}

void XYZ::getXYZ( double a[] )
{
  a[0] = x;
  a[1] = y;
  a[2] = z;
}

void XYZ::print()
{
  cout << "(" << x <<", " << y << ", " << z << ")" << endl;
}
