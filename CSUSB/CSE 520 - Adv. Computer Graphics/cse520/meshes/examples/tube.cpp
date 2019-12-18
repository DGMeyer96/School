/*
 * tube.cpp 
 */ 

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Point3.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Matrix14.h"
#include "Matrix41.h"
#include "Matrix44.h"


const int N0 = 3;      //number of vertices in base
double base[N0][3] = {    
   {0, 0.5, 0}, {0, 0, 0}, {0.5, 0.0, 0}
};

double cap[3][N0][3];

int anglex= 0, angley = 0, anglez = 0;          //rotation angles

//Three Transformation matrices
double a0[4][4] = { {0.5, 0.0, 0.0, 1.0},
		   {0.0, 0.5, 0.0, -0.2},
		   { 0, 0, 0.5, 0.5 },
 		   { 0, 0, 0, 1 } }; 
double a1[4][4] = { {0.8, 0.0, 0.0, 2.0},
		   {0.0, 0.8, 0.0, 0.2},
		   { 0, 0, 0.8, 0.7 },
 		   { 0, 0, 0, 1 } }; 
double a2[4][4] = { {1.5, 0.0, 0.0, 3.0},
		   {0.0, 1.5, 0.0, 1.0},
		   { 0, 0, 1.5, 1.0 },
 		   { 0, 0, 0, 1 } }; 

//Will contruct 3 class objects for transformation matrices
Matrix44 M[3];

//draw base or cap
void draw ( double a[N0][3] ) 
{
     glBegin(GL_POLYGON);
       for ( int i = 0; i < 3; i++ ) {
         int k = i;
         glVertex3dv ( a[k] ); 
       }
     glEnd(); 
}

void setColor ( int n )
{
  if ( n == 0 )
    glColor3f( 0.2, 0.5, 1 );
  else if ( n == 1 )
    glColor3f( 1, 0.5, 0 );
  else if ( n == 2 )
    glColor3f( 0, 1, 0 );
  else if ( n == 3 )
    glColor3f( 0, 1, 0.2 );
  else if ( n == 4 )
    glColor3f( 0.6, 0.8, 0.3 );
  else if ( n == 5 )
    glColor3f( 0.3, 0.2, 1 );
  else if ( n == 6 )
    glColor3f( 0.2, 1, 1 );
  else if ( n == 7 )
    glColor3f( 0.5, 0.2, 0 );
  else if ( n == 8 )
    glColor3f( 0.2, 0.5, 0 );
  else if ( n == 8 )
    glColor3f( 0.2, 0.5, 1 );
  else if ( n == 9 )
    glColor3f( 1.0, 0.2, 0.5 );
  else if ( n == 10 )
    glColor3f( 0.1, 0.2, 0.5 );
  else
    glColor3f ( 0, 0, 0 );
}

//draw walls formed by a base and a cap
void drawWalls ( double base[3][3], double cap[3][3] ) 
{
  int j, k, n = 0;
  for ( j = 0; j < 3; j++ ) {
    setColor ( n++ );           //use different colors 
    glBegin(GL_POLYGON);    
      k = j;
      glVertex3dv ( cap[k] ); 
      glVertex3dv ( base[k] ); 
      int next = (j + 1) % 3;
      k = next;
      glVertex3dv ( base[k] ); 
      glVertex3dv ( cap[k] ); 
    glEnd(); 
  }
}

void init(void) 
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glShadeModel (GL_FLAT);
   glEnable(GL_DEPTH_TEST);
   glClear (GL_COLOR_BUFFER_BIT);
   glLineWidth ( 2 );
   glColor3f (0.0, 0.0, 0.0);
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();            
   gluLookAt (0, 0, 5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   //setup transformation matrices 
   M[0].set ( a0 );  M[1].set ( a1 );  M[2].set ( a2 );
   //calculate caps
   for ( int k = 0; k < 3; k++ ) {
     Matrix41 Base[N0];
     for ( int i = 0; i < N0; i++ ){
       Base[i].set ( base[i], 1 );
       Matrix41 temp = M[k] * Base[i];
       temp.get3 ( cap[k][i] );   //put values in cap array 
     }
  }
  printf("\nPress 'X', 'Y', 'Z' to rotate tube!\n");
}

void display(void)
{
  
  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glRotatef( anglex, 1.0, 0.0, 0.0);   //rotate the object about x-axis
  glRotatef( angley, 0.0, 1.0, 0.0);   //rotate about y-axis   
  glRotatef( anglez, 0.0, 0.0, 1.0);   //rotate about z-axis
   
  glColor3f ( 0.1, 0.8, 0.1 );
  //  glFrontFace( GL_CW );
  draw( base );     //draw base
  glColor3f ( 0.8, 0.1, 0.1 );
  //  glFrontFace( GL_CCW );
  for ( int i = 0; i < 3; i++ ) {
    draw( cap[i] );      //draw cap
    if ( i == 0 )
      drawWalls( base, cap[0] );
    else
      drawWalls( cap[i-1], cap[i] );
  }
  glPopMatrix();
  glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho (-1.0, 4.0, -1.0, 4.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
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

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
   glutInitWindowSize (800, 800); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
