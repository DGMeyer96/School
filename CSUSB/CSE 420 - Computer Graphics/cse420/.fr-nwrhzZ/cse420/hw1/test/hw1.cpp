//bline.cpp : Bresenham Line algorithm, works only for |m| < 1

#include <GL/glut.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "draw.h"
#include "surface.h"

using namespace std;

double f ( double x )
{
  double y = exp ( -fabs ( x ) ) * cos ( 2 * 3.1415926 * x );

  return y;
}

void init(void)
{
  glClearColor(1.0,1.0,1.0,0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0,400.0,0.0,400.0);
}

void setPixel(GLint x,GLint y)
{
  glBegin(GL_POINTS);
     glVertex2i(x,y);
  glEnd();
}

void line()
{
  int x0 = 0, y0= 0, xn = 18, yn = 6, x, y;
  int	dx, dy,		//deltas
	pk,		//decision parameter
  	k;		//looping variable

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f( 1 ,0, 0);  
  setPixel(x0, y0);	//plot first point
  
  // difference between starting and ending points
  dx = xn - x0;
  dy = yn - y0;
  pk = 2 * dy - dx; 
  x = x0;	y = y0; 
  
  for ( k = 0; k < dx-1; ++k ) {
    if ( pk < 0 ) {
      pk = pk + 2 * dy;			//calculate next pk
					//next pixel: (x+1, y )
    } else {
      					//next pixel: (x+1, y+1)
      pk = pk + 2*dy - 2*dx;		//calculate next pk
      ++y;
    }
    ++x;

    cout << "Y: " << y << endl;

    setPixel( x, y );
  }

  glFlush();
}

void plot()
{
  const int VWIDTH = 640;
  const int VHEIGHT = 480;

  const Point center ( VWIDTH/2, VHEIGHT/2 );	//center of screen
  Surface surf( VWIDTH, VHEIGHT, (char *) "HW 1" );

  surf.clearScreen();			//clear screen
  surf.updateSurface();
  SDL_Delay ( 1000 );			//dealy one second, just for demo

  surf.setBackgroundColor ( 0xe0, 0xe0, 0xe0 );	//set background to grey

  //draw a line 
  surf.setColor ( 0xff, 0, 0 );		//using red color

  int sx, sy;
  double x, y, a, b, c, d;
  a = VWIDTH / 4.0;
  c = 0;
  b  = -VHEIGHT / 2.0;
  d  = VHEIGHT / 2.0;


  x = 0.0;                              //initial position
  y = f ( 0.0 );
  sx = (int) ( a * x + c );
  sy = (int) ( b * y + d );
  surf.moveTo ( sx, sy );

  for ( x = 0; x < 4.0; x += 0.005 ) {
    y =  f ( x );
    sx = (int) ( a * x + c );
    sy = (int) ( b * y + d );
    surf.lineTo ( sx, sy );
  }

  surf.updateSurface();
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Bresenham Line");
    init();
    glutDisplayFunc( line );
    glutMainLoop();
    return 0;
}
