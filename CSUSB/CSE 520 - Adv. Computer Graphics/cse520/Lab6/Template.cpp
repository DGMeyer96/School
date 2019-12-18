/*
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

using namespace std;

const int screenHeight = 800;
const int screenWidth = 800;

 // Build standard knot vector for n control points
 // and B-splines of order m
 
void buildKnots(int m, int n, float knot[])
{
	if (n < m) return;         //not enough control points
	for (int i = 0; i < n + m; ++i) {
		if (i < m) knot[i] = 0.0;
		else if (i < n) knot[i] = i - m + 1;        //i is at least m here
		else knot[i] = n - m + 1;
	}
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glShadeModel(GL_FLAT);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	int numControlPoints = 0;
	int splineDegree = 0;

	cout << "Enter number of control points" << endl;
	cin >> numControlPoints;

	cout << "Enter the degree of the spline" << endl;
	cin >> splineDegree;

	splineDegree += 1; //degree + 1 = order

	if (splineDegree > numControlPoints)
	{
		cout << "Invalid order" << endl;
	}
	else
	{
		float *knot = new float[numControlPoints + splineDegree];
		buildKnots(splineDegree, numControlPoints, knot);

		cout << "Knot Vector: " << endl;
		for (int i = 0; i < numControlPoints + splineDegree; i++)
		{
			cout << "u" << i << " = " << knot[i] << endl;
		}
	}


	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 800);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
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
