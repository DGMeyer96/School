//Daniel Meyer
//CSE 420
//Fall 2018

//draw_main.cpp: main loop of drawing program

#include <math.h>
#include <stdlib.h> //Must come before GL/glut.h in VS
#include <GL/glut.h>
#include <stdio.h>

//initialization
void init(void);
//does the drawing 
void display(void);

/*  Main Loop
 *  Open window with initial window size, title bar,
 *  RGB display mode, depth buffer.
 */

int main(int argc, char** argv)
{
	glutInit(&argc, argv);	//initialize toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//set display mode: single bufferring, RGBA model
	glutInitWindowSize(500, 500);		//set window size on screen
	glutInitWindowPosition(100, 150); 	//set window position on screen
	glutCreateWindow(argv[0]);		//open screen window
	init();
	glutDisplayFunc(display);		//points to display function
	glutMainLoop();			//go into perpetual loop
	return 0;
}
