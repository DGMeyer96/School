/*
 * CS 520: environment-map.cpp 
 * Demonstrates the creation of environment map using the command
 * glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, 500, 500, 0);
 * The scene can be rotated by pressing keys 'x', 'X', 'y', 'Y', 'z', 'Z'.
 * @Author: T.L. Yu, 2008F 
 *
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

int window;
int anglex= 0, angley = 0, anglez = 0;		//rotation angles

void init(void)
{    
   glClearColor (0.9, 0.9, 0.8, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   float light_ambient[4] = { 0.1, 0.1, 0.1, 1.0 };     // r, g, b, a
   float light_diffuse[4] = { 0.9, 0.8, 0.9, 1.0 };     // r, g, b, a
   float light_position[4] = { 1.0, 1.0, 1.0 , 0.0 };   // x, y, z, w 
   
   glEnable(GL_LIGHTING);
   glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glEnable(GL_LIGHT0);
   
   // enable automatic texture coordinate generation
   glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
   glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
   glEnable(GL_TEXTURE_GEN_S);
   glEnable(GL_TEXTURE_GEN_T);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glEnable(GL_TEXTURE_2D);
}

//rotate the objects
void rotate()
{
   glRotatef( anglex, 1.0, 0.0, 0.0);			//rotate along x-axis
   glRotatef( angley, 0.0, 1.0, 0.0);			//rotate along y-axis	
   glRotatef( anglez, 0.0, 0.0, 1.0);			//rotate along z-axis
}

//arbitrarily draw something
void drawScene()
{
   glDisable(GL_LIGHTING);
   glDisable(GL_TEXTURE_2D);
   glColor3f ( 1, 0, 0 );
   glPointSize ( 8 );
   //draw a red point
   glBegin ( GL_POINT );
      glVertex3f ( 1, 2, 2 );
   glEnd();
   glColor3f ( 0, 1, 0 );
   //draw a green triangle
   glBegin ( GL_TRIANGLES);
      glVertex3f ( 2, 2, -2 );
      glVertex3f ( 2, 3, -3 );
      glVertex3f ( 2, 2, -3 );
   glEnd();
   glColor3f ( 0.1, 0.1, 0.8 );
   //draw a blue teapot at left side
   glPushMatrix();
   glTranslatef( -1.0, -1.0, 2.5 );
   glRotatef( 45, 1, 1, 1 );
   glutSolidTeapot( 1 );
   glPopMatrix(); 
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_LIGHTING);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //blend texture with lighting
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   
   glLoadIdentity();
   gluLookAt ( 0, 0, 0, 5, 0, 0, 0, 0, 1 );	//put camera at center of origin
   glScalef ( 1, -1, 1 );			//flip left-right 
   rotate();
   drawScene();
   
   //Use current framebuffer image as texture
   glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, 500, 500, 0);

   //clear frame buffer to draw sphere with scene
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   //put camera back at the observational point
   gluLookAt ( 5, 0, 0, 0, 0, 0, 0, 0, 1 );	
   rotate();
   drawScene();
   glutSolidSphere( 1.0, 20, 20 );	// draw a sphere with this sphere map
   glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key) {
    case 'x':
      anglex = ( anglex + 3 ) % 360;
      break;
    case 'X':
      anglex = ( anglex - 3 ) % 360;
      break;
    case 'y':
      angley = ( angley + 3 ) % 360;
      break;
    case 'Y':
      angley = ( angley - 3 ) % 360;
      break;
    case 'z':
      anglez = ( anglez + 3 ) % 360;
      break;
    case 'Z':
      anglez = ( anglez - 3 ) % 360;
      break;
    case 'r':
      anglex = angley = anglez = 0;
      break;
    case 27: /* escape */
        glutDestroyWindow(window);
        exit(0);
  }
  glutPostRedisplay();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
    glOrtho(-4.0, 4.0, -4.0 * (GLfloat) h / (GLfloat) w,
            4.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt ( 5, 0, 0, 0, 0, 0, 0, 0, 1 );
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(800, 800);
   glutInitWindowPosition(100, 100);
   window = glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0; 
}

