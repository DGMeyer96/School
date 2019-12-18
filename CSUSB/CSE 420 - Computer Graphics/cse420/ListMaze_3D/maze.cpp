#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <list>
#include <iostream>
#include <GL/glut.h>
#include "Node.h"

float tx = 0, ty = 0, tz = 0;      // translations
float ax = -45, ay = 0, az = 0;    // rotations

void fillBarriers();
void drawGrid();
void buildMaze();
void makeExit();
void solveMaze();
bool solveMaze(GLint x, GLint y);
void printList();
void gridTo3D();

const int viewportX = 500;
const int viewportY = 500;
const int tileSize = 50;

const int vertices = viewportX / tileSize;
const int edges = viewportY / tileSize;

int mazeX = viewportX;
int mazeY = viewportY;
int numBarriers = tileSize / 2;

std::list<Node> adjMatrix[vertices];

/*
std::vector<GLint> mazeWall = { 0, 0, viewportX, 0, //BL -> BR
								viewportX, 0, viewportX, viewportY, //BR -> TR
								viewportX, viewportY, 0, viewportY, //TR -> TL
								0, viewportY, 0, 0 }; //TL -> BL
std::vector<GLint> barriers;
std::vector<GLint> mazePath;
std::vector<GLint> grid;
std::vector<GLint> mazeExits = { tileSize / 2, tileSize / 2, //start
								viewportX - tileSize / 2, viewportY - tileSize / 2 }; //exit
*/

std::vector<GLint> maze;
std::list<Node>::iterator it;

void drawGrid()
{
	glColor3f(1, 1, 1);
	for (int i = 0; i <= (vertices + edges + 1); i++)
	{
		glPushMatrix();
		if (i <= edges)
			glTranslatef(0, i, 0);
		else
		{
			glTranslatef(i - edges - 1, 0, 0);
			glRotatef(90, 0, 0, 1);  //rotate about z-axis by 90 CCW
		}
		glBegin(GL_LINES);
			glVertex3f(0, 0, -0.5);
			glVertex3f(vertices, 0, -0.5);
		glEnd();
		glPopMatrix();
	}
}

void drawFloor()
{
	//glColor3f(0.5, 0.5, 0.5);
	//glColor3f(1.0, 0.84, 0.0);

	/*
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, -0.7);
	glVertex3f(vertices, 0, -0.7);
	glVertex3f(vertices, edges, -0.7);
	glVertex3f(0, edges, -0.7);
	glEnd();

	//glColor3f(0.7, 0.5, 0.7);
	//glColor3f(.29, 0.0, .51);
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
	glVertex3f(0, edges, 1.5);
	glVertex3f(vertices, edges, 1.5);
	glVertex3f(vertices, 0, 1.5);
	glVertex3f(0, 0, 1.5);
	glEnd();
	*/
}

void buildWalls()
{
	std::cout << "Placing Walls" << std::endl;

	//Walls
	for (int x = 0; x < vertices; x++)
	{
		adjMatrix[x] = std::list<Node>();

		Node n = Node();
		n.makeWall();
		adjMatrix[x].push_front(n);

		for (int y = 0; y < edges; y++)
		{
			if (x == 0 | x == vertices - 1)
			{
				n = Node();
				n.makeWall();
				n.index = y;
				adjMatrix[x].push_back(n);
			}
			else if (y == edges - 1)
			{
				n = Node();
				n.makeWall();
				n.index = y;
				adjMatrix[x].push_back(n);
			}
			else
			{
				n = Node();
				n.index = y;
				adjMatrix[x].push_back(n);
			}
		}
	}
}

void fillBarriers()
{
	std::cout << "Placing Barriers" << std::endl;

	srand(time(NULL));

	int min = 1;
	int maxX = viewportX / tileSize;
	int maxY = viewportY / tileSize;
	int x, y;


	//std::list<Node>::iterator it;

	for (int i = 0; i < numBarriers / 2; i++)
	{
		//x = rand() % 11 + 1; //get grid coordinate
		//y = rand() % 11; //get grid coordinate
		
		x = rand() % ((vertices - 1) - 1) + 1; //get grid coordinate
		y = rand() % ((edges - 1) - 1) + 1; //get grid coordinate

		it = adjMatrix[x].begin();
		advance(it, y);
		Node n = *it;
		n.makeBarrier();
		n.index = y;
		adjMatrix[x].erase(it);
		it = adjMatrix[x].begin();
		advance(it, y);
		adjMatrix[x].insert(it, n);
	}
}

void makeExit()
{
	it = adjMatrix[vertices - 2].begin();
	advance(it, edges - 2);
	Node n = *it;
	n.makeExit();
	n.index = edges - 2;
	adjMatrix[vertices - 2].erase(it);
	it = adjMatrix[vertices - 2].begin();
	advance(it, edges - 2);
	adjMatrix[vertices - 2].insert(it, n);
}

void solveMaze()
{
	if (solveMaze(1, 1) == false)
	{
		std::cout << "No Solution" << std::endl;
		std::cout << std::endl;

		for (int i = 0; i < vertices; i++)
		{
			adjMatrix[i].clear();
		}

		buildWalls();
		fillBarriers();
		makeExit();
		//printList();
		solveMaze();
		//printList();
	}
	else
	{
		std::cout << "Found Solution" << std::endl;
		std::cout << std::endl;
		printList();
		gridTo3D();
	}
	
}


bool solveMaze(GLint x, GLint y)
{
	if (x == vertices - 2 && y == edges - 2)
	{
		it = adjMatrix[x].begin();
		advance(it, y);
		Node n = *it;
		n.makePlayer();
		n.index = y;
		adjMatrix[x].erase(it);
		it = adjMatrix[x].begin();
		advance(it, y);
		adjMatrix[x].insert(it, n);

		return true;
	}
	it = adjMatrix[x].begin();
	std::advance(it, y);
	if (it->Full == 0)
	{
		it = adjMatrix[x].begin();
		advance(it, y);
		Node n = *it;
		n.makePlayer();
		n.index = y;
		adjMatrix[x].erase(it);
		it = adjMatrix[x].begin();
		advance(it, y);
		adjMatrix[x].insert(it, n);

		if (solveMaze(x + 1, y) == true)
		{
			return true;
		}
		else if (solveMaze(x, y + 1) == true)
		{
			return true;
		}
		else
		{
			it = adjMatrix[x].begin();
			advance(it, y);
			Node n = Node();
			n.index = y;
			adjMatrix[x].erase(it);
			it = adjMatrix[x].begin();
			advance(it, y);
			adjMatrix[x].insert(it, n);

			return false;
		}
	}
	else
	{
		return false;
	}
}

void buildMaze()
{
	std::cout << "Building maze" << std::endl;

	//glClear(GL_COLOR_BUFFER_BIT);

	buildWalls();
	fillBarriers();
	makeExit();
	solveMaze();
	//printList();
}

void printList()
{
	//it = adjMatrix[x].begin();
	for (int x = 0; x < vertices; x++)
	{
		for (it = adjMatrix[x].begin(); it != adjMatrix[x].end(); it++)
		{
			//Node n = *it;

			if (it->Visited == true)
			{
				std::cout << "8";
			}
			else
			{
				std::cout << it->Full;
			}
			
		}

		std::cout << std::endl;
	}
}

void gridTo3D()
{
	float offset = 0.5;
	for (int x = 0; x < vertices; x++)
	{
		for (it = adjMatrix[x].begin(); it != adjMatrix[x].end(); it++)
		{
			glPushMatrix();

			if (it->isWall == true)
			{
				glColor3f(0.0, 1.0, 1.0);
				glScalef(1.0, 1.0, 2.0);
				glTranslatef(x + offset, it->index + offset, 0.2);
				glutSolidCube(0.9);
			}
			else if (it->isBarrier == true)
			{
				glColor3f(1.0, 0.0, 0.0);
				glTranslatef(x + offset, it->index + offset, 0);
				glutSolidCube(0.9);
			}
			else if (it->Visited == true)
			{
				glColor3f(0.0, 1.0, 0.0);
				glTranslatef(x + offset, it->index + offset, 0);
				glutSolidCube(0.5);
			}

			glPopMatrix();
		}
	}
}

void drawPath()
{
	float offset = 0.5;
	for (int x = 0; x < vertices; x++)
	{
		for (it = adjMatrix[x].begin(); it != adjMatrix[x].end(); it++)
		{
			if (it->Visited == true)
			{
				glPushMatrix();
				glColor3f(0.0, 1.0, 0.0);
				glTranslatef(x + offset, it->index + offset, 0);
				//glutSolidCube(0.5);
				//glScalef(0.25, 0.25, 0.25);
				//glutSolidDodecahedron();
				glScalef(0.5, 0.5, 0.5);
				glutSolidIcosahedron();
				//glutSolidTetrahedron();
				//glutSolidSphere(1, 50, 50);
				glPopMatrix();

				/*
				glPushMatrix();
				glColor3f(0.0, 0.6, 0.0);
				glTranslatef(x + offset, it->index + offset, 0);
				//glutWireCube(0.5);
				//glScalef(0.25, 0.25, 0.25);
				//glutWireDodecahedron();
				glScalef(0.5, 0.5, 0.5);
				//glutWireIcosahedron();
				glutWireTetrahedron();
				glPopMatrix();
				*/
			}
		}
	}
}

void drawBarriers()
{
	float offset = 0.5;
	for (int x = 0; x < vertices; x++)
	{
		for (it = adjMatrix[x].begin(); it != adjMatrix[x].end(); it++)
		{
			if (it->isBarrier == true)
			{
				/*
				glPushMatrix();
				glColor3f(1.0, 0.0, 0.0);
				glTranslatef(x + offset, it->index + offset, 0);
				glutSolidCube(0.9);
				glPopMatrix();

				glPushMatrix();
				glColor3f(1.0, 1.0, 1.0);
				glTranslatef(x + offset, it->index + offset, 0);
				glutWireCube(0.9);
				glPopMatrix();
				*/

				glPushMatrix();
				glColor3f(1.0, 0.0, 0.0);
				glTranslatef(x + offset, it->index + offset, -offset);
				//glutSolidCube(0.9);
				glutSolidCone(0.4, 1.5, 20, 20);
				glPopMatrix();

				/*
				glPushMatrix();
				glColor3f(1.0, 1.0, 1.0);
				glTranslatef(x + offset, it->index + offset, -offset);
				//glutWireCube(0.9);
				glutWireCone(0.4, 1.5, 8, 3);
				glPopMatrix();
				*/
			}
			else if (it->isExit == true)
			{
				glPushMatrix();
				glColor3f(1.0, 0.0, 1.0);
				glScalef(1.0, 1.0, 2.0);
				glTranslatef(x + offset, it->index + offset, 0.2);
				//glutSolidCube(1.0);
				glutSolidSphere(.5, 20, 20);
				glPopMatrix();

				/*
				glPushMatrix();
				glColor3f(1.0, 1.0, 1.0);
				glScalef(1.0, 1.0, 2.0);
				glTranslatef(x + offset, it->index + offset, 0.2);
				glutWireCube(1.0);
				glPopMatrix();
				*/
			}
		}
	}
}

void drawWalls()
{
	float offset = 0.5;
	for (int x = 0; x < vertices; x++)
	{
		for (it = adjMatrix[x].begin(); it != adjMatrix[x].end(); ++it) //missing last one
		{
			if (it->isWall == true)
			{
				glPushMatrix();
				glColor3f(0.0, 0.0, 1.0);
				glScalef(1.0, 1.0, 2.0);
				glTranslatef(x + offset, it->index + offset, 0.2);
				glutSolidCube(1.0);
				glPopMatrix();

				/*
				glPushMatrix();
				//glColor3f(1.0, 1.0, 1.0);
				glColor3f(0.0, 0.0, 0.7);
				glScalef(1.0, 1.0, 2.0);
				glTranslatef(x + offset, it->index + offset, 0.2);
				glutWireCube(1.0);
				glPopMatrix();
				*/
			}
		}
	}
}

void init(void)
{
	/*
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.2 };
	GLfloat light[] = { 1.0, 1.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 0.2 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light_position1[] = { 0.0, 0.0, 1.0, 0.0 };
	//GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat diffuseMaterial[4] = { 1, 1, 1, 0.2 };

	//glClearColor(0.5, 0.5, 0.2, 0.5);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 125.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	*/

	//glClearColor(1.0, 1.0, 1.0, 0.0);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//glShadeModel(GL_SMOOTH);
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess =  125.0 ;
	GLfloat light[] = { 1.0, 1.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess); //f vale for specular calculation
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	//glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35, 1.0, 4.0, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	buildMaze();
}


void display(void)
{
	//glClear(GL_COLOR_BUFFER_BIT);	//clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 25.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(ax, 1, 0, 0);
	glRotatef(ay, 0, 1, 0);
	glRotatef(az, 0, 0, 1);
	glTranslatef(-(vertices / 2), -(edges / 2), 0);

/*
	//Light position
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(5.0, 5.0, 0.5);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();
*/
	//buildMaze();
	//gridTo3D();
	drawFloor();
	drawGrid();
	drawWalls();
	drawBarriers();
	drawPath();
	
	glFlush();
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
	case GLUT_KEY_UP:
		ax -= 1;
		break;
	case GLUT_KEY_DOWN:
		ax += 1;
		break;
	case GLUT_KEY_LEFT:
		az -= 1;
		break;
	case GLUT_KEY_RIGHT:
		az += 1;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(viewportX, viewportY);
	glutInitWindowPosition(600, 600);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKey);
	glutReshapeFunc(reshape);
	
	glutMainLoop();
	return 0;
}
