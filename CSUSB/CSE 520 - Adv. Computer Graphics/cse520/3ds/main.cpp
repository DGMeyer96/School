/* main.cpp
 * This is a generic OpenGL routine for rendering a scene.
 * It allows users to rotate and translate the scene.
 * For the course CS 520 of Cse, CSUSB, 2009 Winter
 * @Author: T.L. Yu 
 */
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

using namespace std;

#define WINWIDTH	400
#define WINHEIGHT	300

extern void display();
int anglex = 0;			//rotation angles
int angley = 0;
int anglez = 0;
int inca = 4;			//angle increment
float tx = 0;			//translation values
float ty = 0;
float tz = 0;
float tinc[3] = {0, 0, 0};	//translation increment
static int window;
char *testfile;

void key_press(unsigned char key, int x, int y)
{
  switch(key) {
    case 'x':
      anglex = ( anglex + inca ) % 360;
      glutPostRedisplay();
      break;
    case 'X':
      anglex = ( anglex - inca ) % 360;
      glutPostRedisplay();
      break;
    case 'y':
      angley = ( angley + inca ) % 360;
      glutPostRedisplay();
      break;
    case 'Y':
      angley = ( angley - inca ) % 360;
      glutPostRedisplay();
      break;
    case 'z':
      anglez = ( anglez + inca ) % 360;
      glutPostRedisplay();
      break;
    case 'Z':
      anglez = ( anglez - inca ) % 360;
      glutPostRedisplay();
      break;
    case 'a':
      tx += tinc[0];
      glutPostRedisplay();
      break;
    case 'A':
      tx -= tinc[0];
      glutPostRedisplay();
      break;
    case 'b':
      ty += tinc[1];
      glutPostRedisplay();
      break;
    case 'B':
      ty -= tinc[1];
      glutPostRedisplay();
      break;
    case 'c':
      tz += tinc[2];
      glutPostRedisplay();
      break;
    case 'C':
      tz -= tinc[2];
      glutPostRedisplay();
      break;
    default:
	//scene_toggle_lighting();
	break;
    case 27: /* escape */
	glutDestroyWindow(window);
	exit(0);
	break;
  }
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -5 );
}
   
int main(int argc, char *argv[])
{
 
  if ( argc < 2 ) {
    printf("\nUsage: %s 3ds_file\n", argv[0] );
    return 1;
  } 
  testfile = ( char * ) malloc ( 100 );
  assert ( testfile );
  strcpy ( testfile, argv[1] );    
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
  glutInitWindowSize(WINWIDTH, WINHEIGHT);

  window = glutCreateWindow(argv[0]);
  #ifdef FULLSCREEN
	glutFullScreen();
  #endif

  glutKeyboardFunc(key_press);

  /* GL settings */
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);		
  glClearDepth(1.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho ( 0, 200.0, 0, 200.0, 200, -200 );
  glMatrixMode(GL_MODELVIEW);
  glutDisplayFunc( display );

  glutMainLoop();			//event loop
  return 0;
}
