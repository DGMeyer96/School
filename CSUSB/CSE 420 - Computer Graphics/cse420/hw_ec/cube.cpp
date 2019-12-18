
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>

float ax = 0, ay = 0, az = 0;    // rotations


static GLubyte allIndices[] = { 4, 5, 6, 7, //front
								1, 2, 6, 5,	//right
								0, 1, 5, 4,	//bottom
								0, 3, 2, 1,	//back
								0, 4, 7, 3,	//left
								2, 3, 7, 6 };	//top

static GLint vertices[] = { -1, -1, -1,   //0
							1, -1, -1,
							1, 1, -1,
							-1, 1, -1,        //3
							-1, -1, 1,
							1, -1, 1,
							1, 1, 1,         //6
							-1, 1, 1 };       //7

static GLfloat colors[] = { 0.0, 0.0, 0.0,
							1.0, 0.0, 0.0,
							1.0, 1.0, 0.0,
							0.0, 1.0, 0.0,
							0.0, 0.0, 1.0,
							1.0, 0.0, 1.0,
							1.0, 1.0, 1.0,
							0.0, 1.0, 1.0
};

//0 = black
//1 = red
//2 = yellow
//3 = green
//4 = blue
//5 = magenta
//6 = white
//7 = cyan

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	gluLookAt(3.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(ax, 1, 0, 0);
	glRotatef(ay, 0, 1, 0);
	glRotatef(az, 0, 0, 1);

	glVertexPointer(3, GL_INT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, allIndices);

	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':       // up
		ax += 5;
		break;
	case 'X':       // down
		ax -= 5;
		break;
	case 'y':		//north
		ay += 5;
		break;
	case 'Y':		//south
		ay -= 5;
		break;
	case 'z':		//west
		az -= 5;
		break;
	case 'Z':		//east
		az += 5;
		break;
	case 27:
		exit(0);
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(600, 600);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}