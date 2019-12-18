/*
 *  cube_mat.cpp
 *  This program demonstrates examining the transformation matrix values.
 *  
 *  A wireframe cube is rendered.
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

void init(void)
{
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glShadeModel (GL_FLAT);
}

//print the transformation matrix
template<class T>
void print_mat ( T m[][4] )
{
  cout.precision ( 4 );
  cout << fixed;
  for ( int i = 0; i < 4; ++i ) {
    cout << "\t";
    for ( int j = 0; j < 4; ++j )
      cout <<  m[j][i] << "\t";
    cout << endl;
  }
  cout << endl;
}

void display(void)
{
   float p[4][4];
   double pd[4][4];

   glClear (GL_COLOR_BUFFER_BIT);
   glLineWidth ( 5 );
   glColor3f (1, 0, 0);	  	//color
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();             	// clear the matrix 
           				// viewing transformation  
   //glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   //glFrustum (-1.0, 1.0, -1.0, 1.0, 2, 20.0);
   glOrtho (-1.0, 1.0, -1.0, 1.0, 2, 20.0);
//   gluPerspective ( 30, 1, 2, 20 );     
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   glMatrixMode (GL_PROJECTION);
   glGetFloatv(GL_PROJECTION_MATRIX,&p[0][0]);
   cout << "Projection Matrix:" << endl;
   print_mat ( p );
   getchar();
  glTranslatef ( 2, 2, 0 );
  // glRotatef ( 60, 0, 0, 1 );
  // glRotatef ( 30, 0, 1, 0 );
   glRotatef ( 45, 1, 0, 0 );

   glGetDoublev(GL_MODELVIEW_MATRIX, &pd[0][0]);
   cout << "Composite Rotation Matrix:" << endl;
   print_mat ( pd );
   glutWireCube (1.0);

   glLoadIdentity();
   glColor3f ( 0, 1, 0 );
   //glRotatef ( 30, 0, 1, 0 );
   //glRotatef ( 60, 0, 0, 1 );
   glRotatef ( 45, 1, 0, 0 );
   glTranslatef ( 2, 2, 0 );
   glGetDoublev(GL_MODELVIEW_MATRIX, &pd[0][0]);
   cout << "Composite Rotation Matrix:" << endl;
   print_mat ( pd );
   glutWireCube (1.0);
   
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
