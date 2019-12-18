/*
 * prism1.cpp 
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


const double PI = 3.14159265789;
const double X = cos ( PI / 3 );
const double Y = sin ( PI / 3 );
const double H = 3;    //height
const int N0 = 3;      //number of different vertices in base
const int N1 = 3;      //number of actual vertices in base
static double base[N0][3] = {    
   {0, 1.0, 0}, {0, 0, 0}, {1, 0.0, 0}
};
static double cap[N0][3];
static double cap1[N0][3];

//indices for base and cap
static int indices[N1] = { 
   0, 1, 2 }; 

static int indices1[3] = { 0, 1, 2};
static int indices2[6] = { 2, 3, 4, 5, 8, 9};
static int indices3[3] = { 5, 6, 7};

int *indexp[3] = {indices1, indices2, indices3}; 
int nsides[3] = {3, 6, 3};

int anglex= 0, angley = 0, anglez = 0;          //rotation angles

double theta = 3.1415926 / 6;

double a[4][4] = { { cos (theta), -sin (theta), 0 , 0 },
		   { -sin (theta), cos (theta), 0, 0 },
		   { 0, 0, 1, H },
 		   { 0, 0, 0, 1 } }; 

Matrix44 Rz ( a );

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

void drawWalls ( double cap[3][3] ) 
{
  int j, k, n = 0;
       for ( j = 0; j < 3; j++ ) {
          setColor ( n++ );
      glBegin(GL_POLYGON);    //use different colors
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
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glShadeModel (GL_FLAT);
   glEnable(GL_DEPTH_TEST);
   glClear (GL_COLOR_BUFFER_BIT);
   glLineWidth ( 2 );
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();            
   gluLookAt (0, 0, 5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   float sx = 0.6, sy = 0.6;
   for ( int i = 0; i < N0; i++ ){
     cap[i][0] = sx * base[i][0];
     cap[i][1] = sy * base[i][1];
     cap[i][2] = H;
   }
   Matrix41 Base[N0];
   for ( int i = 0; i < N0; i++ ){
     Base[i].set ( base[i], 1 );
     Matrix41 temp = Rz * Base[i];
     temp.get3 ( cap1[i] ); 
     temp.set ( base[i], 1 );   //obtain base vertex
    // temp.print();
   }
   printf("\nPress 'X', 'Y', 'Z' to rotate!\n");
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable ( GL_CULL_FACE );
  glCullFace ( GL_BACK );
  glPushMatrix();
  glRotatef( anglex, 1.0, 0.0, 0.0);   //rotate the object about x-axis
  glRotatef( angley, 0.0, 1.0, 0.0);   //rotate about y-axis   
  glRotatef( anglez, 0.0, 0.0, 1.0);   //rotate about z-axis
   
  glColor3f ( 0.1, 0.8, 0.1 );
  glFrontFace( GL_CW );
  draw( base );    //draw base
  glColor3f ( 0.8, 0.1, 0.1 );
  glFrontFace( GL_CCW );
  draw( cap );     //draw cap
  drawWalls( cap );

  glTranslatef( 2, 0, 0 );
  glColor3f ( 0.1, 0.8, 0.1 );
  glFrontFace( GL_CW );
  draw( base );    //draw base
  glColor3f ( 0.8, 0.1, 0.1 );
  glFrontFace( GL_CCW );
  draw( cap1 );    //draw cap
  drawWalls( cap1 );
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
