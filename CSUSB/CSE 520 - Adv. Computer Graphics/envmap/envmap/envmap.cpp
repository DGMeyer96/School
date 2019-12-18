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
#include <SOIL/SOIL.h>
using namespace std;

/*
   Global handles for the currently active program object, with its two shader objects
*/
static GLint win = 0;
Shader shader;

int texImageWidth;
int texImageHeight;
int objImageWidth;
int objImageHeight;

int anglex = 0, angley = 0, anglez = 0;          //rotation angles
int objectType = 0;
GLuint texName[2];

const int iWidth = 64, iHeight = 64;
static GLubyte checkImage[iHeight][iWidth][4];
void makeCheckImage(void)
{
	int i, j, c;

	for (i = 0; i < iWidth; i++) {
		for (j = 0; j < iHeight; j++) {
			c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 100;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;		//alpha component
		}
	}
}

GLubyte *makeTexImage(char *loadfile)
{
	int i, j, c, width, height;
	unsigned char *texImage;

	/*
	 *      Only works for .png or .tif images.  NULL is returned if errors occurred.
	 *      loadImageRGA() is from imageio library downloaded from Internet.
	 * */
	texImage = SOIL_load_image((char *)loadfile, &width, &height, 0, SOIL_LOAD_RGB);
	texImageWidth = width;
	texImageHeight = height;

	return texImage;
}

GLubyte *makeObjImage(char *loadfile)
{
	int i, j, c, width, height;
	unsigned char *objImage;

	objImage = SOIL_load_image((char *)loadfile, &width, &height, 0, SOIL_LOAD_RGB);
	objImageWidth = width;
	objImageHeight = height;

	return objImage;
}

void init2DTexture()
{
	//GLubyte *objImg, *envImg;
	unsigned char *objImg, *envImg;

	//  makeCheckImage();
	objImg = makeObjImage((char *) "white.png");
	envImg = makeTexImage ((char *) "earth.png");
	//envImg = makeTexImage((char *) "garden.png");

	glGenTextures(2, texName);
	for (int i = 0; i < 2; ++i) {
		glBindTexture(GL_TEXTURE_2D, texName[i]);           //now we work on texName
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		if (i == 0)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, objImageWidth,
				objImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, objImg);
			SOIL_free_image_data(objImg);
		}
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth,
		 //         iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, checkImage );
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texImageWidth,
				texImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, envImg);
			SOIL_free_image_data(objImg);
		}
	}
}

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

	shader.readShaderFile((char *) "envmap.vert", &VertexShaderSource);
	shader.readShaderFile((char *) "envmap.frag", &FragmentShaderSource);

	vs = new string(VertexShaderSource);
	fs = new string(FragmentShaderSource);

	loadstatus = shader.createShader(vs, fs);

	init2DTexture();

	delete fs;
	delete vs;
	delete VertexShaderSource;
	delete FragmentShaderSource;

	return loadstatus;
}

void CleanUp(void)
{
	shader.cleanUp();
	glutDestroyWindow(win);
}

static void Reshape(int w, int h)
{
	float vp = 0.8f;
	float aspect = (float)w / (float)h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// glOrtho(-1.0, 1.0, -1.0, 1.0, -10.0, 10.0);
	glFrustum(-vp, vp, -vp / aspect, vp / aspect, 3, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}

static void Key(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		CleanUp();
		exit(0);
		break;
	case 'x':
		anglex = (anglex + 3) % 360;
		break;
	case 'X':
		anglex = (anglex - 3) % 360;
		break;
	case 'y':
		angley = (angley + 3) % 360;
		break;
	case 'Y':
		angley = (angley - 3) % 360;
		break;
	case 'z':
		anglez = (anglez + 3) % 360;
		break;
	case 'Z':
		anglez = (anglez - 3) % 360;
		break;
	case 'r':
		anglex = angley = anglez = 0;
		break;
	case 't':
		objectType = (objectType + 1) % 3;
		break;
	}
	glutPostRedisplay();
}

void display(void)
{
	GLfloat vec[4];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1, 0.1, 0.1, 1.0);		//get background color

	glPushMatrix();
	glRotatef(anglex, 1.0, 0.0, 0.0);                   //rotate the cube along x-axis
	glRotatef(angley, 0.0, 1.0, 0.0);                   //rotate along y-axis   
	glRotatef(anglez, 0.0, 0.0, 1.0);                   //rotate along z-axis 

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texName[1]);

	GLUquadric *qobj = gluNewQuadric();
	//  glutSolidSphere(), glutSolidTorus() do NOT have texture coordinates
	gluQuadricTexture(qobj, GL_TRUE);
	if (objectType == 0)
		gluSphere(qobj, 0.6, 32, 32);
	else if (objectType == 1) {
		glTranslatef(0, 0.6, 0);
		glRotatef(90, 1, 0, 0);
		//glutSolidSphere( 1.0, 32, 32);		//, glutSolidTorus() do NOT have texture coordinates
		gluCylinder(qobj, 0.5, 0.5, 1.2, 32, 32);		//top, base height
	}
	else
		glutSolidSphere(1.0, 32, 32);		//, glutSolidTorus() do NOT have texture coordinates
		// glutSolidTeapot(0.6f);				//has texture coordinates
	gluDeleteQuadric(qobj);

	glPopMatrix();
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

	// Initialize the "OpenGL Extension Wrangler" library
	glewInit();

	//success = init();
	//printf("\nsuccess=%d\n", success);
	//if (success)
		glutMainLoop();
	return 0;
}

