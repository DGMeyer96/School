
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

using namespace std;

const int screenHeight = 800;
const int screenWidth = 800;

GLfloat ctrlpoints0[4][3] = {
	{-4.5, -4.0, 0.0}, {-3.0, 4.0, 0.0},
	{-1.5, 4.0, 0.0}, {0.0, -4.0, 0.0}
};

GLfloat ctrlpoints[4][3] = {
		{ -4.0, -4.0, 0.0}, { -2.0, 4.0, 0.0},
		{2.0, -4.0, 0.0}, {4.0, 4.0, 0.0} };

float p[3];

//  Build standard knot vector for n control points
//  and B-splines of order m

void buildKnots(int m, int n, float knot[])
{
	if (n < m) return;         //not enough control points
	for (int i = 0; i < n + m; ++i) {
		if (i < m) knot[i] = 0.0;
		else if (i < n) knot[i] = i - m + 1;        //i is at least m here
		else knot[i] = n - m + 1;
	}
}

//evaluate blending functions recurvsively
float bSpline(int k, int m, float u, float knot[])
{
	float d1, d2, sum = 0.0;

	if (m == 1)
		return (knot[k] < u &&  u <= knot[k + 1]);   //1 or 0

	  //m larger than 1, so recurse
	d1 = knot[k + m - 1] - knot[k];
	if (d1 != 0)
		sum = (u - knot[k]) * bSpline(k, m - 1, u, knot) / d1;
	d2 = knot[k + m] - knot[k + 1];
	if (d2 != 0)
		sum += (knot[k + m] - u) * bSpline(k + 1, m - 1, u, knot) / d2;

	return sum;
}

//non uniform rational B-splines, n control points, order m, p[] is the output point 
void nurb(float control_points[][3], float u, float p[])
{
	const int n = 4, m = 4;               //this reduces to cubic B-spline
	float knot[n + m];
	buildKnots(m, n, knot);           //construct the knob

	// sum the control points mulitplied by their respective blending functions
	for (int i = 0; i < 3; ++i) {        //x, y, z components
		p[i] = 0;
		for (int k = 0; k < n; ++k)
			p[i] += bSpline(k, m, u, knot) * control_points[k][i];
	}
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_FLAT);
	glShadeModel(GL_FLAT);
	/*
  *       GL_MAP1_VERTEX_3 -- specifies that 3-dimensional control points are
  *       provided and 3-D vertices should be produced
  *       0.0 -- low value of parmeter u
  *       1.0 -- high value of parmeter u
  *       3   -- number of floating-point values to advance in the data between two
  *       consecutive control points
  *       4   -- order of the spline ( = degree + 1 )
  *       			            	          */
	nurb(ctrlpoints0, 1.0, p);
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints0[0][0]);
	//   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 5, &ctrlpoints0[0][0]);
	glEnable(GL_MAP1_VERTEX_3);
}

void display(void)
{
	/*
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
	*/

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 30; i++)
		glEvalCoord1f((GLfloat)i / 30.0);
	glEnd();
	/* The following code displays the control points as dots. */
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 4; i++)
		glVertex3fv(&ctrlpoints0[i][0]);
	glEnd();

	glFlush();
}

void reshape(int w, int h)
{
	/*
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 800);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-5.0, 5.0, -5.0*(GLfloat)h / (GLfloat)w,
			5.0*(GLfloat)h / (GLfloat)w, -5.0, 5.0);
	else
		glOrtho(-5.0*(GLfloat)w / (GLfloat)h,
			5.0*(GLfloat)w / (GLfloat)h, -5.0, 5.0, -5.0, 5.0);
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
