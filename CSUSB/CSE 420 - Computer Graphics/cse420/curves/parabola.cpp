#include "canvas.h"

Canvas cvs ( 800, 800, "Turtle" );

void parabola()
{
  cvs.setWindow ( -200, 200, -200, 200 );
  double a = 8, t, x, y;
  
  t = -4;
  y = a * t * t;
  x = 2 * a * t;
  cvs.moveTo ( x, y );

  for ( t = -4; t <= 4; t += 0.1 ) {
    y = a * t * t;
    x = 2 * a * t;
    cvs.lineTo ( x, y );
  }
}
 
void display(void)
{
  cvs.clearScreen();
 
  cvs.moveTo(0.0, 0.0); //starts at center
  cvs.turnTo ( 0.0 );   //points horizontally
  glLineWidth ( 6 );
  parabola();
}
  
