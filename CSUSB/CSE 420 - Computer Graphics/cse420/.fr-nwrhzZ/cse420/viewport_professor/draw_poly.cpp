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
  gluOrtho2D( -10.0, 400.0, -10.0, 400.0 );
}

void display( void )
{
  glClear( GL_COLOR_BUFFER_BIT );	//clear screen

  glEnable( GL_CULL_FACE );
  glCullFace ( GL_BACK );
 // glCullFace ( GL_FRONT );
  glColor3f( 1.0, 0.0, 0.0 );           //red
 // glFrontFace ( GL_CW );
  glFrontFace ( GL_CCW );

  glDisable( GL_CULL_FACE );

 int x0, y0; 
  glColor3f( 1.0, 0.0, 0.0 );           //red
  glPolygonMode( GL_FRONT, GL_FILL );
  glBegin( GL_POLYGON );                //draw solid polygon
    glVertex2i( 0, 0 );
    glVertex2i( 0, 100 );  
    glVertex2i( 100, 100 );   
    glVertex2i( 100, 0 );  
  glEnd();
//  glFlush();				//send all output to screen

  x0 = 160;
  glColor3f( 0.0, 1.0, 0.0 );           //green
  glPolygonMode( GL_FRONT, GL_LINE );
  glBegin( GL_POLYGON );                //draw polygon
    glVertex2i( x0+10, 10 );
    glVertex2i( x0+100, 10 );
    glVertex2i( x0+150, 50 );
    glVertex2i( x0+100, 100 );
  //  glVertex2i( x0+50, 80 );  
  //  glVertex2i( x0+10, 10 );
  glEnd(); 
  x0 = 80;
  y0 = 120;
  glColor3f( 0.0, 0.0, 1.0 );           //blue
  glPolygonMode( GL_FRONT, GL_POINT );
  glBegin( GL_POLYGON );                //draw polygon points
    glVertex2i( x0+10, y0+10 );
    glVertex2i( x0+100, y0+10 );
    glVertex2i( x0+150, y0+50 ); 
    glVertex2i( x0+100, y0+100 );
  //  glVertex2i( x0+50, y0+80 );
  //  glVertex2i( x0+10, y0+10 );
  glEnd(); 
	   
  glFlush();				//send all output to screen
}
