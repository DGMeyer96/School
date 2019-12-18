
/*
 *  cube.c
 *  This program demonstrates a single modeling transformation,
 *  glScalef() and a single viewing transformation, gluLookAt().
 *  A wireframe cube is rendered.
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

void init(void) 
{
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glShadeModel (GL_FLAT);
}

//by Tong
void draw_cube ( float a )
{
  glutWireCube ( a );
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (0.0, 0.0, 0.0);
   glLoadIdentity ();             /* clear the matrix */
           /* viewing transformation  */
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
 //  gluLookAt (5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
 //  glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
//   glutWireCube (2.0);
 //  glRotatef( 30, 0, 1, 0 );
   glPushMatrix ();
   glLineWidth ( 2 );
  // draw_cube ( 0.5 );
   glColor3f ( 1, 0, 0 );
   glTranslatef ( 1.0, 0.5, 0 );
   glScalef ( 0.5, 2.0, 1 );
   draw_cube ( 0.5 );
  
   glColor3f ( 0, 1, 0  ); 
   glPopMatrix();
   glPushMatrix(); 
   glTranslatef ( -1.0, -0.5, 0 );
   draw_cube ( 0.5 );

   glColor3f ( 0, 0, 1  );
   glPopMatrix();
   glTranslatef ( -1.0, 0, 0 );
   //draw_cube ( 0.5 );
   glRotatef ( 90, 0, 1, 0 );
   glutWireTeapot ( 0.4 ); 
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
//   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20);
   gluPerspective ( 30, 1, 1.5, 20 );
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
