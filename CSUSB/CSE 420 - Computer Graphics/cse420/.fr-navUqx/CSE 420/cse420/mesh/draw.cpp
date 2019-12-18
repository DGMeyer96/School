//draw.cpp : demo program for drawing 3 dots, two lines, ploylines, rectangles
#include <GL/glut.h>

//initialization
void init( void )
{
  glClearColor( 1.0, 1.0, 1.0, 0.0 );	//get white background color
  glColor3f( 0.0f, 1.0f, 0.0f );	//set drawing color
  glPointSize( 8.0 );			//a dot is 4x4
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();			//replace current matrix with identity matrix
  gluOrtho2D( 0.0, 500.0, 0.0, 500.0 );
}

void display( void )
{
  glClear( GL_COLOR_BUFFER_BIT );	//clear screen
	glEnable( GL_CULL_FACE );
  	glCullFace ( GL_BACK );
  	glColor3f( 1.0, 0.0, 0.0 );           //red
   	glFrontFace ( GL_CCW );
//   	glFrontFace ( GL_CW );
  	glPolygonMode( GL_FRONT, GL_FILL );
  	glBegin( GL_POLYGON );                //draw solid polygon
    	  glVertex2i( 0, 0 );
    	  glVertex2i( 0, 100 );
    	  glVertex2i( 100, 100 );
    	  glVertex2i( 100, 0  );
  	glEnd();
/*
  	glBegin( GL_POLYGON );                //draw solid polygon
    	  glVertex2i( 0, 0 );
    	  glVertex2i( 100, 0 );
    	  glVertex2i( 100, 100 );
    	  glVertex2i( 0, 100  );
  	glEnd();
*/
  glFlush();				//send all output to screen
}

void keyboard ( unsigned char key, int mousex, int mousey )
{
  switch ( key ) {
    case 27:
      exit ( -1 );
  }
}
