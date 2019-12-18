//draw.cpp : demo program for drawing 3 dots, two lines, ploylines, rectangles
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//initialization
void init( void )
{
  glClearColor( 1.0, 1.0, 1.0, 0.0 );	//get white background color
  glColor3f( 0.0f, 1.0f, 0.0f );	//set drawing color
  glPointSize( 8.0 );			//a dot is 4x4
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();			//replace current matrix with identity matrix
  gluOrtho2D( 0.0, 5.0, 0.0, 5.0 );
}

void draw()
{
  glColor3f ( 0.0, 1.0, 0.0 );
  glBegin( GL_POINTS );			//draw points
    glVertex2f( 1, .5 );		//draw a point
    glVertex2f( 1, 1.5 );		//draw a point
    glVertex2f( 2, 2 );		//draw a point
  glEnd();
  glColor3f ( 1.0, 0.0, 0.0 );
  glBegin( GL_LINES );			//draw lines
    glVertex2f( .2, .2 );		//horizontal line
    glVertex2f( 4, .2 );
    glVertex2f( .2, .1 );		//vertical line
    glVertex2f( .2, 4 );
  glEnd();
  glColor3f ( 0.0, 0.0, 1.0 );
  glBegin( GL_LINE_STRIP );		//draw polyline
    glVertex2f( 2, 1 );
    glVertex2f( 3, 1 );
    glVertex2f( 4.5, 2. );
    glVertex2f( 2., 1. );
  glEnd();

  glColor3f( 0.6, 0.6, 0.6 );		//bright grey
  glRectf( 4, 4, 4.5, 4.8 );
  glColor3f( 1.0, 0.0, 0.0 );		//red
  glRecti( 3.5, 3.5, 3.8, 3.9 );
}


void display( void )
{
  glClear( GL_COLOR_BUFFER_BIT );	//clear screen
  glColor3f ( 0.0, 1.0, 0.0 );

  glViewport ( 0, 0, 250, 250 );
  draw();

  glEnable ( GL_SMOOTH );
  glEnable ( GL_POINT_SMOOTH );
  glLineWidth ( 8 );
  glViewport ( 250, 250, 250, 250 );
  draw();

  glViewport ( 300, 150, 50, 50 );
  draw();
  
  glViewport ( 125, 125, 250, 250 );
  draw();
  glFlush();				//send all output to screen
}

void keyboard ( unsigned char key, int mouseX, int mouseY )
{
  switch( key )
  {
    case 'e':
    case 27:    // escape key, 
        exit ( -1 );
    default :
        break;
  }
}


/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, depth buffer.
 */
int main(int argc, char** argv)
{
  glutInit(&argc, argv);	//initialize toolkit
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB );	//set display mode: single bufferring, RGB model
  glutInitWindowSize(800, 500);		//set window size on screen
  glutInitWindowPosition( 700, 150 ); 	//set window position on screen
  //glutCreateWindow(argv[0]);		//open screen window
  glutCreateWindow( "CS 420 Draw" );		//open screen window
  init();
  glutDisplayFunc (display);		//points to display function
  glutKeyboardFunc ( keyboard );
  glutMainLoop();			//go into perpetual loop
  return 0;
}


