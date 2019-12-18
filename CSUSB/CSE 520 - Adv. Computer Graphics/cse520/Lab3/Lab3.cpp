
/*
  Lab3.cpp
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

using namespace std;
#define PI 3.14159265359

/*
   Global handles for the currently active program object, with its two shader objects
*/
GLuint programObject = 0;
GLuint vertexShaderObject = 0;
GLuint fragmentShaderObject = 0;
static GLint win = 0;

int cLoc;
int rLoc;
int sLoc;

float rx = 0.0;
float ry = 0.0;
float rz = 0.0;

float scale = 1.0;
int colorSelect = 0;
float color[] = { 1.0, 0.0, 0.0, 1.0 };

int readShaderSource(char *fileName, GLchar **shader)
{
	// Allocate memory to hold the source of our shaders.
	FILE *fp;
	int count, pos, shaderSize;

	fp = fopen(fileName, "r");
	if (!fp)
		return 0;

	pos = (int)ftell(fp);
	fseek(fp, 0, SEEK_END);			//move to end
	shaderSize = (int)ftell(fp) - pos;	//calculates file size	
	fseek(fp, 0, SEEK_SET); 			//rewind to beginning

	if (shaderSize <= 0) {
		printf("Shader %s empty\n", fileName);
		return 0;
	}

	*shader = (GLchar *)malloc(shaderSize);

	if (*shader == NULL)
		printf("memory allocation error\n");
	// Read the source code

	count = (int)fread(*shader, 1, shaderSize, fp);
	(*shader)[count] = '\0';

	if (ferror(fp))
		count = 0;

	fclose(fp);

	return 1;
}


//  public 
int installShaders(const GLchar *vertex, const GLchar *fragment)
{
	GLint  vertCompiled, fragCompiled;  // status values
	GLint  linked;

	printf("------------\n");
	printf("%s", vertex);
	printf("\n--------------\n");

	printf("------------\n");
	printf("%s", fragment);
	printf("\n--------------\n");

	// Create a vertex shader object and a fragment shader object

	vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	// Load source code strings into shaders, compile and link
	
	glShaderSource(vertexShaderObject, 1, &vertex, NULL);
	glShaderSource(fragmentShaderObject, 1, &fragment, NULL);

	glCompileShader(vertexShaderObject);
	glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &vertCompiled);

	glCompileShader(fragmentShaderObject);
	glGetShaderiv(fragmentShaderObject, GL_COMPILE_STATUS, &fragCompiled);

	printf("vertCompiled, fragCompiled: %d, %d\n", vertCompiled, fragCompiled);
	if (!vertCompiled || !fragCompiled)
		return 0;

	// Create a program object and attach the two compiled shaders

	programObject = glCreateProgram();
	glAttachShader(programObject, vertexShaderObject);
	glAttachShader(programObject, fragmentShaderObject);

	// Link the program object 

	glLinkProgram(programObject);
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

	printf("linked=%d\n");
	if (!linked)
		return 0;

	// Install program object as part of current state

	glUseProgram(programObject);

	return 1;
}


int init(void)
{
	const char *version;
	GLchar *VertexShaderSource, *FragmentShaderSource;
	int loadstatus = 0;

	version = (const char *)glGetString(GL_VERSION);
	if (version[0] < '2' || version[1] != '.') {
		printf("This program requires OpenGL 2.x, found %s\n", version);
		exit(1);
	}

	readShaderSource((char *) "Lab3.vert", &VertexShaderSource);
	readShaderSource((char *) "Lab3.frag", &FragmentShaderSource);

	loadstatus = installShaders(VertexShaderSource, FragmentShaderSource);
	
	cLoc = glGetAttribLocation(programObject, "vColor");
	rLoc = glGetAttribLocation(programObject, "rotate");
	sLoc = glGetAttribLocation(programObject, "VertexScale");

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
	glDeleteShader(vertexShaderObject);
	glDeleteShader(fragmentShaderObject);
	glDeleteProgram(programObject);
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
	case 't':
		if (colorSelect == 0)
		{
			color[0] = 1.0;
			color[1] = 0.0;
			color[2] = 0.0;
			color[3] = 1.0;
			colorSelect++;
			break;
		}
		else if (colorSelect == 1)
		{
			color[0] = 0.0;
			color[1] = 1.0;
			color[2] = 0.0;
			color[3] = 1.0;
			colorSelect++;
			break;
		}
		else if (colorSelect == 2)
		{
			color[0] = 0.0;
			color[1] = 0.0;
			color[2] = 1.0;
			color[3] = 1.0;
			colorSelect++;
			break;
		}
		else
		{
			colorSelect = 0;
			break;
		}
		
	case 'e':
		scale += 0.1;
		break;
	case 'c':
		scale -= 0.1;
		break;
	case 'x':
		rx -= 2.0 * (PI / 180);	//need to convert degree to radians for GLSL
		break;
	case 'X':
		rx += 2.0 * (PI / 180);	//need to convert degree to radians for GLSL
		break;
	case 'y':
		ry -= 2.0 * (PI / 180);	//need to convert degree to radians for GLSL
		break;
	case 'Y':
		ry += 2.0 * (PI / 180);	//need to convert degree to radians for GLSL
		break;
	case 'z':
		rz -= 2.0 * (PI / 180);	//need to convert degree to radians for GLSL
		break;
	case 'Z':
		rz += 2.0 * (PI / 180);	//need to convert degree to radians for GLSL
		break;
	}
	glutPostRedisplay();
}

void display(void)
{
	GLfloat vec[4];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.0);	//get white background color
	glColor3f(1, 0, 0);  		//red, this will have no effect if shader is loaded

	glVertexAttrib3f(rLoc, rx, ry, rz);
	glVertexAttrib1f(sLoc, scale);

	glBegin(GL_TRIANGLES);
	glVertexAttrib4f(cLoc, color[0], color[1], color[2], color[3]);
	glVertex3f(-1.0, 0.5, 0.0);
	glVertex3f(1.0, 0.5, 0.0);
	glVertex3f(0.0, 2.5, 0.0);

	glVertexAttrib4f(cLoc, color[1], color[2], color[0], color[3]);
	glVertex3f(-2.5, -2.0, 0.0);
	glVertex3f(-0.5, -2.0, 0.0);
	glVertex3f(-1.5, 0.0, 0.0);
	
	glVertexAttrib4f(cLoc, color[2], color[0], color[1], color[3]);
	glVertex3f(0.5, -2.0, 0.0);
	glVertex3f(2.5, -2.0, 0.0);
	glVertex3f(1.5, 0.0, 0.0);
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
	printf("success=%d\n", success);
	if (success)
		glutMainLoop();
	return 0;
}