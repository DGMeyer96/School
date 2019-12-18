#include <Windows.h>
#include <iostream>
#include <math.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/GLUT.h>

const float pi = 3.14159265358979;
const float e = 2.7818;

void setWindow(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

void setViewport(GLint left, GLint right, GLint bottom, GLint top)
{
	glViewport(left, bottom, right - left, top - bottom);
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glBegin(GL_LINE_STRIP);
	glBegin(GL_POINTS);

	for (float x = -4.0; x < 4.0; x += 0.01)
	{
		glVertex2f(x, (pow(e, -abs(x)) * sin(2 * pi * x)));
	}

	glEnd();
	glFlush();
}

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glLineWidth(2.0);
	glPointSize(2.0);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("HW1 Graph");
	glutDisplayFunc(myDisplay);
	myInit();
	setWindow(-4.5, 4.5, -1.0, 1.0);
	setViewport(0, 640, 0, 480);
	glutMainLoop();
}