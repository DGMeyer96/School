#include "canvas.h"

Canvas cvs(500, 500, (char *) "A Circle"); //global canvas object

float R = 20.0 / 20.0; 

float f ( float x, float r )
{
  if ( x > r ) return r;
  float y = sqrt ( r * r - x * x ); 
}

void display(void)
{
  cvs.clearScreen();    //clear screen
  float r = 5.0;
  glLineWidth ( 4.0 );
  const float pi = 3.14159265;
  glBegin ( GL_LINE_STRIP );
  glVertex2f ( r, 0 );
  for ( float a = -0.1; a <= 2.1*pi; a+=0.1 ){
     float x = r * cos ( a );
    // float y = f (  x, r );
     float y = r * sin ( a ); 
   //  if ( a > pi ) y = -y;
     glVertex2f ( x, y );
  }
  glEnd();
  glFlush();
}

void reshape( int W, int H )
{
  if ( R > W/H ) 	//use global aspect ratio R
    cvs.setViewport( 0, W, 0, W/R );
  else
    cvs.setViewport( 0, H * R, 0, H );
}

