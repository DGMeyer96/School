/*
 * barn.cpp : Demo of rendering a mesh.
 */
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "Mesh.h"

using namespace std;

Mesh barn;

void init(void)
{
   //The light components that are reflected
   GLfloat mat_specular[] = { 1, 0.8, 0.4, 1.0 };
   GLfloat mat_ambient[] = { 0.8, 0.8, .2, 1.0 };
   GLfloat mat_diffuse[] = { 1, 0.8, 0.4, 1.0 };
   GLfloat mat_shininess[] = { 500.0 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
   GLfloat light[] = { 1, 1, 1 };
   GLfloat lmodel_ambient[] = { 1, 1, 1, 1.0 };
   GLfloat light1[] = {1, 0, 0 };
   GLfloat light_position1[] = { -1.0, -1.0, -1.0, 0.0 };
   GLfloat light_position2[] = { 0.0, 1.0, 1.0, 0.0 };
   glClearColor (1.0, 1.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_ambient);

   glLightfv(GL_LIGHT0, GL_POSITION, light_position2);

   glLightfv(GL_LIGHT0, GL_DIFFUSE, light );
   glLightfv(GL_LIGHT0, GL_AMBIENT, light );
   glLightfv(GL_LIGHT0, GL_SPECULAR, light );


   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glEnable(GL_DEPTH_TEST);
}

void display(void)
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho(-2.0, 2.0, -2.0, 2.0, 0.1, 100 );
  glMatrixMode(GL_MODELVIEW); // position and aim the camera
  glLoadIdentity();
  gluLookAt(8.0, 8.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f( 0, 0, 0 );
  barn.renderMesh();               
  glFlush();
}

void keyboard ( unsigned char key, int x, int y )
{
  switch ( key ) {
  case 27:
    exit ( 0 );
  }
}

int main( int argc, char *argv[] )
{

  if ( !barn.readData ( (char*) "data.txt" ) ) {
     cout << "Error opening file data.txt" << endl;
     return 1;
  }
  glutInit( &argc, argv );
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize( 500, 500 );
  glutInitWindowPosition( 100, 100 );
  glutCreateWindow("Mesh ");
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc( keyboard );
  glClearColor( 1.0f, 1.0f, 1.0f, 0.0f ); //white background
  glViewport ( 0, 0, 500, 500 );

  glutMainLoop();

  return 0;
}

