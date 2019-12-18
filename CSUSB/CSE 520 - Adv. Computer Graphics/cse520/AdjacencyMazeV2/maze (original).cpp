#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <list>
#include <iostream>
#include <GL/glut.h>
#include "Node.h"

float tx = 0, ty = 0, tz = 0;      // translations
float ax = -45, ay = 0, az = 0;    // rotations

//Algroithm Prototypes
void buildWalls();
void fillBarriers();
void makeExit();
void solveMaze();
bool solveMaze(GLint x, GLint y);
void buildMaze();
void printList();

//OpenGL Prototypes
void drawFloor();
void drawGrid();
void drawWalls();
void drawBarriers();
void drawPath();

//Display 
const int viewportX = 500;
const int viewportY = 500;
const int tileSize = 50;

//Maze
const int vertices = viewportX / tileSize;
const int edges = viewportY / tileSize;

//3D object placement
int mazeX = viewportX;
int mazeY = viewportY;
int numBarriers = tileSize / 2;
//int numBarriers = 100;
int playerX = 0;
float offset = 0.5;

std::list<Node> adjMatrix[vertices];
std::list<Node>::iterator it;

//Algoritm
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

	for (int i = 0; i < numBarriers / 2; i++)
	{		
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
		//printList();	//Used for debugging
		solveMaze();
		//printList();	//Used for debugging
	}
	else
	{
		std::cout << "Found Solution" << std::endl;
		std::cout << std::endl;
		printList();
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

	buildWalls();
	fillBarriers();
	makeExit();
	solveMaze();
	//printList(); //Used for debugging purposes
}

void printList()
{
	for (int x = 0; x < vertices; x++)
	{
		for (it = adjMatrix[x].begin(); it != adjMatrix[x].end(); it++)
		{
			if (it->Visited == true)
			{
				std::cout << "2";
			}
			else
			{
				std::cout << it->Full;
			}
			
		}

		std::cout << std::endl;
	}
}

/*
//Non-animated drawPath()
void drawPath()
{
	//float offset = 0.5;
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
				//glutSolidSphere(1, 20, 20);
				glPopMatrix();

				
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
				
			}
		}
	}
}
*/

//OpenGL
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
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, -0.7);				glVertex3f(0, 0, -0.7);
		glNormal3f(vertices, 0, -0.7);		glVertex3f(vertices, 0, -0.7);
		glNormal3f(vertices, edges, -0.7);	glVertex3f(vertices, edges, -0.7);
		glNormal3f(0, edges, -0.7);			glVertex3f(0, edges, -0.7);
	glEnd();

	glColor3f(1.0, 0.84, 0.0);
	glBegin(GL_QUADS);
		glNormal3f(0, edges, 1.5);			glVertex3f(0, edges, 1.5);
		glNormal3f(vertices, edges, 1.5);	glVertex3f(vertices, edges, 1.5);
		glNormal3f(vertices, 0, 1.5);		glVertex3f(vertices, 0, 1.5);
		glNormal3f(0, 0, 1.5);				glVertex3f(0, 0, 1.5);
	glEnd();
}

//Animated drawPath()
void drawPath()
{
	if (playerX < vertices)
	{
		for (it = adjMatrix[playerX].begin(); it != adjMatrix[playerX].end(); it++)
		{
			if (it->Visited == true)
			{
				glPushMatrix();
				glColor3f(0.0, 1.0, 0.0);
				glTranslatef(playerX + offset, it->index + offset, 0);
				glScalef(0.5, 0.5, 0.5);
				glutSolidIcosahedron();
				glPopMatrix();

				//std::cout << "X: " << playerX << " Y: " << it->index << std::endl;

				glFlush();
			}
		}
		playerX++;
	}
	else
	{
		playerX = 0;
	}
}

void drawBarriers()
{
	for (int x = 0; x < vertices; x++)
	{
		for (it = adjMatrix[x].begin(); it != adjMatrix[x].end(); it++)
		{
			if (it->isBarrier == true)
			{
				glPushMatrix();
				glColor3f(1.0, 0.0, 0.0);
				glTranslatef(x + offset, it->index + offset, -offset);
				glutSolidCone(0.4, 1.5, 50, 50);
				glPopMatrix();
			}
			else if (it->isExit == true)
			{
				glPushMatrix();
				glColor3f(1.0, 0.0, 1.0);
				glScalef(1.0, 1.0, 1.7);
				//glScalef(1.0, 1.0, 2.0);
				glTranslatef(x + offset, it->index + offset, 0.2);
				glRotatef(90.0, 1.0, -1.0, 0.0);
				//glutSolidSphere(.5, 50, 50);
				glutSolidTorus(0.2, 0.4, 50, 50);
				glPopMatrix();
			}
		}
	}
}

void drawWalls()
{
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
			}
		}
	}
}

void init(void)
{
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light[] = { 1.0, 1.0, 1.0 };
	GLfloat light_position0[] = { 5.0, 1.0, 0.5, 0.0 };
	GLfloat light_position1[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat diffuseMaterial[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);
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

	glEnable(GL_LINE_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35, 1.0, 4.0, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	buildMaze();

	glLoadIdentity();
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 25.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(ax, 1, 0, 0);
	glRotatef(ay, 0, 1, 0);
	glRotatef(az, 0, 0, 1);
	glTranslatef(tx, ty, tz);
	glTranslatef(-(vertices / 2), -(edges / 2), 0);

	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(1, 1, 1);
	glutSolidCube(1.0);
	glPopMatrix();

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

void timerHandle(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000, timerHandle, 0);
}

void visHandle(int visible)
{
	if (visible == GLUT_VISIBLE)
		timerHandle(0);
	else
		;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(viewportX, viewportY);
	glutInitWindowPosition(600, 600);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKey);
	glutReshapeFunc(reshape);
	glutVisibilityFunc(visHandle);

	glutMainLoop();
	return 0;
}
