/*
 * prism.cpp 
 */ 

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Point3.h"
#include "Vector3.h"

const double PI = 3.14159265789;
const double X = cos ( PI / 3 );
const double Y = sin ( PI / 3 );
const double H = 2;    //height
const int N0 = 10;     //number of different vertices in base
const int N1 = 12;     //number of actual vertices in base
static double base[N0][3] = {    
   {-2, 1.0, 0}, {-2, -1, 0}, {-1, 0.0, 0}, {-X, -Y, 0},    
   {X, -Y, 0}, {1, 0, 0}, {2, -1, 0}, {2, 1, 0},    
   {X, Y, 0.0}, {-X, Y, 0.0}  
};
static double cap[N0][3];

//indices for base and cap
static int indices[N1] = { 
   0, 1, 2, 3, 4, 5, 6, 7, 5,8, 9, 2 };  

static int indices1[3] = { 0, 1, 2};
static int indices2[6] = { 2, 3, 4, 5, 8, 9};
static int indices3[3] = { 5, 6, 7};

int *indexp[3] = {indices1, indices2, indices3}; 
int nsides[3] = {3, 6, 3};

int anglex= 0, angley = 0, anglez = 0;          //rotation angles

void draw ( double a[N0][3] ) 
{
   for ( int j = 0; j < 3; j++ ) { 
     glBegin(GL_POLYGON);
       for ( int i = 0; i < nsides[j]; i++ ) {
         int k = indexp[j][i];
         glVertex3dv ( a[k] ); 
       }
     glEnd(); 
   }
}

void setColor ( int n )
{
  if ( n == 1 )
    glColor3f( 1, 0.5, 0 );
  else if ( n == 2 )
    glColor3f( 0, 1, 0 );
  else if ( n == 3 )
    glColor3f( 0, 1, 0.2 );
  else if ( n == 4 )
    glColor3f( 1, 0.2, 0.1 );
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

void drawWalls () 
{
  int i, j, k, n = 0;
  int sides[3] = {3, 6, 3};
  for ( i = 0; i < 3; i++ ) {
       for ( j = 0; j < nsides[i]; j++ ) {
            setColor ( n++ );
            glBegin(GL_POLYGON);    //use different colors
 	    k = indexp[i][j];
            glVertex3dv ( cap[k] ); 
            glVertex3dv ( base[k] ); 
            int next = (j + 1) % nsides[i];
 	    k = indexp[i][next];
            glVertex3dv ( base[k] ); 
            glVertex3dv ( cap[k] ); 
          glEnd(); 
       }
  }
}

void init(void) 
{
   glClearColor (1, 1.0, 1.0, 0.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glShadeModel (GL_FLAT);
   glEnable(GL_DEPTH_TEST);
   glEnable ( GL_CULL_FACE );
   glCullFace ( GL_BACK );
   glLineWidth ( 2 );
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();            
   gluLookAt (0, 0, 5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   for ( int i = 0; i < N0; i++ ){
     cap[i][0] = base[i][0];
     cap[i][1] = base[i][1];
     cap[i][2] = H;
   }
   printf("\nPress 'X', 'Y', 'Z' to rotate!\n");
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glRotatef( anglex, 1.0, 0.0, 0.0);   //rotate the object about x-axis
  glRotatef( angley, 0.0, 1.0, 0.0);   //rotate about y-axis   
  glRotatef( anglez, 0.0, 0.0, 1.0);   //rotate about z-axis
   
  glColor3f ( 0.1, 0.8, 0.1 );
  glFrontFace( GL_CW );   //Clockwise as front face for base
  draw( base );           //draw base
  glColor3f ( 0.8, 0.1, 0.1 );
  glFrontFace( GL_CCW );  //Anticlockwise as front face for cap and walls
  draw( cap );            //draw cap
  drawWalls();
  glPopMatrix();
  glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-2.0, 2.0, -2.0, 2.0, 2.0, 20.0);
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
