//Matrix41.h : Class defines 4 X 1 matrix operations
#ifndef _MATRIX41_H
#define _MATRIX41_H
#include "Matrix4.h"

using namespace std;
class Matrix14;
class Matrix44;

class Matrix41 : public Matrix4
{
  public:
    Matrix41();
    Matrix41 ( double x, double y, double z, double w );
    Matrix41 ( const double a[3], double w );
    Matrix41 ( const Point3 &p );
    Matrix41 ( const Vector3 &v );
    Matrix14 transpose(); 
    Matrix44 operator * ( const Matrix14 &mat );  //(4x1)(1x4) --> (4x4) 
    void print();
};
#endif
