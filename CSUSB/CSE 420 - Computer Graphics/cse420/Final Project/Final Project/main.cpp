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
#include <vector>
#include <iostream>
#include <GL/glut.h>

#ifdef GL_VERSION_1_1
#define POINTER 1
#define INTERLEAVED 2

#define DRAWARRAY 1
#define ARRAYELEMENT  2
#define DRAWELEMENTS 3

int setupMethod = POINTER;
int derefMethod = DRAWARRAY;

int viewportX = 1280;
int viewportY = 720;
float windowLeft = -5.0;
float windowRight = 5.0;
float windowBottom = -5.0;
float windowTop = 5.0;

int tileSize = 100;

int playerX = 0 + (viewportX / 2);
int playerY = 0 + (viewportY / 2);

std::vector<GLint> maze;



//void addStraight(GLint v1x, GLint v1y, GLint v2x, GLint v2y, GLint v3x, GLint v3y, GLint v4x, GLint v4y, int direction)
void addStraight(GLint end1X, GLint end1Y, GLint end2X, GLint end2Y, int direction)
{
	//direction = 0 -> vertical going up -> | | 
	//direction = 1 -> vertical going down -> | |
	//direction = 2 -> horizontal going left -> ̅_
	//direction = 3 -> horizontal going right -> ̅_

	glColor3f(0.0, 0.0, 1.0);

	switch (direction)
	{
	case 0:	//up
		maze[0] = end1X;
		maze[1] = end1Y; //v1
		maze[2] = end1X;
		maze[3] = end1Y + 100; //v4
		maze[4] = end2X;
		maze[5] = end2Y; //v2
		maze[6] = end2X;
		maze[7] = end2Y + 100; //v3
		break;
	case 1: //down
		maze[0] = end1X;
		maze[1] = end1Y; //v4
		maze[2] = end1X;
		maze[3] = end1Y - 100; //v1
		maze[4] = end2X;
		maze[5] = end2Y - 100; //v2
		maze[6] = end2X;
		maze[7] = end2Y; //v3
		break;
	case 2:	//left
		maze[0] = end1X - 100;
		maze[1] = end1Y; //v1
		maze[2] = end1X;
		maze[3] = end1Y; //v2
		maze[4] = end2X;
		maze[5] = end2Y; //v3
		maze[6] = end2X;
		maze[7] = end2Y - 100; //v4
		break;
	case 3:	//right
		maze[0] = end1X;
		maze[1] = end1Y; //v1
		maze[2] = end1X + 100;
		maze[3] = end1Y; //v2
		maze[4] = end2X + 100;
		maze[5] = end2Y; //v3
		maze[6] = end2X;
		maze[7] = end2Y; //v4
		break;
	default:
		break;
	}

	/*
	switch (direction)
	{
	case 0:
		maze[0] = v1x;	//counter-clockwise direction
		maze[1] = v1y + 100;
		maze[2] = v4x;
		maze[3] = v4y + 100;
		maze[4] = v2x;
		maze[5] = v2y + 100;
		maze[6] = v3x;
		maze[7] = v3y + 100;
		break;
	case 1:
		maze[0] = v1x;	//counter-clockwise direction
		maze[1] = v1y - 100;
		maze[2] = v4x;
		maze[3] = v4y - 100;
		maze[4] = v2x;
		maze[5] = v2y - 100;
		maze[6] = v3x;
		maze[7] = v3y - 100;
		break;
	case 2:
		maze[0] = v1x + 100; //counter-clockwise direction
		maze[1] = v1y;
		maze[2] = v2x + 100;
		maze[3] = v2y;
		maze[4] = v3x + 100;
		maze[5] = v3y;
		maze[6] = v4x + 100;
		maze[7] = v4y;
		break;
	case 3:
		maze[0] = v1x - 100; //counter-clockwise direction
		maze[1] = v1y;
		maze[2] = v2x - 100;
		maze[3] = v2y;
		maze[4] = v3x - 100;
		maze[5] = v3y;
		maze[6] = v4x - 100;
		maze[7] = v4y;
		break;
	default:
		break;
	}
	*/
}

void addTurn(GLint v1x, GLint v1y, GLint v2x, GLint v2y, GLint v3x, GLint v3y, GLint v4x, GLint v4y, int direction)
{
	//direction = 0 -> up & left / right & down -> ̅ |
	//direction = 1 -> up & right / left & down -> |̅
	//direction = 2 -> down & left / right & up -> _|
	//direction = 3 -> down * right / left & up -> |_

	switch (direction)
	{
	case 0:
		
		break;
	case 1:
		
		break;
	case 2:
		
		break;
	case 3:
		
		break;
	default:
		break;
	}
}

void playerMove(char direction)
{
	//Move all pointers back n (# of vectors per tile * # of dimensions) times
	//4 tiles per vector * 2 for 2D = 8
	//to remove last tile and add room for new tile
	//Then determine new tile randomly
	//Call appropriate tile function

	/*
	for (int i = maze.size() - 1; i > 0; i--)
	{
		maze[i] = maze[i - 1];
	}
	*/

	//Move all pointers back 1 and adjust every other value in direction of movement
	//i.e. if going up, every other value (each Y) needs to be -100

	int y = 0;
	int x = 1;

	switch (direction)
	{
	case 'w':
		for (int i = maze.size() - 1; i > 0; i--)
		{
			if (y == 0)
			{
				y++;
			}
			else
			{
				maze[i] -= 100;
				y--;
			}
			maze[i] = maze[i - 1];
		}
		addStraight(maze[8], maze[9], maze[14], maze[15], 0); //v4, v3, direction
		std::cout << "Moved up" << std::endl;
		break;
	case 'a':
		for (int i = maze.size() - 1; i > 0; i--)
		{
			if (x == 0)
			{
				x++;
			}
			else
			{
				maze[i] += 100;
				x--;
			}
			maze[i] = maze[i - 1];
		}
		addStraight(maze[8], maze[9], maze[10], maze[11], 2); //v1, v2, direction
		std::cout << "Moved left" << std::endl;
		break;
	case 's':
		for (int i = maze.size() - 1; i > 0; i--)
		{
			if (y == 0)
			{
				y++;
			}
			else
			{
				maze[i] += 100;
				y--;
			}
			maze[i] = maze[i - 1];
		}
		addStraight(maze[8], maze[9], maze[12], maze[13], 1); //v2, v3, direction
		std::cout << "Moved down" << std::endl;
		break;
	case 'd':
		for (int i = maze.size() - 1; i > 0; i--)
		{
			if (x == 0)
			{
				x++;
			}
			else
			{
				maze[i] -= 100;
				x--;
			}
			maze[i] = maze[i - 1];
		}
		addStraight(maze[8], maze[9], maze[14], maze[15], 3); //v1, v4, direction
		std::cout << "Moved right" << std::endl;
		break;
	case 27:
		exit(0);
		break;
	}

	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_INT, 0, &maze.front());

	glLineWidth(2.0);
	glColor3f(0.0, 1.0, 0.0);
	glDrawArrays(GL_LINES, 0, 12);
	std::cout << "Line drawn" << std::endl;

	glDisableClientState(GL_VERTEX_ARRAY);

}

void playerTurn()
{

}

/*
void setupPointers(void)
{
	static GLint vertices[] = { 25, 25,
						100, 325,
						175, 25,
						175, 325,
						250, 25,
						325, 325 };
	static GLfloat colors[] = { 1.0, 0.0, 0.0,
			 0.0, 1.0, 0.0,
			 0.0, 0.0, 1.0,
						0.2, 0.2, 1.0,
						0.8, 1.0, 0.2,
					   0.75, 0.75, 0.75,
		//        0.35, 0.35, 0.35,
				0.0, 1, 0,
				0.5, 0.5, 0.5 };

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(2, GL_INT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
}
*/

/*
void setupInterleave(void)
{
	static GLfloat intertwined[] =
	{ 1.0, 0.2, 1.0, 100.0, 100.0, 0.0,
	 1.0, 0.2, 0.2, 0.0, 200.0, 0.0,
	 1.0, 1.0, 0.2, 100.0, 300.0, 0.0,
	 0.2, 1.0, 0.2, 200.0, 300.0, 0.0,
	 0.2, 1.0, 1.0, 300.0, 200.0, 0.0,
	 0.2, 0.2, 1.0, 200.0, 100.0, 0.0 };

	glInterleavedArrays(GL_C3F_V3F, 0, intertwined);
}
*/

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

	//v1
	maze.push_back(playerX - 50);
	maze.push_back(playerY - (viewportY / 2));
	//v2
	maze.push_back(playerX - 50);
	maze.push_back(playerY - 50);
	//v3
	maze.push_back(playerX + 50);
	maze.push_back(playerY - (viewportY / 2));
	//v4
	maze.push_back(playerX + 50);
	maze.push_back(playerY - 50);
	
	//v1
	maze.push_back(playerX - 50);
	maze.push_back(playerY - 50);
	//v2
	maze.push_back(playerX - 50);
	maze.push_back(playerY + 50);
	//v3
	maze.push_back(playerX + 50);
	maze.push_back(playerY - 50);
	//v4
	maze.push_back(playerX + 50);
	maze.push_back(playerY + 50);

	//v1
	maze.push_back(playerX - 50);
	maze.push_back(playerY + 50);
	//v2
	maze.push_back(playerX - 50);
	maze.push_back(playerY + (viewportY / 2));
	//v3
	maze.push_back(playerX + 50);
	maze.push_back(playerY + 50);
	//v4
	maze.push_back(playerX + 50);
	maze.push_back(playerY + (viewportY / 2));

	//gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
	//setupPointers();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//setupInterleave();
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	//   GLuint indices[6] = {0, 1, 2, 3, 4, 5};

	//    glDrawElements (GL_POLYGON, 6, GL_UNSIGNED_INT, indices);
  /*
	 glBegin (GL_TRIANGLES);
		glArrayElement ( 2 );
		glArrayElement ( 3 );
		glArrayElement ( 4 );
	 glEnd();
  */
  /*
	 if (derefMethod == DRAWARRAY)
		glDrawArrays (GL_TRIANGLES, 0, 6);
	 else if (derefMethod == ARRAYELEMENT) {
		glBegin (GL_TRIANGLES);
		glArrayElement (2);   //note: vertices 1, 3, 5 is a straight line
		glArrayElement (3);
		glArrayElement (5);
		glEnd ();
	 }
	 else if (derefMethod == DRAWELEMENTS) {
	   GLuint indices[4] = {0, 1, 3, 4};

		glDrawElements (GL_POLYGON, 4, GL_UNSIGNED_INT, indices);
	 }
  */
	
	
	//glVertexPointer(2, GL_INT, 0, vertices);
	
	
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(5, 2, 1);
	glutSolidCube(100);
	glPopMatrix();
	

	//Draw player position
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(10.0);
	glBegin(GL_POINTS);
	glVertex2i(playerX, playerY);
	glEnd();

	//Draw maze
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_INT, 0, &maze.front());

	glLineWidth(2.0);
	glColor3f(0.0, 1.0, 0.0);
	glDrawArrays(GL_LINES, 0, 12);
	std::cout << "Line drawn" << std::endl;

	//glDisableClientState(GL_VERTEX_ARRAY);
	
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

/*
void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			if (setupMethod == POINTER) {
				setupMethod = INTERLEAVED;
				setupInterleave();
			}
			else if (setupMethod == INTERLEAVED) {
				setupMethod = POINTER;
				setupPointers();
			}
			glutPostRedisplay();
		}
		break;
	case GLUT_MIDDLE_BUTTON:
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			if (derefMethod == DRAWARRAY)
				derefMethod = ARRAYELEMENT;
			else if (derefMethod == ARRAYELEMENT)
				derefMethod = DRAWELEMENTS;
			else if (derefMethod == DRAWELEMENTS)
				derefMethod = DRAWARRAY;
			glutPostRedisplay();
		}
		break;
	default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}
*/

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		playerMove(key);
		break;
	case 'a':
		playerMove(key);
		break;
	case 's':
		playerMove(key);
		break;
	case 'd':
		playerMove(key);
		break;
	case 27:
		exit(0);
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(viewportX, viewportY);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	setWindow(windowLeft, windowRight, windowBottom, windowTop);
	setViewport(0, viewportX, 0, viewportY);
	//glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

#else
int main(int argc, char** argv)
{
	fprintf(stderr, "This program demonstrates a feature which is not in OpenGL Version 1.0.\n");
	fprintf(stderr, "If your implementation of OpenGL Version 1.0 has the right extensions,\n");
	fprintf(stderr, "you may be able to modify this program to make it run.\n");
	return 0;
}
#endif
