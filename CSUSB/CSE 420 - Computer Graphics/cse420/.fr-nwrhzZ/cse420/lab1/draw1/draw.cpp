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
	glClear(GL_COLOR_BUFFER_BIT);	//clear screen
	/*
	glBegin(GL_POINTS);			//draw points
	glVertex2i(100, 50);		//draw a point
	glVertex2i(100, 150);		//draw a point
	glVertex2i(200, 200);		//draw a point
	glEnd();
	*/

	/*
	glBegin(GL_LINES);			//draw lines
	glVertex2i(20, 20);		//horizontal line
	glVertex2i(400, 20);
	glVertex2i(20, 10);		//vertical line
	glVertex2i(20, 400);
	glEnd();
	*/

	/*
	glBegin(GL_LINE_STRIP);		//draw polyline
	glVertex2i(200, 100);
	glVertex2i(300, 100);
	glVertex2i(450, 200);
	glVertex2i(200, 100);
	glEnd();
	*/

	
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
