#include <stdio.h>
#include <GL/glut.h>

float tx = 0, ty = 0, tz = 0;      // translations
float ax = -45, ay = 0, az = 0;    // rotations

bool triangles = false;

class Quads
{
public:
	float x[4], y[4], z[4];
	float r, g, b;
};

Quads Q[100];
int nQuads = 0;
int sideQ = 0;

class Triangles
{
public:
	float x[3], y[3], z[3];
	float r, g, b;
};

Triangles T[100];
int nTriangles = 0;
int sideT = 0;

void addQuad()
{
	Q[nQuads].x[sideQ] = tx;
	Q[nQuads].y[sideQ] = ty;
	Q[nQuads].z[sideQ] = tz;
	sideQ++;
	if (sideQ > 3) {
		nQuads++;
		sideQ = 0;
	}
}

void drawQuads()
{
	for (int i = 0; i < nQuads; i++) {
		glColor3f(Q[i].r, Q[i].g, Q[i].b);
		glBegin(GL_QUADS);
		for (int j = 0; j < 4; j++)
			glVertex3f(Q[i].x[j], Q[i].y[j], Q[i].z[j]);
		glEnd();
	}

}

void addTriangle()
{
	T[nTriangles].x[sideT] = tx;
	T[nTriangles].y[sideT] = ty;
	T[nTriangles].z[sideT] = tz;
	sideT++;
	if (sideT > 2)
	{
		nTriangles++;
		sideT = 0;
	}
}

void drawTriangle()
{
	for (int i = 0; i < nTriangles; i++) {
		glColor3f(T[i].r, T[i].g, T[i].b);
		glBegin(GL_TRIANGLES);
		for (int j = 0; j < 3; j++)
			glVertex3f(T[i].x[j], T[i].y[j], T[i].z[j]);
		glEnd();
	}
}

//initialization
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);	//get white background color
	glColor3f(0.0f, 0.0f, 0.0f);	//set drawing color
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35, 1.0f, 4.0f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawGrid()
{
	glColor3f(0, 0, 0);
	for (int i = 0; i < 34; i++) {
		glPushMatrix();
		if (i < 17)
			glTranslatef(0, i, 0);
		else {
			glTranslatef(i - 17, 0, 0);
			glRotatef(90, 0, 0, 1);  //rotate about z-axis by 90 CCW
		}
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(16, 0, 0);
		glEnd();
		glPopMatrix();
	}

}

void drawCube()
{
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(tx, ty, tz);
	glutSolidCube(0.5);
	glPopMatrix();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	//clear screen
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 40.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(ax, 1, 0, 0);
	glRotatef(ay, 0, 1, 0);
	glRotatef(az, 0, 0, 1);
	glTranslatef(-8, -8, 0);
	drawGrid();
	drawCube();
	drawQuads();
	drawTriangle();
	glFlush();				//send all output to screen
}

void setColor(float r, float g, float b)
{
	Q[nQuads].r = r;
	Q[nQuads].g = g;
	Q[nQuads].b = b;
}
void keyboard(unsigned char key, int mousex, int mousey)
{
	switch (key) {
	case 'u':       // up
		tz += 1;
		break;
	case 'd':       // down
		tz -= 1;
		break;
	case 'a':   //rotation angle
		ax -= 1;
		break;
	case 'A':   //rotation angle
		ax += 1;
		break;
	case 'z':   //rotation angle
		az -= 1;
		break;
	case 'Z':   //rotation angle
		az += 1;
		break;

	case 32:       //space
		if (triangles == false)
			addQuad();
		else if(triangles == true)
			addTriangle();
		break;
	case 'R':
		setColor(1, 0, 0);
		break;
	case 'G':
		setColor(0, 1, 0);
		break;
	case 'B':
		setColor(0, 0, 1);
		break;
	case 'Y':
		setColor(1, 1, 0);
		break;

	case 't':
		if (triangles == false)
			triangles = true;
		else  if(triangles == true)
			triangles = false;
		break;
	case 27:       // escape
		exit(-1);
	}
	glutPostRedisplay();
}

void specialKey(int key, int mousex, int mousey)
{
	switch (key) {
	case GLUT_KEY_UP:
		ty += 1;
		break;
	case GLUT_KEY_DOWN:
		ty -= 1;
		break;
	case GLUT_KEY_LEFT:
		tx -= 1;
		break;
	case GLUT_KEY_RIGHT:
		tx += 1;
		break;
	}
	glutPostRedisplay();
}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);
	glFlush();                            //send all output to screen
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35, (GLfloat)w / (GLfloat)h, 4.0f, 1000);
	//  gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}


/*  Main Loop
 *  Open window with initial window size, title bar,
 *  RGBA display mode, depth buffer.
 */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);	//initialize toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//set display mode
	glutInitWindowSize(800, 800);		//set window size on screen
	glutInitWindowPosition(100, 150); 	//set window position on screen
	glutCreateWindow(argv[0]);		//open screen widow
	init();
	glutDisplayFunc(display);		//points to display function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKey);
	glutMouseFunc(myMouse);
	glutReshapeFunc(reshape);


	glutMainLoop();			//go into perpetual loop
	return 0;
}
