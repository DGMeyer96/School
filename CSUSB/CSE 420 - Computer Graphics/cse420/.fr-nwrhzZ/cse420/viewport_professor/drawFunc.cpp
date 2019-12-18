//draw.cpp : demo program for drawing 3 dots, two lines, ploylines, rectangles
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

const int ScreenWidth = 500, ScreenHeight = 500;   //in pixels
//initialization
void init( void )
{
  glClearColor( 1.0, 1.0, 1.0, 0.0 );	//get white background color
  glColor3f( 0.0f, 1.0f, 0.0f );	//set drawing color
  glEnable ( GL_SMOOTH );
  glEnable ( GL_POINT_SMOOTH );
  glEnable ( GL_LINE_SMOOTH );
  glPointSize( 16.0 );			//a dot is 4x4
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();			//replace current matrix with identity matrix
  // default world window is ( -1.0, 1.0, -1.0, 1.0 );
//  gluOrtho2D( 0, ScreenWidth, 0, ScreenHeight );
 //gluOrtho2D( -ScreenWidth, ScreenWidth, -ScreenHeight, ScreenHeight );
  gluOrtho2D ( -4.0, 4.0, -1.0, 1.0 );
}

void screen2Win ( int x, int y, double &xw, double &yw )
{
  double worldWidth = 4 - (-4);
  double worldHeight = 1 - (-1);
  xw = -4.0 + worldWidth / ScreenWidth * x;
  yw = -1.0 + worldHeight / ScreenHeight * y;
}
void drawDot( double x, double y )
{
  glBegin( GL_POINTS );                 
    glVertex2d( x, y );         //draw a points
  glEnd();
} //drawDot

void myMouse( int button, int state, int x, int y )
{
  double xw, yw;
  if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
    y = ScreenHeight - y;
    screen2Win ( x, y, xw, yw );  
    drawDot( xw, yw );
  }
  glFlush();                            //send all output to Screen
}


double f ( double x )
{
  double y = exp ( -fabs ( x ) ) * cos ( 2 * 3.1415926 * x );

  return y;
}

void draw()
{
  double y;
  glBegin( GL_LINE_STRIP );
  for (  double x = -4.0; x < 4.0; x += 0.005 ) {
    y =  f ( x );
    glVertex2d ( x, y );
  }
  glEnd();

}


void display( void )
{
  glClear( GL_COLOR_BUFFER_BIT );	//clear Screen
  glColor3f ( 0.0, 0.0, 0.0 );
  draw();

  glFlush();				//send all output to Screen
}


/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, depth buffer.
 */
int main(int argc, char** argv)
{
  glutInit(&argc, argv);	//initialize toolkit
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB );	//set display mode: single bufferring, RGB model
  glutInitWindowSize(ScreenWidth, ScreenHeight);		//set window size on Screen
  glutInitWindowPosition( 700, 150 ); 	//set window position on Screen
  //glutCreateWindow(argv[0]);		//open Screen window
  glutCreateWindow( "CS 420 Draw" );		//open Screen window
  init();
  glutDisplayFunc (display);		//points to display function
  glutMouseFunc ( myMouse );
  glutMainLoop();			//go into perpetual loop
  return 0;
}


