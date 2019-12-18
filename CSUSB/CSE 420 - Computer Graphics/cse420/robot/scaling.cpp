/*
 * transform.cpp
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void init(void)
{
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glLoadIdentity ();             	// clear the matrix 
   glMatrixMode (GL_PROJECTION);
           				// viewing transformation  
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity();
   glColor3f (1.0, 0.0, 0.0);     //red color
   glTranslatef ( 0, 0.8, 0 );    //move teapot upward
   glutWireTeapot( 1.0 );

  // glLoadIdentity();
   glColor3f (0.0, 1.0, 0.0);     //green color
   glTranslatef ( 0, -0.8, 0 );   //move reflected teapot downward
   glScalef ( 1.5, -1.0, 1.0 );   //scale and reflect
   glutWireTeapot( 1.0 );
   
   glFlush ();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
