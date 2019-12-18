/*
  renderer.cpp
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Cube.h"

using namespace std;

static GLint win = 0;
Cube     *cube;
const int screenWidth = 500;
const int screenHeight = 500;
float mvMatrix[4][4];   //model-view matrix
float mvpMatrix[4][4];  //model-view projection matrix
float previousX=0,  previousY=0, dx = 0, dy = 0;
float angle = 0;
int  program = 0;

int  init(void)
{
   const char *version;

   version = (const char *) glGetString(GL_VERSION);
   if (version[0] < '2' || version[1] != '.') {
      printf("This program requires OpenGL >= 2.x, found %s\n", version);
      exit(1);
   }
   glEnable (GL_CULL_FACE);
   glCullFace(GL_BACK);
 
   int  loadStatus = 0;
   loadStatus = 0;
   cube = new Cube( loadStatus );
   if ( loadStatus )
      printf("Cube shader creation OK!\n"); 

   return  loadStatus;
}

static void reshape(int width, int height)
{
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-1.0, 1.0, -1.0, 1.0, 5.0, 25.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0f, 0.0f, -15.0f);
}

void CleanUp(void)
{
   glutDestroyWindow(win);
}

static void idle(void)
{
   glutPostRedisplay();
}


static void keyboard(unsigned char key, int x, int y)
{
   switch(key) {
   case 27:
      CleanUp();
      exit(0);
      break;
   }
   glutPostRedisplay();
}

void display(void)
{
   GLfloat vec[4];

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClearColor( 1.0, 1.0, 1.0, 0.0 );	//get white background color

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 6.3, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  //inside box
   glRotatef ( angle, 1.0f, 0.2f, 0.2f );
   // retrieve model-view matrix
   glGetFloatv(GL_MODELVIEW_MATRIX, &mvMatrix[0][0]);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-10.0, 10.0, -10.0, 10.0, 5.0, 50.0);
   // multiply projection matrix by model-view matrix
   glMultMatrixf ( &mvMatrix[0][0] );
   // retrieve model-view projection matrix
   glGetFloatv(GL_PROJECTION_MATRIX, &mvpMatrix[0][0]);
   // pass transformation matrix to vertex shader
   cube->draw( mvpMatrix );
   cube->cleanUp();
   
   glutSwapBuffers();
   glFlush();
}


void movedMouse(  int mouseX, int mouseY)
{
  dx = mouseX - previousX;
  dy = mouseY - previousY;

  // reverse direction of rotation above the mid-line
  if (mouseY > screenHeight / 2)
     dx = dx * -1 ;
  // reverse direction of rotation to left of the mid-line
  if (mouseX < screenWidth / 2)
     dy = dy * -1 ;

  angle = angle + (dx + dy) / 2;  //scale factor of 2
  previousX = mouseX;
  previousY = mouseY;
  glutPostRedisplay();
}

int main(int argc, char *argv[])
{
   int success = 0;

   glutInit(&argc, argv);
   glutInitWindowPosition( 0, 0);
   glutInitWindowSize(screenWidth, screenHeight);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   win = glutCreateWindow(argv[0]);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutIdleFunc(idle);

   glutMotionFunc( movedMouse );

   // Initialize the "OpenGL Extension Wrangler" library
    glewInit();

   success = init();
   if ( success )
     glutMainLoop();
   else
     printf( "Initialization failed!\n");
   return 0;
}

