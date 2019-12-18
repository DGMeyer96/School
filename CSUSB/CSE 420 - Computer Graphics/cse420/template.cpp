
#include <stdio.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GL/glut.h>

//initialization
void init( void )
{
  glClearColor( 1.0, 1.0, 1.0, 0.0 );	//get white background color
  glColor3f( 0.0f, 0.0f, 0.0f );	//set drawing color
  gluOrtho2D( 0.0, 50.0, 0.0, 50.0 );
}


void display( void )
{
  glClear( GL_COLOR_BUFFER_BIT );	//clear screen
  glFlush();				//send all output to screen
}

void keyboard ( unsigned char key, int mousex, int mousey )
{
   switch ( key ) {
     case 27:       // escape
       exit ( -1 );
   }
   glutPostRedisplay();
}

void specialKey ( int key, int mousex, int mousey )
{
 switch ( key ) {
  case GLUT_KEY_UP:
       break;
  case GLUT_KEY_DOWN:
       break;
  case GLUT_KEY_LEFT:
   	break;
  case GLUT_KEY_RIGHT:
 	break;
  }
  glutPostRedisplay();
}

void myMouse( int button, int state, int x, int y )
{
  if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN );
  glFlush();                            //send all output to screen
}


/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, depth buffer.
 */
int main(int argc, char** argv)
{
  glutInit(&argc, argv);	//initialize toolkit
  glutInitDisplayMode (GLUT_SINGLE| GLUT_RGB );	//set display mode
  glutInitWindowSize(800, 800);		//set window size on screen
  glutInitWindowPosition( 100, 150 ); 	//set window position on screen
  glutCreateWindow(argv[0]);		//open screen widow
  init();
  glutDisplayFunc (display);		//points to display function
  glutKeyboardFunc ( keyboard );
  glutSpecialFunc( specialKey );
  glutMouseFunc( myMouse );

  glutMainLoop();			//go into perpetual loop
  return 0;
}
