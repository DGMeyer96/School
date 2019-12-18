//robot.cpp
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <GL/glut.h>

/*

static int shoulder = 0, elbow = 0, hand = 0;
static int fingers = 0, thumb = 0;
static int armX = 0, armY = 0;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glTranslatef((GLfloat)armX, armY, 0);
	glTranslatef(-1.0, 0.0, 0.0);
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.6, 1.0);
	//   glScalef( 2.0, 0.1, 1.0 );
	glutWireCube(1.0);

	glPopMatrix();
	
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glRotatef(30, 0.0, 0.0, 1.0);
	glTranslatef(1.2, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.6, 1.0);
	glutWireCube(1.0);

	glPopMatrix();

	//thumb
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)thumb, 0.0, 0.0, 1.0);
	glRotatef(-30, 0.0, 0.0, 1.0);
	glTranslatef(0.4, -0.25, 0.3);
	glPushMatrix();
	glScalef(0.4, 0.2, 0.3);
	glutWireCube(1.0);

	glPopMatrix();

	//FINGER 1
	glTranslatef(-0.4, 0.8, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glPushMatrix();
	glScalef(0.4, 0.2, 0.3);
	glutWireCube(1.0);

	glPopMatrix();
	
	//FINGER 2
	glTranslatef(0.0, 0.0, -0.3);
	glRotatef(-60, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -0.3, 0.0);
	glPushMatrix();
	glScalef(0.4, 0.2, 0.3);
	glutWireCube(1.0);

	glPopMatrix();

	//Finger 3
	glTranslatef(0.0, 0.0, -0.3);
	glTranslatef(0.0, 0.1, 0.0);
	glPushMatrix();
	glScalef(0.4, 0.2, 0.3);
	glutWireCube(1.0);

	glPopMatrix();

	//Finger tip 3
	glTranslatef(0.5, -0.1, 0.0);
	glRotatef(-30, 0.0, 0.0, 1.0);
	glPushMatrix();
	glScalef(0.4, 0.2, 0.3);
	glutWireCube(1.0);

	glPopMatrix();

	//Finger tip 2
	glTranslatef(0.1, 0.0, 0.3);
	glPushMatrix();
	glScalef(0.4, 0.2, 0.3);
	glutWireCube(1.0);

	glPopMatrix();

	//Finger tip 1
	glTranslatef(-0.5, 0.4, 0.3);
	glRotatef(45, 0.0, 0.0, 1.0);
	glPushMatrix();
	glScalef(0.4, 0.2, 0.3);
	glutWireCube(1.0);

	glPopMatrix();

	//Thumb tip 
	glTranslatef(-0.3, -1.1, 0.0);
	glRotatef(15, 0.0, 0.0, 1.0);
	glPushMatrix();
	glScalef(0.4, 0.2, 0.3);
	glutWireCube(1.0);

	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 's':
		shoulder = (shoulder + 5) % 360;
		glutPostRedisplay();
		break;
	case 'S':
		shoulder = (shoulder - 5) % 360;
		glutPostRedisplay();
		break;
	case 'e':
		elbow = (elbow + 5) % 360;
		glutPostRedisplay();
		break;
	case 'E':
		elbow = (elbow - 5) % 360;
		glutPostRedisplay();
		break;
	case 'h':
		hand = (hand + 5) % 360;
		glutPostRedisplay();
		break;
	case 'H':
		hand = (hand - 5) % 360;
		glutPostRedisplay();
		break;
	case 'f':
		fingers = (fingers + 5) % 360;
		thumb = (thumb - 5) % 360;
		glutPostRedisplay();
		break;
	case 'F':
		fingers = (fingers - 5) % 360;
		thumb = (thumb + 5) % 360;
		glutPostRedisplay();
		break;
	case 'a':
		armX = (armX + 1) % 360;
		glutPostRedisplay();
		break;
	case 'A':
		armX = (armX - 1) % 360;
		glutPostRedisplay();
		break;
	case 'z':
		armY = (armY + 1) % 360;
		glutPostRedisplay();
		break;
	case 'Z':
		armY = (armY - 1) % 360;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
*/