#include <Windows.h>
#include <iostream>
#include <math.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/GLUT.h>

class GLintPoint
{
public:
	GLint x, y;
};

class Point2
{
public:
	float x, y;
	void set(float dx, float dy) { x = dx; y = dy; }
	void set(Point2 &p) { x = p.x; y = p.y; }
	Point2(float xx, float yy) { x = xx; y = yy; }
	Point2() { x = y = 0; }
};

Point2 currPos;
Point2 CP;

const float pi = 3.14159265358979;

void moveTo(Point2 p)
{
	CP.set(p);
}

void moveTo(float x, float y)
{
	CP.set(x, y);
}

void lineTo(Point2 p)
{
	glBegin(GL_LINES);

	glVertex2f(CP.x, CP.y);
	glVertex2f(p.x, p.y);

	glEnd();
	glFlush();
	CP.set(p);
}

void lineTo(float x, float y)
{
	glBegin(GL_LINES);

	glVertex2f(CP.x, CP.y);
	glVertex2f(x, y);

	glEnd();
	glFlush();
	CP.set(x, y);
}

void myInit(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
}

//---------------- setWindow ---------------
void setWindow(float left, float right, float bottom, float top)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D((GLdouble)left, (GLdouble)right, (GLdouble)bottom, (GLdouble)top);
}

//---------------- setViewport --------------
void setViewport(int left, int right, int bottom, int top)
{
	glViewport(left, bottom, right - left, top - bottom);
}

//draw an n-sided regular polygon
void draw_polygon(int N, float cx, float cy, float radius, float rotAngle)
{
	if (N < 3) return;				//bad number of sides
	//Point2 *pointlist = new Point2[N];
	//GLfloat theta = (2.0f * pi) / N;

	double angle = rotAngle * pi / 180;	//initial angle
	double theta = 2 * pi / N;		//angle increment

	moveTo(radius * cos(angle) + cx, radius * sin(angle) + cy);

	for (int k = 0; k < N; k++) //repeat n times
	{
		angle += theta;
		lineTo(radius * cos(angle) + cx, radius * sin(angle) + cy);
	}
} //draw_polygon

void rosette(int N, float radius)
{
	Point2 *pointlist = new Point2[N];
	GLfloat theta = (2.0f * pi) / N;

	for (int c = 0; c < N; c++)
	{
		pointlist[c].set(radius * sin(theta * c), radius * cos(theta * c));
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			moveTo(pointlist[i]);
			lineTo(pointlist[j]);
		}
	}
}

void draw_circle(float cx, float cy, float radius)
{
	glColor3f(1.0, 0.0, 0.0);

	const int numVerts = 100;
	draw_polygon(numVerts, cx, cy, radius, 0);
	glPointSize(3);

	glFlush();
}

void draw_arc(float cx, float cy, float radius, float sAngle, float sweep)
{
	glColor3f(0.0, 1.0, 0.0);

	const int n = 30;
	float angle = sAngle * pi / 180;
	float theta = sweep * pi / (180 * n);
	
	moveTo(cx + radius * cos(angle), cy + radius * sin(angle));

	for (int i = 1; i < n; i++)
	{
		lineTo(cx + radius * cos(angle), cy + radius * sin(angle));
		angle += theta;
	}
}

void draw_star(float cx, float cy, float radius, float rotAngle)
{
	float angle = rotAngle;
	moveTo(cx + radius * cos(angle), cy + radius * sin(angle));
	
	for (int i = 0; i <= 5; ++i)
	{
		lineTo(cx + radius * cos(0.017453393 * angle), cy + radius * sin(0.017453393 * angle));
		angle += 144;
	}
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	setWindow(-12.0, 12.0, -12.0, 12.0);
	setViewport(0, 500, 0, 500);
	draw_star(8.0, -2.0, 3.0, 55.0);
	draw_polygon(5, 7.0, 5.0, 3.0, 18.0);
	rosette(25, 5.0);
	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutInitWindowSize(640, 480);
	glutCreateWindow("Turtle");
	glutDisplayFunc(render);

	myInit();
	glutMainLoop();
}