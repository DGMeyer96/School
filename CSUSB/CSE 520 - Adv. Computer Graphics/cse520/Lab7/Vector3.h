#ifndef VECTOR3_H
#define VECTOR3_H
#include "XYZ.h"

using namespace std;

class Point3;		//forward declaration

class Vector3: public XYZ 
{
  public:
    Vector3();
    Vector3( double x0, double y0, double z0 );  
    Vector3( double a[] );
    Vector3( const Vector3 &v );
    Vector3 operator + ( const Vector3 &v );	//vector + vector --> vector
    Vector3 operator - ( const Vector3 &v );    //vector - vector --> vector
    Vector3 operator ^ ( const Vector3 &v );	//cross product
    double  operator * ( const Vector3 &v );	//dot product
    Point3  operator + ( const Point3 &p );	//vector + point --> point
    double magnitude();
    void  normalize();				//make it a unit vector
};
    
Vector3 operator * ( double a, const Vector3 &v );		
Vector3 operator * ( const Vector3 &v, double a );		


//External C functions
void vector_cross( double c[3], double a[3], double b[3]);
void vector_normalize(double c[3]);

//Compute normal n of plane formed by three points a, b, c
void plane_normal( double n[3], double a[3], double b[3], double c[3]) ;
#endif
