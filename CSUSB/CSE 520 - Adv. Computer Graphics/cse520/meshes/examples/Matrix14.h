//Matrix14.h : Class defines 1 X 4 matrix operations
#ifndef _MATRIX14_H
#define _MATRIX14_H
#include "Matrix4.h"

using namespace std;
class Matrix41;
class Matrix44;

class Matrix14: public Matrix4
{
  public:
    Matrix14();
    Matrix14 ( double x, double y, double z, double w );
    Matrix14 ( const Point3 &p );
    Matrix14 ( const Vector3 &v );
    Matrix41 transpose();
    double operator * ( const Matrix41 &mat );     //(1x4)(4x1) --> (1x1)
    Matrix14 operator * ( const Matrix44 &mat );   //(1x4)(4x4) --> (1x4) 
    void print();   //print row matrix
};
#endif
