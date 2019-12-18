//draw.cpp : demo program for drawing 3 dots, two lines, ploylines, rectangles
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const int ScreenWidth = 500, ScreenHeight = 500;   //in pixels
//initialization
void init( void )
{
  glClearColor( 1.0, 1.0, 1.0, 0.0 );	//get white background color
  glColor3f( 0.0f, 1.0f, 0.0f );	//set drawing color
  glEnable ( GL_SMOOTH );
  glEnable ( GL_POINT_SMOOTH );
  //glEnable ( GL_LINE_SMOOTH );
  glPointSize( 16.0 );			//a dot is 4x4
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();			//replace current matrix with identity matrix
  gluOrtho2D( 0.0, 600.0, 0.0, 600.0 );
//  gluOrtho2D( -600.0, 600.0, -600.0, 600.0 );
 // gluOrtho2D( 0.0, ScreenWidth-1, 0.0, ScreenHeight-1 );
}

void draw()
{
  glColor3f ( 0.0, 1.0, 0.0 );
  glBegin( GL_POINTS );			//draw points
    glVertex2i( 100, 50 );		//draw a point
    glVertex2i( 100, 150 );		//draw a point
    glVertex2i( 200, 200 );		//draw a point
  glEnd();

  glColor3f ( 1.0, 0.0, 0.0 );
  glBegin( GL_LINES );			//draw lines
    glVertex2i( 0,0 );
    glVertex2i (500,  200 );
    glVertex2i( 0, ScreenHeight - 1 );
    glVertex2i ( ScreenWidth - 1, 0 );
  glEnd();
  glColor3f ( 0.0, 0.0, 1.0 );
  glBegin( GL_LINE_STRIP );		
    glVertex2i( 200, 100 );
    glVertex2i( 300, 100 );
    glVertex2i( 450, 200 );
    glVertex2i( 350, 500 );
  glEnd();

  glColor3f ( 1.0, 0.0, 1.0 );
  glLineWidth ( 4 );
  glBegin( GL_LINE_LOOP );		
    glVertex2i( 100, 100 );
    glVertex2i( 200, 100 );
    glVertex2i( 350, 200 );
    glVertex2i( 250, 500 );
  glEnd();
  return;
/*
  glBegin( GL_POLYGON );		
    glVertex2i( 100, 100 );
    glVertex2i( 200, 100 );
    glVertex2i( 350, 200 );
    glVertex2i( 250, 500 );
  glEnd();
*/

  glBegin( GL_TRIANGLES );		
    glVertex2i( 100, 100 );
    glVertex2i( 200, 100 );
    glVertex2i( 350, 200 );
    glVertex2i( 250, 500 );
    glVertex2i( 100, 100 );
    glVertex2i( 200, 100 );
  glEnd();

/*
  glColor3f( 0.6, 0.6, 0.6 );		//bright grey
  glRecti( 400, 400, 450, 480 );
  glColor3f( 1.0, 0.0, 0.0 );		//red
  glRecti( 350, 350, 380, 390 );
*/
}


void display( void )
{
  glClear( GL_COLOR_BUFFER_BIT );	//clear screen
  glColor3f ( 0.0, 1.0, 0.0 );
  glViewport ( 0, 0, 600, 600 );
  draw();
  /*
  glViewport ( 0, 0, 250, 250 );
  draw();
  glViewport ( 100, 400, 200, 100 );
  draw();
  glViewport ( 200, 250, 50, 50 );
  draw();
*/
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
  glutInitWindowSize(ScreenWidth, ScreenHeight);		//set window size on screen
  glutInitWindowPosition( 700, 150 ); 	//set window position on screen
  //glutCreateWindow(argv[0]);		//open screen window
  glutCreateWindow( "CS 420 Draw" );		//open screen window
  init();
  glutDisplayFunc (display);		//points to display function
  glutMainLoop();			//go into perpetual loop
  return 0;
}


