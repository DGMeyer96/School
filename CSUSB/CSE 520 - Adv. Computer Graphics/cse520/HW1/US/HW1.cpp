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

/*
   Global handles for the currently active program object, with its two shader objects
*/
static GLint win = 0;
Shader shader;

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

	shader.readShaderFile((char *) "US.vert", &VertexShaderSource);
	shader.readShaderFile((char *) "US.frag", &FragmentShaderSource);

	vs = new string(VertexShaderSource);
	fs = new string(FragmentShaderSource);

	loadstatus = shader.createShader(vs, fs);

	//Set up initial uniform values
	GLchar names[][20] = { "CoolestColor", "HottestColor", "CoolestTemp",
	"TempRange" };
	GLint loc[10];
	for (int i = 0; i < 4; ++i) {
		loc[i] = glGetUniformLocation(shader.programObject, names[i]);
		if (loc[i] == -1)
			printf("No such uniform named %s\n", names[i]);
	}

	glUniform3f(loc[0], 0.0, 1.0, 0.0);
	glUniform3f(loc[1], 1.0, 1.0, 1.0);
	glUniform1f(loc[2], 0.0);
	glUniform1f(loc[3], 1.0);	

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
	while (t > 3000) t -= 3000;
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

	loc = glGetAttribLocation(shader.programObject, "VertexTemp");
	glBegin(GL_POLYGON);
	if (loc == -1)
		printf("No such attribute named %s\n", "VertexTemp");

	//0.0 = coldest, 1.0 = hottest

	glVertexAttrib1f(loc, 0.6);
	glVertex3f(-2.0, -1.2, 0);
	glVertexAttrib1f(loc, 0.8);
	glVertex3f(-1.0, -1.5, 0);
	glVertexAttrib1f(loc, 1.0);
	glVertex3f(0.0, -2.2, 0);
	glVertexAttrib1f(loc, 0.8);
	glVertex3f(1.2, -1.7, 0);
	glVertexAttrib1f(loc, 1.0);
	glVertex3f(1.7, -2.2, 0);
	glVertexAttrib1f(loc, 0.8);
	glVertex3f(1.7, -1.5, 0);
	glVertexAttrib1f(loc, 0.8);
	glVertex3f(2.2, -0.5, 0);
	glVertexAttrib1f(loc, 0.6);
	glVertex3f(2.0, -0.7, 0);
	glVertexAttrib1f(loc, 0.4);
	glVertex3f(2.4, 1.0, 0);
	glVertexAttrib1f(loc, 0.0);
	glVertex3f(2.1, 1.6, 0);
	glVertexAttrib1f(loc, 0.4);
	glVertex3f(1.5, 0.5, 0);
	glVertexAttrib1f(loc, 0.2);
	glVertex3f(1.0, 1.0, 0);
	glVertexAttrib1f(loc, 0.2);
	glVertex3f(-2.0, 1.0, 0);
	glVertexAttrib1f(loc, 0.0);
	glVertex3f(-2.0, 1.0, 0);
	glVertexAttrib1f(loc, 0.6);
	glVertex3f(-2.2, 0.5, 0);


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

