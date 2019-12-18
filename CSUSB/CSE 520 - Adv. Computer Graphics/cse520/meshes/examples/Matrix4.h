//Matrix4.h : Base class for 1 X 4 and 4 x 1 matrix operations
#ifndef _MATRIX4_H
#define _MATRIX4_H
#include "Point3.h"
#include "Vector3.h"

using namespace std;

class Matrix4
{
  public:
    double m[4];   	//row or column elements
    Matrix4();
    Matrix4 ( double x, double y, double z, double w );
    Matrix4 ( const double a[3], double w );
    Matrix4 ( const double a[4] );
    Matrix4 ( const Point3 &p );
    Matrix4 ( const Vector3 &v );
    void set ( double x, double y, double z, double w );
    void set ( const double a[3], double w );
    void set ( const double a[4] );
    void get3 ( double a[3] );
    void get4 ( double a[4] );
    XYZ getXYZ();
    bool isVector3();  //does it represent a 3D vector or a point?
    Point3 getPoint3();
    Matrix4 operator + ( const Matrix4 &mat );
    Matrix4 operator - ( const Matrix4 &mat );
    Matrix4 operator * ( const double a );
};
#endif
