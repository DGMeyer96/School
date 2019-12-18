#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>

void init(void)
{
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat diffuseMaterial[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light[] = { 1.0, 1.0, 1.0 };
	
	GLfloat light_position0[] = { -3.0, -1.0, -1.0, 1.0 };
	GLfloat light_position1[] = { 0.0, 3.0, 1.0, 1.0 };
	GLfloat light_position2[] = { 3.0, 0.0, 1.0, 1.0 };
	GLfloat spot_direction0[] = { 1.0, 1.0, 1.0 };
	GLfloat spot_direction1[] = { -1.0, -1.0, -1.0 };
	GLfloat spot_direction2[] = { 0.0, -1.0, 0.0 };
	
	
	/*
	GLfloat light_position0[] = { 3.0, 3.0, 3.0, 1.0 };
	GLfloat light_position1[] = { -3.0, -3.0, -3.0, 1.0 };
	GLfloat light_position2[] = { 0.0, -3.0, 0.0, 1.0 };
	GLfloat spot_direction0[] = { -3.0, -3.0, -3.0 };
	GLfloat spot_direction1[] = { 3.0, 0.0, 0.0 };
	GLfloat spot_direction2[] = { -1.5, 3.0, 0.0 };
	*/

	GLfloat local_view[] = { 0.0 };

	glClearColor(0.7, 0.7, 0.7, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction1);

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction2);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Sphere A
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(3, 0, 0);
	glutSolidSphere(1.0, 50, 50);
	glPopMatrix();

	//Sphere B
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(-3, 0, 0);
	glutSolidSphere(1.0, 50, 50);
	glPopMatrix();

	//Sphere C
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(0, 3, 0);
	glutSolidSphere(1.0, 50, 50);
	glPopMatrix();

	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= (h * 2))
		glOrtho(-6.0, 6.0, -3.0*((GLfloat)h * 2) / (GLfloat)w,
			3.0*((GLfloat)h * 2) / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-6.0*(GLfloat)w / ((GLfloat)h * 2),
			6.0*(GLfloat)w / ((GLfloat)h * 2), -3.0, 3.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(600, 600);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}