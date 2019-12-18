//demo_canvas.cpp
#include "canvas.h"

Canvas cvs(640, 480, "try out Canvas"); //global canvas object


void dragon( int n )
{
  if (n == 0)
    cvs.forward(.2,1);
  else {
    dragon (n-1);
    cvs.turn(-90);
    for (int i = n-2; i >= 0; i--) {
      dragon(i);
      cvs.turn(90);
    }
    cvs.forward(.2,1);
  }  
}

void display(void)
{
  cvs.clearScreen();
  cvs.setBackgroundColor(0, 0, 0);
  cvs.setColor(1.0, 0.5, 0);
  cvs.moveTo(-2.0, 0.0);
  cvs.turnTo ( 90.0 );  
  dragon ( 10 );
}

/*
void display()
{
  cvs.clearScreen();	//clear screen
  cvs.setColor ( 1.0, 0.0, 0.0 );
  cvs.moveTo( 0, 0.0 ); //draw line
  cvs.lineTo( 5, 5.0 );
  cvs.setColor ( 0.0, 1.0, 0.0 );

  glFlush();
}

*/
