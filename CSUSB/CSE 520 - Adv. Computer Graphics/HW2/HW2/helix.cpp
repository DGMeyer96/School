/* helix-tube1.cpp : Constructs a tube using helix curve and Frenet frames.
 *
 * For CS 520, 2010
 * @Author: T.L. Yu
 */
/*
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "LinearR4.h"
#include <SDL/SDL.h>
#include <GL/glut.h>

using namespace std;

int anglex = 0, angley = 0, anglez = 0;          //rotation angles
int window;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3.0, 3.0, -3.0, 3.0, 0.1, 100);
	glMatrixMode(GL_MODELVIEW); // position and aim the camera
	glLoadIdentity();
	gluLookAt(0, 0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

//helix curve
void get_C(float C[4], float t, float b)
{
	C[0] = (1 + 0.5 * cos(7 * t)) * cos(t);
	C[1] = (1 + 0.5 * cos(7 * t)) * sin(t);
	C[2] = 0.5 * sin(7 * t);
	C[3] = 1;
}


//Matrix for transforming to Frenet frame
void setM(LinearMapR4 &M, float t, float b)
{
	float c = 1.0 / sqrt(1 + b * b);
	M.SetColumn1((7 * sin(t) * sin(7 * t)) + cos(t) * (-25 * cos(7 * t) - 1),
				(-25.5 * sin(t) * cos(7 * t)) - (10.5 * sin(7 * t) * cos(t)),
				-24.5 * sin(7 * t),
				0);		//Normal    N(t)
	M.SetColumn2((-89.25 * pow(cos(7*t),2) * sin(t)) + (24.5 * cos(t) * sin(7*t)) - (24.5 * cos(t) * cos(7*t) * sin(7*t)) - (85.75 * sin(t) * pow(sin(7*t), 2))*c,
				(3.5 * cos(t) * cos(7*t)) + (87.5 * cos(t) * pow(cos(7*t), 2)) + (24.5 * sin(t) * sin(7*t)) - (12.25 * cos(7*t) * sin(t) * sin(7*t)) + (85.75 * cos(t) * pow(sin(7*t), 2)) *c,
				(-pow(cos(t), 2)) - (25.5 * pow(cos(t), 2) * cos(7*t)) - (12.5 * pow(cos(t), 2) * pow(cos(7*t), 2)) - (25.5 * cos(7*t) * pow(sin(t), 2)) - (12.75 * pow(cos(7*t), 2) * pow(sin(t), 2)) - (3.5 * cos(t) * cos(7*t) * sin(t) * sin(7*t)) - (36.75 * pow(cos(t), 2) * pow(sin(7*t), 2)) - (24.5 * pow(sin(t), 2) * pow(sin(7*t), 2)),
				0);	//Binormal  B(t)
	M.SetColumn3(sin(t) * (-0.5 * Cos(7 * t) - 1) - (3.5 * sin(7 * t) * cos(t)) * c,
				(-3.5 * sin(t) *  sin(7 * t)) + (0.5 * cos(7 *t) * cos(t)) + cos(t) * c,
				(3.5 * cos(7 * t)) * c,
				0);	//Tangent   T(t)
	M.SetColumn4((1 + 0.5 * cos(7 * t)) * cos(t),
				(1 + 0.5 * cos(7 * t)) * sin(t),
				0.5 * sin(7 * t),
				1);  		//The curve C(t)
}

void print_M(LinearMapR4 &M)
{
	cout << "(" << M.m11 << ",\t" << M.m12 << ",\t" << M.m13 << ",\t" << M.m14 << ")" << endl;
	cout << "(" << M.m21 << ",\t" << M.m22 << ",\t" << M.m23 << ",\t" << M.m24 << ")" << endl;
	cout << "(" << M.m31 << ",\t" << M.m32 << ",\t" << M.m33 << ",\t" << M.m34 << ")" << endl;
	cout << "(" << M.m41 << ",\t" << M.m42 << ",\t" << M.m43 << ",\t" << M.m44 << ")" << endl;
}

class Cfloat3 {		//Note: array is copyable; e.g. int a[8],b[8]; "a = b;" won't work 
public:
	float p3[3];
};

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const float b = 0.1;		//constant of Helix curve
	double H = 6.0;
	LinearMapR4 M;		//Transformation matrix
	const int N = 4;		//number of vertices in base


	vector<Cfloat3>vp0(N), vp1(N);
	VectorR4 p_1;			//transformed point	

	//4 vertices of a quad
	//float p[4][3]= { {-0.2,-0.2,0}, {0.2,-0.2,0}, {0.2,0.2, 0},{-0.2,0.2,0} };
	//homogeneous coordinates of the four vertices of a quad
	VectorR4 points[4];		//define four points
	points[0] = VectorR4(-0.1, -0.1, 0, 1);	//x, y, z, w
	points[1] = VectorR4(0.1, -0.1, 0, 1);	//x, y, z, w
	points[2] = VectorR4(0.1, 0.1, 0, 1);	//x, y, z, w
	points[3] = VectorR4(-0.1, 0.1, 0, 1);	//x, y, z, w

	glColor3f(0.1, 1.0, 0);
	glPushMatrix();
	glRotatef(anglex, 1.0, 0.0, 0.0);   //rotate the object about x-axis
	glRotatef(angley, 0.0, 1.0, 0.0);   //rotate about y-axis   
	glRotatef(anglez, 0.0, 0.0, 1.0);   //rotate about z-axis
	float C[4];
	glLineWidth(3);
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	//The curve
	glBegin(GL_LINE_STRIP);
	for (float t = 0; t <= 26; t += 0.2) {
		get_C(C, t, b);
		glVertex4fv(C);
	}
	glColor3f(1.0, 0.1, 0);
	glEnd();

	float p3[3];		//3-D point, (x, y, z)
	//starting
	setM(M, 0, b);	//t = 0
	for (int i = 0; i < 4; ++i) {
		p_1 = M * points[i];	//transform the point
		p_1.Dump(vp0[i].p3);	//put (x, y, z) in vp0[i].p3[]
	}
	glBegin(GL_QUADS);		//a side has four points
	for (float t = 0.2; t <= 26; t += 0.2) {
		setM(M, t, b);
		for (int i = 0; i < N; ++i) {
			p_1 = M * points[i];	//transform the point
			p_1.Dump(vp1[i].p3);	//put (x, y, z) in vp1[i].p3[]
		}
		for (int i = 0; i < N; ++i) { //draw the N sides of tube between 'base' and 'cap'
			int j = (i + 1) % N;
			glVertex3fv(vp0[i].p3);
			glVertex3fv(vp0[j].p3);
			glVertex3fv(vp1[j].p3);
			glVertex3fv(vp1[i].p3);
		}
		copy(vp1.begin(), vp1.end(), vp0.begin());	//copy vp1 to vp0
	}  //for t
	glEnd();
	glPopMatrix();
	glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		glutDestroyWindow(window);
		exit(0);
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
	case 'r':                                   //reset
		anglez = angley = anglex = 0;
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	window = glutCreateWindow("Mesh ");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); //white background
	glViewport(0, 0, 500, 500);
	init();

	glutMainLoop();

	return 0;
}
*/