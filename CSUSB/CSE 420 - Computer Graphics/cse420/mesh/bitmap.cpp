
/*
   bitmap.cpp

   void glBitmap(GLsizei width,  GLsizei height,  GLfloat xorig,  GLfloat yorig,  GLfloat xmove,  GLfloat ymove,  
                      const GLubyte * bitmap); 
		 
   Parameters:  width, height
                    Specify the pixel width and height of the bitmap image.
                xorig, yorig
                    Specify the location of the origin in the bitmap image.
                    The origin is measured from the lower left corner of the bitmap,
                    with right and up being the positive axes.
                xmove, ymove
                    Specify the x and y offsets to be added to the current raster position
                    after the bitmap is drawn.
                bitmap
                    Specifies the address of the bitmap image.
                
 *
 */
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void init(void)
{
  glShadeModel (GL_FLAT);
}

void draw_scene()
{
   glColor4f(0, 0, 0.8, 0.5 );
}

void display(void)
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho (-1.0, 1.0, -1.0, 1.0, -10.0, 10.0);
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glClear (GL_COLOR_BUFFER_BIT );
   glColor4f(0, 0, 0, 0);
   glBegin( GL_LINES );
      glVertex3f(-1, 0, 0 ); 
      glVertex3f(1, 0, 0 ); 
      glVertex3f(0, 1, 0 ); 
      glVertex3f(0, -1, 0 ); 
   glEnd();
   GLubyte arrow[20] = {0x1c, 0x00, 0x1c, 0x00,  0x1c, 0x00,  0x1c, 0x00, 0x1c, 0x00, 
			0xff, 0x80, 0x7f, 0x00, 0x3e, 0x00, 0x1c, 0x00, 0x08, 0x00};
   glPixelStorei (GL_UNPACK_ALIGNMENT, 1);  //set pixel storage mode
   glRasterPos2f( 0.1, 0.2 );
   glBitmap ( 9, 10, 0, 0, 20, 30, arrow );      
   glBitmap ( 9, 10, 0, 0, 20, 30, arrow );      
   glBitmap ( 9, 10, 0, 0, 20, 30, arrow );      
   glBitmap ( 9, 10, 0, 0, 20, 30, arrow );      
   glBitmap ( 9, 10, 0, 0, 20, 30, arrow );      
   glBitmap ( 9, 10, 0, 0, 20, 30, arrow );      
   glBitmap ( 9, 10, 0, 0, -20, 0, arrow );      
   glBitmap ( 9, 10, 0, 0, -20, 0, arrow );      
   glBitmap ( 9, 10, 0, 0, -20, 0, arrow );      
   glBitmap ( 9, 10, 0, 0, -20, 0, arrow );      
   glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
        exit(0);
    }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowSize(500, 500);
   glutCreateWindow(argv[0]);
   init();
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
