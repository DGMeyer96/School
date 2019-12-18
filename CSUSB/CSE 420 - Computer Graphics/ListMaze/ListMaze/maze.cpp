/*
 * Copyright (c) 1993-2003, Silicon Graphics, Inc.
 * All Rights Reserved
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright
 * notice and this permission notice appear in supporting documentation,
 * and that the name of Silicon Graphics, Inc. not be used in
 * advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS" AND
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION, LOSS OF
 * PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF THIRD
 * PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE POSSESSION, USE
 * OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor clauses
 * in the FAR or the DOD or NASA FAR Supplement.  Unpublished - rights
 * reserved under the copyright laws of the United States.
 *
 * Contractor/manufacturer is:
 *	Silicon Graphics, Inc.
 *	1500 Crittenden Lane
 *	Mountain View, CA  94043
 *	United State of America
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

 /*
  *  varray.c
  *  This program demonstrates vertex arrays.
  */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <list>
#include <iostream>
#include <GL/glut.h>
#include "Node.h"

void fillBarriers();
void drawGrid();
void buildMaze();
void makeExit();
void solveMaze();
bool solveMaze(GLint x, GLint y);
void printList();
void gridToPixel();

const int viewportX = 500;
const int viewportY = 500;
const int tileSize = 50;

float windowLeft = -5.0;
float windowRight = 5.0;
float windowBottom = -5.0;
float windowTop = 5.0;

const int vertices = viewportX / tileSize;
const int edges = viewportY / tileSize;

int mazeX = viewportX;
int mazeY = viewportY;
int numBarriers = tileSize / 2;

std::list<Node> adjMatrix[vertices];

std::vector<GLint> mazeWall = { 0, 0, viewportX, 0, //BL -> BR
								viewportX, 0, viewportX, viewportY, //BR -> TR
								viewportX, viewportY, 0, viewportY, //TR -> TL
								0, viewportY, 0, 0 }; //TL -> BL
std::vector<GLint> barriers;
std::vector<GLint> mazePath;
std::vector<GLint> grid;
std::vector<GLint> mazeExits = { tileSize / 2, tileSize / 2, //start
								viewportX - tileSize / 2, viewportY - tileSize / 2 }; //exit

std::vector<GLint> maze;

//std::vector<list<Node>> maze(viewportX / tileSize);

std::vector<GLint>::iterator iterX;
std::vector<GLint>::iterator iterY;

std::list<Node>::iterator it;

void setWindow(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

void setViewport(GLint left, GLint right, GLint bottom, GLint top)
{
	glViewport(left, bottom, right - left, top - bottom);
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glEnableClientState(GL_VERTEX_ARRAY);
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	buildMaze();

	

	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

void drawGrid()
{
	std::cout << "Drawing Grid" << std::endl;

	//Draw all vertical lines
	for (int x = 0; x < viewportX; x += tileSize)
	{
		grid.push_back(x);
		grid.push_back(viewportY);
		grid.push_back(x);
		grid.push_back(0);
	}

	//Draw all horizontal lines
	for (int y = 0; y < viewportY; y += tileSize)
	{
		grid.push_back(viewportX);
		grid.push_back(y);
		grid.push_back(0);
		grid.push_back(y);
	}
}

void buildWalls()
{
	//Exit
	//std::list<Node>::iterator it;
	/*
	it = adjMatrix[vertices - 2].begin();
	advance(it, edges - 2);
	Node n = *it;
	adjMatrix[vertices - 2].erase(it);
	n.makeWall();
	n.index = edges - 2;
	it = adjMatrix[vertices - 2].begin();
	adjMatrix[vertices - 2].insert(it, edges - 2, n);
	*/

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
		n.makeWall();
		n.index = y;
		adjMatrix[x].erase(it);
		it = adjMatrix[x].begin();
		advance(it, y);
		adjMatrix[x].insert(it, n);

		/*
		x *= tileSize; //translate grid coordinate to pixel
		x -= tileSize / 2; //center x-component
		
		y *= tileSize; //translate grid coordinate to pixel
		y -= tileSize / 2; //center y-component

		//Check if barrier is at entrance or exit
		if ((x == tileSize / 2 && y == tileSize / 2) | (x == viewportX - tileSize / 2 && y == viewportY - tileSize / 2))
		{
			x = rand() % 11; //get grid coordinate
			x *= tileSize; //translate grid coordinate to pixel
			x -= tileSize / 2; //center x-component
			y = rand() % 11; //get grid coordinate
			y *= tileSize; //translate grid coordinate to pixel
			y -= tileSize / 2; //center y-component
		}

		barriers.push_back(x); //store x-component
		barriers.push_back(y); //store y-component
		*/
	}
}

void makeExit()
{
	it = adjMatrix[vertices - 2].begin();
	advance(it, edges - 2);
	Node n = *it;
	n.makeWall();
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

		for (int i = 0; i < vertices; i++)
		{
			adjMatrix[i].clear();
		}

		buildWalls();
		fillBarriers();
		makeExit();
		//printList();
		solveMaze();
		printList();
	}
		std::cout << "Found Solution" << std::endl;
		gridToPixel();

	
	/*
	std::cout << "Attempting to solve:" << std::endl;

	if (solveMaze(mazeExits[0], mazeExits[1]) == false)
	{
		std::cout << "No Solution" << std::endl;

		return;

		//buildMaze();
		//solveMaze();
	}

	std::cout << "Found Solution" << std::endl;

	std::cout << "Drawing Solution" << std::endl;
	fillBarriers();
	glColor3f(1.0, 0.0, 1.0);
	glVertexPointer(2, GL_INT, 0, &mazePath.front());
	glPointSize(45.0);
	glDrawArrays(GL_POINTS, 0, mazePath.size() / 2);
	*/
}


bool solveMaze(GLint x, GLint y)
{
	//std::list<Node>::iterator it;

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

	/*
	iterX = find(barriers.begin(), barriers.end(), x + tileSize); //Check for barrier at x + 1
	//iterY = find(barriers.begin(), barriers.end(), y + tileSize); //Check for barrier at y + 1
	if (iterX != barriers.end() && y == *(iterX + 1) || x >= viewportX) //Found barrier at x + 1 or at edge
	{
		//mazePath.push_back(x);
		//mazePath.push_back(y);
		//return solveMaze(x, y + tileSize);

		iterY = find(barriers.begin(), barriers.end(), y + tileSize); //Check for barrier at y + 1
		if (iterY != barriers.end() && x == *(iterY - 1) || y >= viewportY) //Found barrier at y + 1 or at edge
		{
			//Can't go up or right = no solution
			return false;
		}
		else //No barrier at y + 1
		{
			mazePath.push_back(x);
			mazePath.push_back(y);
			return solveMaze(x, y + tileSize); //move to y + 1
		}
	}
	else //No barrier at x + 1
	{
		mazePath.push_back(x);
		mazePath.push_back(y);
		return solveMaze(x + tileSize, y); //move to x + 1
	}
	*/
}

void buildMaze()
{
	std::cout << "Building maze" << std::endl;

	//glClear(GL_COLOR_BUFFER_BIT);

	//drawing wall
	glColor3f(1.0, 0.0, 0.0);
	glVertexPointer(2, GL_INT, 0, &mazeWall.front());
	glLineWidth(50.0);
	glDrawArrays(GL_LINES, 0, 10);

	//drawing grid
	drawGrid();
	glColor3f(1.0, 1.0, 1.0);
	glVertexPointer(2, GL_INT, 0, &grid.front());
	glLineWidth(5.0);
	glDrawArrays(GL_LINES, 0, grid.size() / 2);

	/*
	fillBarriers();
	glColor3f(0.0, 1.0, 0.0);
	glVertexPointer(2, GL_INT, 0, &barriers.front());
	glPointSize(45.0);
	glDrawArrays(GL_POINTS, 0, numBarriers);

	glColor3f(0.0, 0.0, 1.0);
	glVertexPointer(2, GL_INT, 0, &mazeExits.front());
	glPointSize(45.0);
	glDrawArrays(GL_POINTS, 0, 2);
	*/

	//gridToPixel();
	buildWalls();
	fillBarriers();
	makeExit();
	//printList();
	solveMaze();
	printList();

	glColor3f(0.0, 1.0, 0.0);
	glVertexPointer(2, GL_INT, 0, &barriers.front());
	glPointSize(45.0);
	glDrawArrays(GL_POINTS, 0, barriers.size() / 2);

	std::cout << "Drawing Solution" << std::endl;
	glColor3f(1.0, 0.0, 1.0);
	glVertexPointer(2, GL_INT, 0, &maze.front());
	glPointSize(45.0);
	glDrawArrays(GL_POINTS, 0, maze.size() / 2);
}

void printList()
{
	//it = adjMatrix[x].begin();
	for (int x = 0; x < vertices; x++)
	{
		for (it = adjMatrix[x].begin(); it != adjMatrix[x].end(); it++)
		{
			Node n = *it;

			if (n.Visited == true)
			{
				std::cout << "8";
			}
			else
			{
				std::cout << n.Full;
			}
			
		}

		std::cout << std::endl;
	}
}

void gridToPixel()
{
	

	for (int x = 0; x < vertices; x++)
	{
		for (it = adjMatrix[x].begin(); it != adjMatrix[x].end(); it++)
		{
			if (it->isWall == true)
			{
				//maze.push_back((x * tileSize) + (tileSize / 2));
				//maze.push_back((it->index * tileSize) + (tileSize / 2));

				
				barriers.push_back((it->index * tileSize) + (tileSize / 2));
				barriers.push_back((x * tileSize) + (tileSize / 2));
			}
			if (it->Visited == true)
			{
				
				maze.push_back((it->index * tileSize) + (tileSize / 2));
				maze.push_back((x * tileSize) + (tileSize / 2));
			}
		}
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		//playerMove(key);
		break;
	case 'a':
		//playerMove(key);
		break;
	case 's':
		//playerMove(key);
		break;
	case 'd':
		//playerMove(key);
		break;
	case 'b':
		buildMaze();
		//glutPostRedisplay();
		break;
	case 'p':
		solveMaze();
		//glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	}

	//glutPostRedisplay();
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
	glutReshapeFunc(reshape);
	//setWindow(windowLeft, windowRight, windowBottom, windowTop);
	//setViewport(0, viewportX, 0, viewportY);
	//glutMouseFunc(mouse);
	//glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}
