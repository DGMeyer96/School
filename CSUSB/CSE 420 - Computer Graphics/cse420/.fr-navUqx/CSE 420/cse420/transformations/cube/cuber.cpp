/*
 *  cuber.cpp
 *  rotation demo
 */
#include <GL/glut.h>
#include <stdlib.h>

void init(void) 
{
   //glClearColor (0.0, 0.0, 0.0, 0.0);
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
//   glColor3f (1.0, 1.0, 1.0);
   glColor3f (0.0, 0.0, 0.0);
   glLineWidth ( 4 );
   glLoadIdentity ();             /* clear the matrix */
           /* viewing transformation  */
   //gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   gluLookAt (3.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   glPushMatrix();
   glutWireTeapot ( 0.6 );
   glColor3f ( 1.0, 0.0, 0 );
   glTranslatef( 2, 0, 0 );
   glutWireTeapot ( 0.6 );
   glColor3f ( 0, 1.0, 0 );
   glRotatef ( 90, 0, 1, 0 );
   glutWireTeapot ( 0.6 );
   glPopMatrix();
   glColor3f ( 0.0, 0.0, 1 );
   glRotatef ( 90, 0, 1, 0 );
   glTranslatef( 2, 0, 0 );
   glutWireTeapot ( 0.6 );
   
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
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
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
