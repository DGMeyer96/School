/*
   main.cpp
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Shader.h"

using namespace std;

#define PI 3.14159265359
#define X .525731112119133606 
#define Z .850650808352039932

/*
   Global handles for the currently active program object, with its two shader objects
*/
static GLint win = 0;
Shader shader;

int pLoc;	//position
int tLoc;	//time
int vLoc;	//velocity

float iVelocityY = 7.0;
float iVelocityX = 1.0;
float iVelocityZ = 0.0;
float iPositionX = -2.0;
float iPositionY = -2.0;
float iPositionZ = 0.0;

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

	shader.readShaderFile((char *) "Ball.vert", &VertexShaderSource);
	shader.readShaderFile((char *) "Ball.frag", &FragmentShaderSource);

	vs = new string(VertexShaderSource);
	fs = new string(FragmentShaderSource);

	loadstatus = shader.createShader(vs, fs);

	vLoc = glGetUniformLocation(shader.programObject, "iVel");
	pLoc = glGetUniformLocation(shader.programObject, "iPos");
	tLoc = glGetUniformLocation(shader.programObject, "time1");

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
	while (t > 5000) t -= 5000;
	glUniform1f(tLoc, t);
	glutPostRedisplay();
}

static void Key(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		CleanUp();
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void display(void)
{
	GLfloat vec[4];
	int loc;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);	//get white background color
	glColor3f(0, 0, 1);  		//red, this will have no effect if shader is loaded

	glUniform3f(pLoc, iPositionX, iPositionY, iPositionZ);
	glUniform3f(vLoc, iVelocityX, iVelocityY, iVelocityZ);
	glutSolidSphere(0.2, 50, 50);
	
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

