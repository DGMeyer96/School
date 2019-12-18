/*
 * rotate.cpp
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };

void init(void)
{
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glShadeModel (GL_FLAT);
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glColorMaterial(GL_FRONT, GL_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);

}

void text18 ( char *s )
{
  char *p;

  for ( p = s; *p; p++ )
    glutBitmapCharacter ( GLUT_BITMAP_HELVETICA_18, *p );
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity ();             	// clear the matrix 
   glMatrixMode (GL_PROJECTION);
           				// viewing transformation  
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
//   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity();
     gluLookAt ( 5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   //glColor3f(1, 1, 1);
   glColor3f(0, 0, 0);
   glRasterPos3f (3.2, 0, 0 );
   text18( "x" );
   glRasterPos3f (0, 3.2, 0 );
   text18( "y" );
   glRasterPos3f (0, 0, 3.2 );
   text18( "z" );
   glBegin( GL_LINE );
     glVertex3f(0, 0, 0);
     glVertex3f(3.0, 0, 0);
     glVertex3f(0, 0, 0);
     glVertex3f(0, 3.0, 0);
     glVertex3f(0, 0, 0);
     glVertex3f(0, 0, 3.0);
   glEnd();
   glLoadIdentity();
   glColor3f (1.0, 0.0, 0.0);     //red color
   glTranslatef ( 1.0, 0.0, 0 );  
   //glutWireTeapot( 0.6 );
   glutSolidTeapot( 0.6 );

   glLoadIdentity();
   glColor3f (0.0, 1.0, 0.0);     //green color
   glRotatef (135, 0, 0, 1 );
   glTranslatef ( 1.0, 0.0, 0 );  
  // glutWireTeapot( 0.6 );
   glutSolidTeapot( 0.6 );
  
   
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
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
