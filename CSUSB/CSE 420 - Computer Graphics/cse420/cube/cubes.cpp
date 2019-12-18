#include <GL/glut.h>
#include <stdlib.h>
#include <SDL/SDL.h>

void init(void) 
{
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (0.0, 0.0, 0.0);
   //float x = 3.0, y = 2.0, z = 5.0;
   float x = 0.0, y = 0.0, z = 5.0;
   glLoadIdentity ();             /* clear the matrix */
           /* viewing transformation  */
   gluLookAt ( x, y, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  // glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
  // glutWireCube (1.0);
   glutSolidCube (1.0);
   glPointSize ( 9 );
   glColor3f ( 0, 1, 0 );
   glBegin (GL_POINTS);
    glVertex3f( 0, 0, -1 );
    //glVertex3f( 0.5, 0.5, -2 );
   glEnd();
   glFlush ();
   SDL_Delay ( 5000 );
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
   glEnable ( GL_DEPTH_TEST );
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
