/*
 * spheremap.cpp ( Demo for CS 520 ):  Draw a sphere with texture images. The cube can be rotated
 * by pressing keys 'x', 'X', 'y', 'Y', 'z', 'Z'.
 * Images are downloaded from Internet.  
 * @Author: T.L. Yu, 2008F
 *
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "imageio.h"

int texImageWidth;
int texImageHeight;
int window;
static GLuint texName[6];			//texture names
int anglex= 0, angley = 0, anglez = 0;		//rotation angles


char maps[][20] = {"earth.png"};

typedef struct {
  double x;
  double y;
  double z;
} XYZ; 

//load texture image
GLubyte *makeTexImage( char *loadfile )
{
   int i, j, c, width, height;
   GLubyte *texImage;
  
   /*
     Only works for .png or .tif images.  NULL is returned if errors occurred.
     loadImageRGA() is from imageio library downloaded from Internet.
   */ 
   texImage = loadImageRGBA( (char *) loadfile, &width, &height);	
   texImageWidth = width;
   texImageHeight = height;

   return texImage;
}

void init(void)
{    
   glClearColor (1, 1, 1, 0.0);
   glShadeModel(GL_FLAT);

   glEnable(GL_DEPTH_TEST);

   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
   //texName is global
   glGenTextures(6, texName);

//  for ( int i = 0; i < 6; ++i ) {	
  for ( int i = 0; i < 1; ++i ) {	
    GLubyte *texImage = makeTexImage( maps[i] );
    if ( !texImage ) {
      printf("\nError reading %s \n", maps[i] );
      continue;
    }
    glBindTexture(GL_TEXTURE_2D, texName[i]);		//now we work on texName
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texImageWidth, 
                texImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);

    delete texImage;					//free memory holding texture image
  }
}

#define PI 3.141592654
#define TWOPI 6.283185308

//not used here
void SphereMap( double x, double y, double z, double radius, double *u, double *v)
{
   *v = acos(z/radius) / PI;
   if (y >= 0)
      *u = acos(x/(radius * sin(PI*(*v)))) / TWOPI;
   else
      *u = (PI + acos(x/(radius * sin(PI*(*v))))) / TWOPI;
}

/*
 *    Create a sphere centered at c, with radius r, and precision n
 *    Draw a point for zero radius spheres
 *
 */

void CreateSphere(XYZ c,double r,int n)
{
   int i,j;
   double phi1,phi2,theta, u, v;
   XYZ e,p;

   if (r < 0)
      r = -r;
   if (n < 0)
      n = -n;
   if (n < 4 || r <= 0) {
      glBegin(GL_POINTS);
      glVertex3f(c.x,c.y,c.z);
      glEnd();
      return;
   }

   for (j=0;j < n; j++) {
      phi1 = j * TWOPI / n;
      phi2 = (j + 1) * TWOPI / n;	//next phi

      glBegin(GL_QUAD_STRIP);
      for (i=0;i <= n;i++) {
         theta = i * PI / n;

        e.x = sin ( theta ) * cos ( phi2 );
	e.y = sin ( theta ) * sin ( phi2 );
        e.z = cos ( theta );
        p.x = c.x + r * e.x;
        p.y = c.y + r * e.y;
        p.z = c.z + r * e.z;

        glNormal3f(e.x,e.y,e.z);
        u = (double)(j+1) / n;		// column
 	v = 1 - (double) i / n;		// row
        glTexCoord2f(u, v);
        glVertex3f(p.x,p.y,p.z);

        e.x = sin ( theta ) * cos ( phi1 );
	e.y = sin ( theta ) * sin ( phi1 );
        e.z = cos ( theta );
        p.x = c.x + r * e.x;
        p.y = c.y + r * e.y;
        p.z = c.z + r * e.z;

         glNormal3f(e.x,e.y,e.z);
         u = (double) j / n;		// column
	 v = 1 - (double) i / n;	// row
         glTexCoord2f(j/(double)n, 1-i/(double)n);
         glVertex3f(p.x,p.y,p.z);
      }
      glEnd();
   }
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   glEnable( GL_CULL_FACE );
   glCullFace ( GL_BACK );
  
   glPushMatrix(); 
   glRotatef( anglex, 1.0, 0.0, 0.0);			//rotate the cube along x-axis
   glRotatef( angley, 0.0, 1.0, 0.0);			//rotate along y-axis	
   glRotatef( anglez, 0.0, 0.0, 1.0);			//rotate along z-axis

   glColor3f ( 1, 0, 0 );
   glPointSize ( 6 );
   glBegin ( GL_POINT );
      glVertex3f ( 1, 2, 0 );
   glEnd();
   XYZ c;
   c.x = c.y = c.z = 0.0;

   CreateSphere( c, 3.0 , 40 );

   glPopMatrix();
   glFlush();
   glDisable(GL_TEXTURE_2D);
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
   //gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
    glOrtho(-4.0, 4.0, -4.0 * (GLfloat) h / (GLfloat) w,
            4.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   //gluLookAt ( 0, 0, 5, 0, 0, 0, 0, 1, 0 );
   gluLookAt ( 5, 0, 0, 0, 0, 0, 0, 0, 1 );
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(900, 900);
   glutInitWindowPosition(100, 100);
   window = glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0; 
}
