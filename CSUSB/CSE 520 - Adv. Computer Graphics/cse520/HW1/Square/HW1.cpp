/*
   main.cpp
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Shader.h"

using namespace std;

#define PI 3.14159265359

class Point2 {
public:
	float x;
	float y;
	Point2()
	{
		x = y = 0;
	}
	Point2(float x0, float y0)
	{
		x = x0;     y = y0;
	}
	Point2(const Point2 &p)
	{
		x = p.x;
		y = p.y;
	}
};

/*
   Global handles for the currently active program object, with its two shader objects
*/
static GLint win = 0;
Shader shader;

int cLoc;	//color
int rLoc;	//rotation
int sLoc;	//scale

float rx = 0.0;
float ry = 0.0;
float rz = 0.0;

float scale = 1.0;
int colorSelect = 0;
float color[] = { 1.0, 0.0, 1.0, 1.0 };

Point2 A[10], B[10];

int init(void)
{
	const char *version;
	char *VertexShaderSource, *FragmentShaderSource;
	string *vs, *fs;
	int loadstatus = 0;

	version = (const char *)glGetString(GL_VERSION);
	if (version[0] < '2' || version[1] != '.') {
		printf("This program requires OpenGL > 2.x, found %s\n", version);
		exit(1);
	}
	printf("version=%s\n", version);

	shader.readShaderFile((char *) "Square.vert", &VertexShaderSource);
	shader.readShaderFile((char *) "Square.frag", &FragmentShaderSource);

	vs = new string(VertexShaderSource);
	fs = new string(FragmentShaderSource);

	loadstatus = shader.createShader(vs, fs);

	delete fs;
	delete vs;
	delete VertexShaderSource;
	delete FragmentShaderSource;

	cLoc = glGetAttribLocation(shader.programObject, "vColor");
	rLoc = glGetAttribLocation(shader.programObject, "rotate");

	return loadstatus;
}

static void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 5.0, 25.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -15.0f);
}

void CleanUp(void)
{
	shader.cleanUp();
	glutDestroyWindow(win);
}

static void Idle(void)
{
	float t = glutGet(GLUT_ELAPSED_TIME);
	if (anim == 0)
	{
		while (t > 2000) t -= 2000;

	}
	else if (anim == 1)
	{
		t = 0;
	}
	else 
	{
		t = 2000;
	}

	glUniform1f(tLoc, t);
	glutPostRedisplay();
}

void animate()
{
	if (rz < 360)
	{
		rz += 2.0 * (PI / 180);	//need to convert degree to radians for GLSL
	}
	else
	{
		rz = 0.0;
	}
}

static void Key(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		CleanUp();
		exit(0);
		break;
	case 'a':
		animate();
		break;
	}
	glutPostRedisplay();
}

void display(void)
{

	GLfloat vec[4];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);	//get white background color
	glColor3f(0, 0, 1);  		//red, this will have no effect if shader is loaded
	/*
	glLineWidth(4);
	glBegin(GL_LINE_STRIP);  //need GL_POINTS; "GL_POINT" doesn't work
	for (float x = -3.0; x <= 3.0; x += 0.1)
		glVertex3f(x, 0, 0);
	glEnd();
	*/
	
	glVertexAttrib3f(rLoc, rx, ry, rz);
	glVertexAttrib4f(cLoc, color[0], color[1], color[2], color[3]);
	glBegin(GL_QUADS);
		glVertex3f(-2.2, -2.2, 0);
		glVertex3f(2.2, -2.2, 0);
		glVertex3f(2.2, 2.2, 0);
		glVertex3f(-2.2, 2.2, 0);
	glEnd();
	
	glutSwapBuffers();
	glFlush();
}


int main(int argc, char *argv[])
{
	int success = 0;

	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	win = glutCreateWindow(argv[0]);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Key);
	glutDisplayFunc(display);
	glutIdleFunc(Idle);

	// Initialize the "OpenGL Extension Wrangler" library
	glewInit();

	success = init();
	if (success)
	{
		printf("Shaders compiled successfully!\n");
		glutMainLoop();
	}
	else
	{
		printf("infoLog:: %s\n", shader.infoLog);
	}
	return 0;
}

