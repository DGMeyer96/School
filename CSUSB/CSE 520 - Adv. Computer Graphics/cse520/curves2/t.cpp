/*   bezcurve.cpp
 **  This program uses evaluators to draw a Bezier curve.
 **/
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;
const int maxPoints = 100;
float buf[maxPoints][3];
int  npoints = 0;

//float endPoint[3];

class Apoint{
public:
  float a[3]; 
  //contructor
  Apoint ( float x, float y, float z ) {
    a[0] = x; a[1] = y, a[2] = z;
  }
};

vector<Apoint *> points;
Apoint *p;

const int screenHeight = 800;
const int screenWidth  = 800;

void addPoint( int x, int y )
{
   glColor3f(1.0, 0.0, 0.0);
   p = new Apoint ( (float) x, (float) y, 0.0 ); 
   points.push_back ( p );
} //addPoint

void init(void)
{
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glShadeModel(GL_FLAT);
}
                                                                                
void display(void)
{
   int i;

   glClear(GL_COLOR_BUFFER_BIT);
   npoints = points.size();
   if ( npoints == 0  || npoints > maxPoints ) {
      glFlush();
      return;
   }
                                                                             
   glLineWidth ( 4 );
   glColor3f(0.0, 0.0, 0.0);
   i = npoints - 1;
   for ( int j = 0; j < 3; j++ )
	buf[i][j] = points[i]->a[j];

   cout << npoints << endl;
   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, npoints, &buf[0][0] );
   glEnable(GL_MAP1_VERTEX_3);
   glBegin(GL_LINE_STRIP);
     float nx = npoints * 5;
     for (i = 0; i <= nx; i++)
         glEvalCoord1f((GLfloat) i/nx);
   glEnd();

   // The following code displays the control points as dots and connects them. 
   glPointSize(9.0);
   glColor3f(1.0, 0.0, 0.0);
   glLineWidth ( 1 );
   glBegin(GL_LINE_STRIP);
      for (i = 0; i < npoints; i++)
         glVertex3fv(&buf[i][0]);
   glEnd();
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_POINTS);
      for (i = 0; i < npoints; i++)
         glVertex3fv(&buf[i][0]);
   glEnd();
   glFlush();
}
 
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D ( 0, 800, 0, 800 );
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
                                                                                
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}
  
void myMouse( int button, int state, int x, int y )
{
  if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    addPoint( x, screenHeight - y );
  glutPostRedisplay();
}

void myMovedMouse(  int mouseX, int mouseY)
{
  GLint x = mouseX;
  GLint y = screenHeight - mouseY;
  if ( npoints > 1 ) {
    glBegin( GL_LINES );
      glVertex3fv ( &buf[npoints-1][0] );
      glVertex3f ( x, y, 0 );
    glEnd();
  }

  glFlush();
} //myMovedMouse
  
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (screenWidth, screenHeight );
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc (keyboard);
   glutMouseFunc( myMouse );
   glutMotionFunc( myMovedMouse );

   glutMainLoop();
   return 0;
}
