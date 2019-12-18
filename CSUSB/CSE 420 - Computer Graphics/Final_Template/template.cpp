
//draw.cpp : demo program for drawing 3 dots, two lines, ploylines, rectangles
#include <stdlib.h>
#include <stdio.h>
/*
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glext.h>
*/
#include <GL/glut.h>

//For subdivision of sphere
#define X .525731112119133606 
#define Z .850650808352039932

float tx = 0, ty = 0, tz = 0;      // translations
float ax = 0, ay = 0, az = 0;    // rotations

//For subdivision of sphere
/*
static GLfloat vdata[12][3] = {
   {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
   {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
   {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
};
static GLuint tindices[20][3] = {
   {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},
   {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},
   {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
   {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

//normalize a vector
void normalize(float v[3]) {
	GLfloat d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (d == 0.0) {
		printf("\nErrot: zero length vector");
		return;
	}
	v[0] /= d; v[1] /= d; v[2] /= d;
}

//v1[], v2[] are two vectors
//out[] holds the crossproduct v1 x v2 
void normcrossprod(float v1[3], float v2[3], float out[3])
{
	GLint i, j;
	GLfloat length;

	out[0] = v1[1] * v2[2] - v1[2] * v2[1];
	out[1] = v1[2] * v2[0] - v1[0] * v2[2];
	out[2] = v1[0] * v2[1] - v1[1] * v2[0];
	normalize(out);
}

//Use subdivision to create 80-sided spherical approximation
void drawtriangle(float *v1, float *v2, float *v3)
{
	glBegin(GL_TRIANGLES);
	glNormal3fv(v1); glVertex3fv(v1);
	glNormal3fv(v2); glVertex3fv(v2);
	glNormal3fv(v3); glVertex3fv(v3);
	glEnd();
}

void subdivide(float *v1, float *v2, float *v3, long depth)
{
	GLfloat v12[3], v23[3], v31[3];
	GLint i;

	if (depth == 0) {
		drawtriangle(v1, v2, v3);
		return;
	}
	for (i = 0; i < 3; i++) {
		v12[i] = (v1[i] + v2[i]) / 2.0;
		v23[i] = (v2[i] + v3[i]) / 2.0;
		v31[i] = (v3[i] + v1[i]) / 2.0;
	}
	normalize(v12);
	normalize(v23);
	normalize(v31);
	subdivide(v1, v12, v31, depth - 1);
	subdivide(v2, v23, v12, depth - 1);
	subdivide(v3, v31, v23, depth - 1);
	subdivide(v12, v23, v31, depth - 1);
}

void subdivide0(float *v1, float *v2, float *v3)
{
	GLfloat v12[3], v23[3], v31[3];
	GLint i;

	for (i = 0; i < 3; i++) {
		v12[i] = (v1[i] + v2[i]) / 2.0;
		v23[i] = (v2[i] + v3[i]) / 2.0;
		v31[i] = (v3[i] + v1[i]) / 2.0;
	}
	normalize(v12);	//The normalize procedure 'push out' the vertex ( make it 3-D )    
	normalize(v23);
	normalize(v31);
	drawtriangle(v1, v12, v31);
	drawtriangle(v2, v23, v12);
	drawtriangle(v3, v31, v23);
	drawtriangle(v12, v23, v31);
}
*/

//Vertex Array Cube
/*
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
							0.0, 1.0, 1.0 };
*/

//initialization
void init(void)
{
	
	//Lighting
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light[] = { 1.0, 1.0, 1.0 };
	GLfloat light_position0[] = { 5.0, 1.0, 0.5, 0.0 };
	GLfloat light_position1[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat diffuseMaterial[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };

	//glClearColor(0.0, 0.0, 0.0, 0.0);	//Black background
	glClearColor(1.0, 1.0, 1.0, 0.0);	//White background
	//glClearColor(0.7, 0.7, 0.7, 0.0);	//Gray Background
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light);

	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	

	/*
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
	*/

	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);

	//Orthographic 2D
	/*
	glClearColor(1.0, 1.0, 1.0, 0.0);	//get white background color
	glColor3f(0.0f, 0.0f, 0.0f);	//set drawing color
	gluOrtho2D(0.0, 50.0, 0.0, 50.0); (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far)
	*/

	//Orthographic 3D
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho(-5.0, 5.0, -5.0, 5.0, 0.1, 100 );
	

	//Perspective using FOV
	//FOV = 2 * Tan-1( (0.5 * Size) / Distance )
	/*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35, 1.0, 4.0, 1000);  //(GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far)
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	*/

	//Move light with camera
	/*
	glLoadIdentity();
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	*/
}


void display(void)
{
	//2D Ortho
	/*
	glClear(GL_COLOR_BUFFER_BIT);	//clear screen
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	*/

	//For Lighting
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//gluLookAt(3.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //camera at (3,3,3), aim towards point (0,0,0), up-vector (y-axis)
	//glRotatef(ax, 1, 0, 0);
	//glRotatef(ay, 0, 1, 0);
	//glRotatef(az, 0, 0, 1);
	//glTranslatef(tx, ty, tz);

	//Subdivision Sphere
	/*
	glMatrixMode(GL_MODELVIEW); // position and aim the camera
	glLoadIdentity();
	gluLookAt(8.0, 8.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                                                             
	glColor3f ( 1, 0, 0 );	//This would have no effect 
	glEnable( GL_CULL_FACE );
	glCullFace ( GL_BACK );
	glRotatef ( ay, 0, 1, 0 );
	if ( translate )
		glTranslatef ( 5, 0, 0 );
	for (int i = 0; i < 20; i++) 
	{ 
		subdivide(&vdata[tindices[i][0]][0],       
             &vdata[tindices[i][1]][0],       
             &vdata[tindices[i][2]][0], 2); 
	}
	*/

	//Draw Cube using vertex array
	/*
	glVertexPointer(3, GL_INT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, allIndices);
	*/

	//Create sphere example
	
	glPushMatrix();
	glColor3f(1, 0, 0);
	//glTranslatef(3, 0, 0);
	glScalef(0.5, 0.5, 0.5);
	glutSolidSphere(1.0, 50, 50);
	glPopMatrix();
	

	glFlush();				//send all output to screen
}

//Reshape for Orthographic
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-1.5, 1.5, -1.5*(GLfloat)h / (GLfloat)w, 
			1.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0); //(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far)
	else
		glOrtho(-1.5*(GLfloat)w / (GLfloat)h,
			1.5*(GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0); //(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


//Reshape for Perspective
/*
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35, (GLfloat)w / (GLfloat)h, 4.0f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}
*/

//Reshape using Frustrum
/*
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
}
*/

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'e':       // up
		tz += 1;
		break;
	case 'q':       // down
		tz -= 1;
		break;
	case 'w':		//north
		ty += 1;
		break;
	case 's':		//south
		ty -= 1;
		break;
	case 'a':		//west
		tx -= 1;
		break;
	case 'd':		//east
		tx += 1;
		break;
	case 27:
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void specialKey(int key, int mousex, int mousey)
{
	switch (key)
	{
	case GLUT_KEY_UP:	//rotate clockwise (down to up)
		ax -= 1;
		break;
	case GLUT_KEY_DOWN:	//rotate counter-clockwise (up to down)
		ax += 1;
		break;
	case GLUT_KEY_LEFT:	//rotate clockwise (right to left)
		az -= 1;
		break;
	case GLUT_KEY_RIGHT: //rotate counter-clockwise (left to right)
		az += 1;
		break;
	}
	glutPostRedisplay();
}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);
	glFlush();                            //send all output to screen
}


/*  Main Loop
 *  Open window with initial window size, title bar,
 *  RGBA display mode, depth buffer.
 */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);	//initialize toolkit
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//set display mode
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);	//Lighting display mode
	glutInitWindowSize(800, 800);		//set window size on screen
	glutInitWindowPosition(100, 150); 	//set window position on screen
	glutCreateWindow(argv[0]);		//open screen widow
	init();
	glutDisplayFunc(display);		//points to display function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKey);
	glutMouseFunc(myMouse);

	glutMainLoop();			//go into perpetual loop
	return 0;
}
