//bline.cpp : Bresenham Line algorithm, works only for |m| < 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <GL/glut.h>

const float pi = 3.14159265358979;
const float e = 2.71828;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-5.0, 20.0, -5.0, 20.0);
	glPointSize(3.0);
}

void setPixel(GLint x, GLint y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void line()
{
	int x0 = 0, y0 = 0, xn = 18, yn = 6, x, y;
	int	dx, dy,		//deltas
		pk,		//decision parameter
		k;		//looping variable

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	setPixel(x0, y0);	//plot first point

	// difference between starting and ending points
	dx = xn - x0;
	dy = yn - y0;
	pk = 2 * dy - dx;
	x = x0;	y = y0;

	for (k = 0; k < dx - 1; ++k) 
	{
		std::cout << "p" << k << " = " << pk << std::endl;
		//std::cout << "( " << x << " , " << y << " )" << std::endl;
		if (pk < 0) {
			pk = pk + 2 * dy;			//calculate next pk
						  //next pixel: (x+1, y )
			std::cout << "X" << std::endl;
			std::cout << "( " << x << " , " << y << " )" << std::endl;
		}
		else {
			//next pixel: (x+1, y+1)
			pk = pk + 2 * dy - 2 * dx;		//calculate next pk
			std::cout << "XY" << std::endl;
			std::cout << "( " << x << " , " << y << " )" << std::endl;
			++y;
		}
		++x;

		
		setPixel(x, y);
	}

	glFlush();
}

void myInit()
{
	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(3.0);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(250, 250);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Bresenham Line");
	init();
	glutDisplayFunc(line);
	glutMainLoop();
	return 0;
}