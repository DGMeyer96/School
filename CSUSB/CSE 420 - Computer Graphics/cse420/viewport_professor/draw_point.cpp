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
  gluOrtho2D( 0.0, 600.0, 0.0, 600.0 );
}

void draw()
{
  glColor3f ( 0.0, 0.0, 0.0 );
  glPointSize ( 16 );
  glBegin( GL_POINTS );			//draw points
    glVertex2i( 100, 50 );		//draw a point
    glVertex2i( 100, 150 );		//draw a point
    glVertex2i( 200, 200 );		//draw a point
  glEnd();
  glColor3f ( 1.0, 0.0, 0.0 );
  glLineStipple(2, 0x3f07 ); 
  glBegin( GL_LINES );			//draw lines
    glVertex2i( 20, 20 );		//horizontal line
    glVertex2i( 400, 20 );
  glEnd();
  glColor3f ( 0.0, 1.0, 0.0 );
  glLineStipple(5, 0x3f07 ); 
  glBegin( GL_LINES );			//draw lines
    glVertex2i( 20, 10 );		
    glVertex2i( 300, 550 );
  glEnd();
  glColor3f ( 0.0, 1.0, 1.0 );
  glLineStipple(2, 0xAAAA ); 
  glBegin( GL_LINES );			//draw lines
    glVertex2i( 20, 200 );		
    glVertex2i( 300, 550 );
  glEnd();
/*
  glColor3f ( 0.0, 0.0, 1.0 );
  glBegin( GL_LINE_STRIP );		//draw polyline
    glVertex2i( 200, 100 );
    glVertex2i( 300, 100 );
    glVertex2i( 450, 200 );
    glVertex2i( 200, 100 );
  glEnd();
*/
}


void display( void )
{
  glClear( GL_COLOR_BUFFER_BIT );	//clear screen
  glEnable ( GL_SMOOTH );
  glEnable ( GL_POINT_SMOOTH );
  glEnable ( GL_LINE_SMOOTH );
  glLineWidth ( 1 );
  glEnable( GL_LINE_STIPPLE );
  draw();


//  glLineWidth ( 8 );
  glFlush();				//send all output to screen
}


/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, depth buffer.
 */
int main(int argc, char** argv)
{
  glutInit(&argc, argv);	//initialize toolkit
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB );	//set display mode: single bufferring, RGB model
  glutInitWindowSize(500, 500);		//set window size on screen
  glutInitWindowPosition( 700, 150 ); 	//set window position on screen
  //glutCreateWindow(argv[0]);		//open screen window
  glutCreateWindow( "CS 420 Draw" );		//open screen window
  init();
  glutDisplayFunc (display);		//points to display function
  glutMainLoop();			//go into perpetual loop
  return 0;
}


