/*
   main.cpp
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Shader.h"

using namespace std;

#define PI 3.14159265359

/*
   Global handles for the currently active program object, with its two shader objects
*/
static GLint win = 0;
Shader shader;

//bool mouseDown = false;
int mouseDown = 0;

float xrot = 0.0;
float yrot = 0.0;
float zrot = 0.0;

float xdiff = 0.0;
float ydiff = 0.0;
float zdiff = 0.0;

const int screenWidth = 500;
const int screenHeight = 500;
float anglex = 0, angley = 0, anglez = 0;          //rotation angles

int rLoc;
int cLoc;


// Vertex co-ordinate vectors for the tetrahedron.
static float vertices[] =
{
	 1.0,  1.0,  1.0, // V0
	-1.0,  1.0, -1.0, // V1
	 1.0, -1.0, -1.0, // V2
	-1.0, -1.0,  1.0  // v3
};

// Vertex indices for the four trianglular faces.
static int triangleIndices[4][3] =
{
	{1, 2, 3}, // F0
	{0, 3, 2}, // F1
	{0, 1, 3}, // F2
	{0, 2, 1}  // F3
};

int init(void)
{
	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

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

	shader.readShaderFile((char *) "Lab4.vert", &VertexShaderSource);
	shader.readShaderFile((char *) "Lab4.frag", &FragmentShaderSource);

	vs = new string(VertexShaderSource);
	fs = new string(FragmentShaderSource);

	loadstatus = shader.createShader(vs, fs);

	delete fs;
	delete vs;
	delete VertexShaderSource;
	delete FragmentShaderSource;

	rLoc = glGetAttribLocation(shader.programObject, "rotate");
	cLoc = glGetAttribLocation(shader.programObject, "vColor");

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
	glutPostRedisplay();
}


static void Key(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		CleanUp();
		exit(0);
		break;
	case 'x':
		anglex += 2.0 * (PI / 180);
		break;
	case 'X':
		anglex -= 2.0 * (PI / 180);
		break;
	case 'y':
		angley += 2.0 * (PI / 180);
		break;
	case 'Y':
		angley -= 2.0 * (PI / 180);
		break;
	case 'z':
		anglez += 2.0 * (PI / 180);
		break;
	case 'Z':
		anglez -= 2.0 * (PI / 180);
		break;
	case 'r':
		anglex = angley = anglez = 0;
		break;
	}
	glutPostRedisplay();
}

void display(void)
{
	GLfloat vec[4];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);	//get white background color

	/*
	glRotatef(anglex, 1.0, 0.0, 0.0);                   //rotate the cube along x-axis
	glRotatef(angley, 0.0, 1.0, 0.0);                   //rotate along y-axis   
	glRotatef(anglez, 0.0, 0.0, 1.0);                   //rotate along z-axis 
	*/

	//glVertexAttrib3f(rLoc, anglex, angley, anglez);
	glVertexAttrib3f(rLoc, xrot * 0.1, yrot * 0.1, anglez);
	// Draw tetrahedron.
	
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 4; ++i)
	{
		glVertexAttrib4f(cLoc, 1.0, 0.0, 0.0, 1.0);
		glArrayElement(triangleIndices[i][0]);
		glVertexAttrib4f(cLoc, 1.0, 1.0, 0.0, 1.0);
		glArrayElement(triangleIndices[i][1]);
		glVertexAttrib4f(cLoc, 1.0, 0.0, 1.0, 1.0);
		glArrayElement(triangleIndices[i][2]);
	}
	glEnd();
	

	/*
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 4; ++i)
	{
		glVertexAttrib4f(cLoc, 0.8, 0.2, 0.0, 1.0);
		glArrayElement(triangleIndices[i][0]);
	}
	glEnd();

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 4; ++i)
	{
		glVertexAttrib4f(cLoc, 0.2, 0.8, 0.0, 1.0);
		glArrayElement(triangleIndices[i][1]);
	}
	glEnd();

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 4; ++i)
	{
		glVertexAttrib4f(cLoc, 0.0, 0.0, 1.0, 1.0);
		glArrayElement(triangleIndices[i][2]);
	}
	glEnd();
	*/

	glLineWidth(4);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 4; ++i)
	{
		glVertexAttrib4f(cLoc, 1.0, 1.0, 1.0, 1.0);
		glArrayElement(triangleIndices[i][0]);
		glVertexAttrib4f(cLoc, 1.0, 1.0, 1.0, 1.0);
		glArrayElement(triangleIndices[i][1]);
		glVertexAttrib4f(cLoc, 1.0, 1.0, 1.0, 1.0);
		glArrayElement(triangleIndices[i][2]);
	}
	glEnd();

	glutSwapBuffers();
	glFlush();
}

void movedMouse(int mouseX, int mouseY)
{

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//mouseDown = true;
		mouseDown = 1;
		xdiff = x - yrot;
		//ydiff = -y + xrot;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//mouseDown = true;
		mouseDown = 2;
		ydiff = -y + xrot;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		mouseDown = 3;
		//zdiff = x - zrot;
		anglez += 5.0 * (PI / 180);
	}
	else
	{
		mouseDown = 0;
		//mouseDown = false;
	}
		
}

void mouseMotion(int x, int y)
{
	if (mouseDown == 1)
	{
		yrot = x - xdiff * (PI / 180);
		//xrot = y + ydiff * (PI / 180);

		//glutPostRedisplay();
	}
	else if (mouseDown == 2)
	{
		xrot = y + ydiff * (PI / 180);
	}
	else if (mouseDown == 3)
	{
		zrot = x - zdiff * (PI / 180);
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	int success = 0;

	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	win = glutCreateWindow(argv[0]);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Key);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutDisplayFunc(display);
	//glutIdleFunc(Idle);

	// Initialize the "OpenGL Extension Wrangler" library
	glewInit();

	success = init();
	if (success)
		glutMainLoop();
	else
	{
		printf("infoLog:: %s\n", shader.infoLog);
	}
	return 0;
}

