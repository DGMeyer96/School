//Daniel Meyer
//CSE 420
//Fall 2018

//draw.cpp : demo program for drawing 3 dots, two lines, ploylines, rectangles
#include <GL/glut.h>

//initialization

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);	//get white background color
	glColor3f(0.0f, 0.0f, 0.0f);	//set drawing color
	glPointSize(4.0);			//a dot is 4x4
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();			//replace current matrix with identity matrix
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

void display(void)
{
	glViewport(50, 200, 250, 100);
	//glViewport( 0, 0, 50, 50);
	glClear(GL_COLOR_BUFFER_BIT);	//clear screen
	
	glColor3f(0.0, 0.0, 1.0);		//blue rectangle
	glRecti(250, 100, 400, 300);	//draw rectangle
	glColor3f(1.0, 0.0, 0.0);		//red triangle
	glBegin(GL_LINES);				//start drawing lines for triangle
	glVertex2i(50, 50);				//point 1
	glVertex2i(125, 125);			//point 1 -> point 2
	glVertex2i(125, 125);			//point 2
	glVertex2i(200, 50);			//point 2 -> point 3
	glVertex2i(200, 50);			//point 3 
	glVertex2i(50, 50);				//point 3 -> point 1
	glEnd();						//stop drawing	

	glFlush();				//send all output to screen
}
