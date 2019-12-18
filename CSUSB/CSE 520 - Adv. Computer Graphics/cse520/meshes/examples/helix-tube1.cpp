/* helix-tube1.cpp : Constructs a tube using helix curve and Frenet frames.
 */

#include <SDL/SDL.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "Point3.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Matrix14.h"
#include "Matrix41.h"
#include "Matrix44.h"

using namespace std;

int anglex= 0, angley = 0, anglez = 0;          //rotation angles
int window;

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho(-3.0, 3.0, -3.0, 3.0, 0.1, 100 );
  glMatrixMode(GL_MODELVIEW); // position and aim the camera
  glLoadIdentity();
  gluLookAt( 0, 0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  printf("\nPress 'X', 'Y', 'Z' to rotate tube!\n");
}

//helix curve
void get_C ( float C[4], float u, float b )
{
  C[0] = cos ( u );
  C[1] = sin ( u );
  C[2] = b * u;
  C[3] = 1;
}


//Matrix for transforming to Frenet frame
void setM( Matrix44 &M, float u, float b )
{
  float c = 1.0 / sqrt ( 1 + b*b );
  M.setCol( 0, -c * sin(u), c * cos(u), b * c, 0);	//Tangent   T(u)
  M.setCol( 1,  -cos(u), -sin(u), 0, 0 );		//Normal    N(u)
  M.setCol( 2, c * b * sin(u), -c * b * cos(u), c, 0 );	//Binormal  B(u)
  M.setCol( 3, cos(u), sin(u), b * u, 1 );  		//The curve C(u)
}

 
//An array is not copyable; so we define this class mainly for copying 
class Cdouble3 {           //Note: array is not copyable; e.g. int a[8],b[8]; "a = b;" won't work 
  public:
     double p3[3];
};

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  const float b = 0.1;	   //constant of Helix curve
  Matrix44 M44;		   //Transformation matrix
  const int N = 4;	   //number of vertices in base

  vector<Cdouble3>vp0(N), vp1(N);
  Matrix41 p_1;			//transformed point	

  //4 vertices of a quad
  //homogeneous coordinates of the four vertices of a quad
  Matrix41 points[4];		//define four points
  points[0] =  Matrix41 ( 0, -0.1, -0.1,  1 );	//x, y, z, w
  points[1] =  Matrix41 ( 0, -0.1,  0.1, 1 );	//x, y, z, w
  points[2] =  Matrix41 ( 0, 0.1,  0.1, 1 );	//x, y, z, w
  points[3] =  Matrix41 ( 0, 0.1,  -0.1,  1 );	//x, y, z, w

  glColor3f ( 0.1, 1.0, 0 ); 
  glPushMatrix();
  glRotatef( anglex, 1.0, 0.0, 0.0);   //rotate the object about x-axis
  glRotatef( angley, 0.0, 1.0, 0.0);   //rotate about y-axis   
  glRotatef( anglez, 0.0, 0.0, 1.0);   //rotate about z-axis
  float C[4];
  glLineWidth ( 3 );
  glPolygonMode( GL_FRONT, GL_LINE );
  glPolygonMode( GL_BACK, GL_LINE );
  
  //The curve
  glBegin(GL_LINE_STRIP );
  for ( float u = 0; u <=  26; u += 0.2 ) {
    get_C ( C, u, b );
     glVertex4fv( C );
  }
  glColor3f ( 1.0, 0.1, 0 ); 
  glEnd();

  float p3[3];		//3-D point, (x, y, z)
  //starting
  setM ( M44, 0, b );	//u = 0
  for ( int i = 0; i < 4; ++i ) {
    p_1 = M44 * points[i];	//transform the point
    p_1.get3( vp0[i].p3 );	//put (x, y, z) in vp0[i].p3[]
  }
  glBegin( GL_QUADS );		//a side has four points
  for ( float u = 0.2; u <=  26; u += 0.2 ) {
    setM ( M44, u, b );
    for ( int i = 0; i < N; ++i ) {
      p_1 = M44 * points[i];	//transform the point
      p_1.get3( vp1[i].p3 );	//put (x, y, z) in vp1[i].p3[]
    }
    for ( int i = 0; i < N; ++i ) { //draw the N sides of tube between 'base' and 'cap'
      int j = (i+1) % N;
      glVertex3dv( vp0[i].p3 );
      glVertex3dv( vp0[j].p3 );
      glVertex3dv( vp1[j].p3 );
      glVertex3dv( vp1[i].p3 );
    }
    copy ( vp1.begin(), vp1.end(), vp0.begin() );  //copy vp1 to vp0
  }  //for u
  glEnd();
  glPopMatrix();
  glFlush();
}

void keyboard ( unsigned char key, int x, int y )
{
  switch ( key ) {
  case 27:
    glutDestroyWindow(window);
    exit ( 0 );
   case 'x':
      anglex = ( anglex + 3 ) % 360;
      break;
    case 'X':
      anglex = ( anglex - 3 ) % 360;
      break;
    case 'y':
      angley = ( angley + 3 ) % 360;
      break;
    case 'Y':
      angley = ( angley - 3 ) % 360;
      break;
    case 'z':
      anglez = ( anglez + 3 ) % 360;
      break;
    case 'Z':
      anglez = ( anglez - 3 ) % 360;
      break;
    case 'r':                                   //reset
      anglez = angley = anglex = 0;
      break;
  }
  glutPostRedisplay();
}


int main( int argc, char *argv[] )
{
  glutInit( &argc, argv );
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize( 500, 500 );
  glutInitWindowPosition( 100, 100 );
  window = glutCreateWindow("Mesh ");
  glutDisplayFunc(display);
  glutKeyboardFunc( keyboard );
  glViewport ( 0, 0, 500, 500 );
  init ();

  glutMainLoop();

  return 0;
}

