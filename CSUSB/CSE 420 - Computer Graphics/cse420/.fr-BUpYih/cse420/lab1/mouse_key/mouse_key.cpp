//Daniel Meyer
//CSE 420
//Fall 2018

//mouse_key.cpp 
#include <GL/glut.h>
#include <stdlib.h>


#define   screenHeight  500

//initialization
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);	//get white background color
	glColor3f(0.0f, 0.0f, 0.0f);	//set drawing color
	glPointSize(4.0);			//a dot is 4x4
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
} //init

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();
}

void drawDot(int x, int y)
{
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2i(x + 75, y + 37);		//draw a points
	glEnd();
} //drawDot

void drawTriangle(int x, int y)
{
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);				//start drawing lines for triangle
	glVertex2i(x, y);				//point 1
	glVertex2i(x + 75, y + 75);		//point 1 -> point 2
	glVertex2i(x + 75, y + 75);		//point 2
	glVertex2i(x + 150, y);			//point 2 -> point 3
	glVertex2i(x + 150, y);			//point 3 
	glVertex2i(x, y);				//point 3 -> point 1
	glEnd();
} //drawTriangle

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{ 
		drawDot(x, screenHeight - y);
		drawTriangle(x, screenHeight - y);
	}
	
	glFlush();				//send all output to screen
}

void myMovedMouse(int mouseX, int mouseY)
{
	GLint x = mouseX;
	GLint y = screenHeight - mouseY;
	GLint brushsize = 12;
	glColor3f(0.5, 0.0, 0.5);
	glRecti(x, y, x + brushsize, y + brushsize);
	glFlush();
} //myMovedMouse

void myKeyboard(unsigned char key, int mouseX, int mouseY)
{
	GLint x = mouseX;
	GLint y = screenHeight - mouseY;
	switch (key)
	{
	case 'p':
		drawDot(x, y);
		break;
	case 'e':
		exit(-1);
	default:
		break;
	}
}