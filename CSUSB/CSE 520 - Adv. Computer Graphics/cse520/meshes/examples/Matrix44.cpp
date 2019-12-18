// Matrix44.cpp

#include <iostream>
#include <math.h>
#include "Matrix44.h"
#include "Matrix14.h"
#include "Matrix41.h"

Matrix44::Matrix44()
{
  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 4; j++ )
      m[i][j] = 0;
}

Matrix44::Matrix44 (  const double a[4][4] )
{
  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 4; j++ )
      m[i][j] = a[i][j];
}

Matrix44::Matrix44 ( const double *a )
{
  int k = 0;
  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 4; j++ )
      m[i][j] = a[k++];
}

Matrix44::Matrix44 ( const Matrix14 &r0, const Matrix14 &r1, const Matrix14 &r2, const Matrix14 &r3 )
{
  for ( int j = 0; j < 4; j++ )
    m[0][j] = r0.m[j];
  for ( int j = 0; j < 4; j++ )
    m[1][j] = r1.m[j];
  for ( int j = 0; j < 4; j++ )
    m[2][j] = r2.m[j];
  for ( int j = 0; j < 4; j++ )
    m[3][j] = r3.m[j];
}
   
Matrix44::Matrix44 ( const Matrix41 &c0, const Matrix41 &c1, const Matrix41 &c2, const Matrix41 &c3 )
{
  for ( int i = 0; i < 4; i++ )
    m[i][0] = c0.m[i];
  for ( int i = 0; i < 4; i++ )
    m[i][1] = c1.m[i];
  for ( int i = 0; i < 4; i++ )
    m[i][2] = c2.m[i];
  for ( int i = 0; i < 4; i++ )
    m[i][3] = c3.m[i];
}


//void Matrix44::set ( const double a[4][4] )
void Matrix44::set ( const double *a )
{
  int k = 0;
  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 4; j++ )
      m[i][j] = a[k++];
}

void Matrix44::set (  const double a[4][4] )
{
  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 4; j++ )
      m[i][j] = a[i][j];
}

//set column j
bool Matrix44::setCol ( int j, double a0, double a1, double a2, double a3 )  
{
   if ( j < 0 || j > 3 ) return false;
   
   m[0][j] = a0;
   m[1][j] = a1;
   m[2][j] = a2;
   m[3][j] = a3;

   return true;
}

//set column j, 0 <= j <=3
bool Matrix44::setCol ( int j, const double a[] )
{
   if ( j < 0 || j > 3 ) return false;

   for ( int i = 0; i < 4; i++ )
      m[i][j] = a[i];

   return true;
}

//set Row i
bool Matrix44::setRow ( int i, double a0, double a1, double a2, double a3 )  
{
   if ( i < 0 || i > 3 ) return false;
   
   m[i][0] = a0;
   m[i][1] = a1;
   m[i][2] = a2;
   m[i][3] = a3;

   return true;
}

//set row i, 0 <= i <=3
bool Matrix44::setRow ( int i, const double a[] )
{
   if ( i < 0 || i > 3 ) return false;

   for ( int j = 0; j < 4; j++ )
      m[i][j] = a[j];

   return true;
}

void Matrix44::get ( double *a )
{
  int k = 0;
  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 4; j++ )
      a[k++] = m[i][j];
}

Matrix44 Matrix44::transpose()
{
  Matrix44 mat44;

  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 4; j++ )
      mat44.m[i][j] = m[j][i];
  
  return mat44;
}

Matrix44 Matrix44::operator + ( const Matrix44 &mat )
{
  Matrix44 mat44;

  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 4; j++ )
      mat44.m[i][j] = m[i][j] + mat.m[i][j];

  return mat44;
}

Matrix44 Matrix44::operator - ( const Matrix44 &mat )
{
  Matrix44 mat44;

  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 4; j++ )
      mat44.m[i][j] = m[i][j] - mat.m[i][j];

  return mat44;
}

Matrix44 Matrix44::operator * ( const double a )
{
  Matrix44 mat44;

  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 4; j++ )
      mat44.m[i][j] = a * m[i][j];

  return mat44; 
}

Matrix41 Matrix44::operator * ( const Matrix41 &mat )     //(4x4)(4x1) --> (4x1)
{
  Matrix41 mat41;

  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 4; j++ )
      mat41.m[i] += m[i][j] * mat.m[j];

  return mat41; 
}

Matrix44 Matrix44::operator * ( const Matrix44 &mat )  //(4x4)(4x4) --> (4x4)
{
  Matrix44 mat44;    //elements initialize to 0

  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 4; j++ )
      for ( int k = 0; k < 4; k++ )
        mat44.m[i][j] += m[i][k] * mat.m[k][j]; 

  return mat44;
}

void Matrix44::print()
{

  double a;

  for ( int i = 0; i < 4; i++ ){
    cout << "\n( ";
    for ( int j = 0; j < 4; j++ ){
       a = m[i][j];
       if ( fabs ( a ) < 1e-12 ) a = 0;
       cout << a;
       if ( j < 3 )
	 cout << ", ";
       else
	 cout << " )" ;
   }    
  }
  cout << endl;
}

//calculate determinant using Cramer's Rule
//Code adopted from "http://download.intel.com/design/PentiumIII/sml/24504301.pdf"
double Matrix44::determinant()
{
 // Matrix44 mt;

  double tmp[12];    	//temp array for pairs
  double src[16];	//array of transpose
  double dst[4];
  double det;		//determinant
 // mt = transpose();	//transpose matrix
  get ( src );


  // calculate pairs for first 8 elements (cofactors) 
  tmp[0] = src[10] * src[15];
  tmp[1] = src[11] * src[14];
  tmp[2] = src[9] * src[15];
  tmp[3] = src[11] * src[13];
  tmp[4] = src[9] * src[14];
  tmp[5] = src[10] * src[13];
  tmp[6] = src[8] * src[15];
  tmp[7] = src[11] * src[12];
  tmp[8] = src[8] * src[14];
  tmp[9] = src[10] * src[12];
  tmp[10] = src[8] * src[13];
  tmp[11] = src[9] * src[12];

  // calculate first 8 elements (cofactors) 
  dst[0] = tmp[0]*src[5] + tmp[3]*src[6] + tmp[4]*src[7];
  dst[0] -= tmp[1]*src[5] + tmp[2]*src[6] + tmp[5]*src[7];
  dst[1] = tmp[1]*src[4] + tmp[6]*src[6] + tmp[9]*src[7];
  dst[1] -= tmp[0]*src[4] + tmp[7]*src[6] + tmp[8]*src[7];
  dst[2] = tmp[2]*src[4] + tmp[7]*src[5] + tmp[10]*src[7];
  dst[2] -= tmp[3]*src[4] + tmp[6]*src[5] + tmp[11]*src[7];
  dst[3] = tmp[5]*src[4] + tmp[8]*src[5] + tmp[11]*src[6];
  dst[3] -= tmp[4]*src[4] + tmp[9]*src[5] + tmp[10]*src[6];

  // calculate determinant 
  det=src[0]*dst[0]+src[1]*dst[1]+src[2]*dst[2]+src[3]*dst[3];
  
  return det;            //return determinant
}

//inverse using Cramer's Rule
//Code adopted from "http://download.intel.com/design/PentiumIII/sml/24504301.pdf"
Matrix44 Matrix44::inverse()
{
  Matrix44 mi;
  Matrix44 mt;

  double tmp[12];    	//temp array for pairs
  double src[16];	//array of transpose
  double dst[16];
  double det;		//determinant
  mt = transpose();	//transpose matrix
  mt.get ( src );

  // calculate pairs for first 8 elements (cofactors) 
  tmp[0] = src[10] * src[15];
  tmp[1] = src[11] * src[14];
  tmp[2] = src[9] * src[15];
  tmp[3] = src[11] * src[13];
  tmp[4] = src[9] * src[14];
  tmp[5] = src[10] * src[13];
  tmp[6] = src[8] * src[15];
  tmp[7] = src[11] * src[12];
  tmp[8] = src[8] * src[14];
  tmp[9] = src[10] * src[12];
  tmp[10] = src[8] * src[13];
  tmp[11] = src[9] * src[12];

  // calculate first 8 elements (cofactors) 
  dst[0] = tmp[0]*src[5] + tmp[3]*src[6] + tmp[4]*src[7];
  dst[0] -= tmp[1]*src[5] + tmp[2]*src[6] + tmp[5]*src[7];
  dst[1] = tmp[1]*src[4] + tmp[6]*src[6] + tmp[9]*src[7];
  dst[1] -= tmp[0]*src[4] + tmp[7]*src[6] + tmp[8]*src[7];
  dst[2] = tmp[2]*src[4] + tmp[7]*src[5] + tmp[10]*src[7];
  dst[2] -= tmp[3]*src[4] + tmp[6]*src[5] + tmp[11]*src[7];
  dst[3] = tmp[5]*src[4] + tmp[8]*src[5] + tmp[11]*src[6];
  dst[3] -= tmp[4]*src[4] + tmp[9]*src[5] + tmp[10]*src[6];
  dst[4] = tmp[1]*src[1] + tmp[2]*src[2] + tmp[5]*src[3];
  dst[4] -= tmp[0]*src[1] + tmp[3]*src[2] + tmp[4]*src[3];
  dst[5] = tmp[0]*src[0] + tmp[7]*src[2] + tmp[8]*src[3];
  dst[5] -= tmp[1]*src[0] + tmp[6]*src[2] + tmp[9]*src[3];
  dst[6] = tmp[3]*src[0] + tmp[6]*src[1] + tmp[11]*src[3];
  dst[6] -= tmp[2]*src[0] + tmp[7]*src[1] + tmp[10]*src[3];
  dst[7] = tmp[4]*src[0] + tmp[9]*src[1] + tmp[10]*src[2];
  dst[7] -= tmp[5]*src[0] + tmp[8]*src[1] + tmp[11]*src[2];

  // calculate pairs for second 8 elements (cofactors) 
  tmp[0] = src[2]*src[7];
  tmp[1] = src[3]*src[6];
  tmp[2] = src[1]*src[7];
  tmp[3] = src[3]*src[5];
  tmp[4] = src[1]*src[6];
  tmp[5] = src[2]*src[5];

  tmp[6] = src[0]*src[7];
  tmp[7] = src[3]*src[4];
  tmp[8] = src[0]*src[6];
  tmp[9] = src[2]*src[4];
  tmp[10] = src[0]*src[5];
  tmp[11] = src[1]*src[4];
  // calculate second 8 elements (cofactors) 
  dst[8] = tmp[0]*src[13] + tmp[3]*src[14] + tmp[4]*src[15];
  dst[8] -= tmp[1]*src[13] + tmp[2]*src[14] + tmp[5]*src[15];
  dst[9] = tmp[1]*src[12] + tmp[6]*src[14] + tmp[9]*src[15];
  dst[9] -= tmp[0]*src[12] + tmp[7]*src[14] + tmp[8]*src[15];
  dst[10] = tmp[2]*src[12] + tmp[7]*src[13] + tmp[10]*src[15];
  dst[10]-= tmp[3]*src[12] + tmp[6]*src[13] + tmp[11]*src[15];
  dst[11] = tmp[5]*src[12] + tmp[8]*src[13] + tmp[11]*src[14];
  dst[11]-= tmp[4]*src[12] + tmp[9]*src[13] + tmp[10]*src[14];
  dst[12] = tmp[2]*src[10] + tmp[5]*src[11] + tmp[1]*src[9];
  dst[12]-= tmp[4]*src[11] + tmp[0]*src[9] + tmp[3]*src[10];
  dst[13] = tmp[8]*src[11] + tmp[0]*src[8] + tmp[7]*src[10];
  dst[13]-= tmp[6]*src[10] + tmp[9]*src[11] + tmp[1]*src[8];
  dst[14] = tmp[6]*src[9] + tmp[11]*src[11] + tmp[3]*src[8];
  dst[14]-= tmp[10]*src[11] + tmp[2]*src[8] + tmp[7]*src[9];
  dst[15] = tmp[10]*src[10] + tmp[4]*src[8] + tmp[9]*src[9];
  dst[15]-= tmp[8]*src[9] + tmp[11]*src[10] + tmp[5]*src[8];
  // calculate determinant 
  det=src[0]*dst[0]+src[1]*dst[1]+src[2]*dst[2]+src[3]*dst[3];
  if ( det == 0 ) {
    cout << "\nError: determinant value 0!";
    return mi; 
  }
  // calculate matrix inverse 
  det = 1 / det;
  for (int j = 0; j < 16; j++)
    dst[j] *= det;

  mi.set ( dst );
  return mi;            //return inverse
}
