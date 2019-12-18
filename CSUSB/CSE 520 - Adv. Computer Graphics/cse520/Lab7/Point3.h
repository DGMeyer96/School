#ifndef POINT3_H
#define POINT3_H
#include "XYZ.h"

using namespace std;

class Vector3;		//forward declaration

class Point3: public XYZ 
{
  public:
    Point3();
    Point3( double x0, double y0, double z0 ); 
    Point3( double p[] );  
    Point3( const Point3 &p);
    Vector3 operator - ( const Point3 &p );    //point - point --> vector
    Point3  operator + ( const Vector3 &v );	//point + vector --> point
};
    
#endif

