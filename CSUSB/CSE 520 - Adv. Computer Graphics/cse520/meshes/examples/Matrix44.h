//Matrix44.h : Class defines 4 X 4 matrix operations
#ifndef _MATRIX44_H
#define _MATRIX44_H
#include "Matrix4.h"

using namespace std;
class Matrix14;
class Matrix41;

class Matrix44
{
  public:
    double m[4][4];   	//4 x 4 array
    Matrix44();
    Matrix44 ( const double mat44[4][4] );
    Matrix44 ( const double *a );
    Matrix44 ( const Matrix14 &r0, const Matrix14 &r1, const Matrix14 &r2, const Matrix14 &r3 );  
    Matrix44 ( const Matrix41 &c0, const Matrix41 &c1, const Matrix41 &c2, const Matrix41 &c3 );  
    void set ( const double mat44[4][4] );
    void set ( const double *a );
    bool setCol ( int nCol, const double a[] );  //set one column
    bool setCol ( int nCol, double a0, double a1, double a2, double a3 );  //set one column
    bool setRow ( int nRow, const double a[] );  //set one row
    bool setRow ( int nRow, double a0, double a1, double a2, double a3 );  //set one row
    void get ( double *a );
    Matrix44 transpose();
    Matrix44 operator + ( const Matrix44 &mat );
    Matrix44 operator - ( const Matrix44 &mat );
    Matrix44 operator * ( const double d );
    Matrix41 operator * ( const Matrix41 &mat );  // (4x4)(4x1) --> (4x1)
    Matrix44 operator * ( const Matrix44 &mat );  //(4x4)(4x4) --> (4x4) 
    void print();
    double determinant();
    Matrix44 inverse();
};
#endif
