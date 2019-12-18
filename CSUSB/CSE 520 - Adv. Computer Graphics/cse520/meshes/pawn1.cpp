
/*  pawn1.cpp
 *  Construct surfaces of revolution but have not considered lighting and wireframe is used.
 *  Surface is generated by revolving a curve around x-axis.			
 *  A curve f(x) is generated by polynomial interpretation from some control points
 *  or by some interested functions.
 *  Display list is used to speed up process.
 *  
 *  @Author: T.L. Yu, Fall 2008 
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "lib3ds_vector.h"

using namespace std;

const double PI = 3.14159265389;
const int Npoints = 27;
//const int Npoints = 6;
const int m_order = 4;
int anglex= 0, angley = 0, anglez = 0;          //rotation angles
int window;

GLuint thePawn;
void pawn (int nx, int ntheta, float startx, float endx );

//control points

/*
GLfloat ctrlpoints[Npoints][3] = {
//	{ 0.0, 0.0, 0.0}, { 0.5, 1.0, 0.0 }, 
//	{1.2, 2.0, 0.0}, {3, 3.0, 0}, {3.3, 3.2, 0}, {3.5, 3.4, 0}};
	{ 3.5, 0.0, 0.0}, { 3.2, 0.5, 0.0 }, 
	{2.5, 1.2, 0.0}, {2.2, 2, 0}, {0.8, 2.5, 0}, {0.0, 3.0, 0}};
//	{ 0, 3.5, 0.0}, { 1, 3, 0.0 }, 
//	{2, 2, 0.0}, {2.5, 1.5,0 }, {3, 0.5, 0}, {3.5, 0.0, 0}};
*/

GLfloat ctrlpoints[Npoints][3] = {
{4.38,0.00, 0},{4.22,0.50, 0},{3.98,0.72, 0},{3.62,0.80, 0},{3.24,0.66, 0},
{3.10,0.56, 0},{2.92,0.80, 0},{2.76,0.88, 0},{2.58,0.74, 0},{2.48,0.44, 0},
{2.10,0.48, 0},{1.74,0.60, 0},{1.54,0.66, 0},{1.44,0.90, 0},{1.10,1.04, 0},
{0.90,1.18, 0},{0.76,1.38, 0},{0.68,1.48, 0},{0.62,1.48, 0},{0.58,1.44, 0},
{0.52,1.36, 0},{0.44,1.38, 0},{0.30,1.46, 0},{0.28,1.54, 0},{0.22,1.50, 0},
{0.10,1.50, 0},{0.00,1.50, 0}
};

void init(void)
{
   glClearColor(1.0, 1.0, 1.0, 1.0);
  // glPolygonMode( GL_FRONT, GL_LINE ) ;
  // glPolygonMode( GL_BACK,  GL_LINE ) ;
   glEnable( GL_CULL_FACE );
   glCullFace ( GL_BACK );
  // glPolygonMode( GL_FRONT, GL_LINE );
  glPolygonMode( GL_FRONT, GL_FILL );

   thePawn = glGenLists (1);
   glNewList(thePawn, GL_COMPILE);
   pawn(32, 64, 0, 3.5);
   glEndList();
   glShadeModel(GL_SMOOTH);
   
   //lighting
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light[] = { 1.0, 1.0, 1.0 };
   GLfloat light1[] = { 1.0, 1.0, 1.0 };
   //GLfloat light1[] = { 0.2, 1.0, 0.2 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
   GLfloat light_position1[] = { -1.0, -1.0, -1.0, 0.0 };
   GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
   glClearColor (1.0, 1.0, 1.0, 0.0);
   //glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

   glLightfv(GL_LIGHT0, GL_DIFFUSE, light );
   glLightfv(GL_LIGHT0, GL_SPECULAR, light );
   glLightfv(GL_LIGHT1, GL_DIFFUSE, light1 );
   glLightfv(GL_LIGHT1, GL_SPECULAR, light1 );
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
   glEnable(GL_DEPTH_TEST);
}

/*
 *   Build standard knot vector for n control points
 *   and B-splines of order m
 */
void buildKnots ( int m, int n, float knot[] )
{
  if ( n < m  ) return;         //not enough control points
  for ( int i = 0; i < n + m; ++i ){
    if (i < m) knot[i] = 0.0;
    else if (i < n) knot[i] = i - m + 1;        //i is at least m here
    else knot[i] = n - m + 1;
  }
}

//evaluate blending functions recurvsively
float bSpline ( int k, int m, float u, float knot[] )
{
  float d1, d2, sum = 0.0;

  if ( m == 1 )
    return ( knot[k] < u &&  u <= knot[k+1] );   //1 or 0

  //m larger than 1, so recurse
   d1 = knot[k+m-1] - knot[k];
  if ( d1 != 0 )
    sum = (u - knot[k]) * bSpline(k,m-1,u, knot) / d1;
  d2 = knot[k+m] - knot[k+1];
  if ( d2 != 0 )
    sum += (knot[k+m] - u) * bSpline(k+1, m-1, u, knot) / d2;

  return sum;
}

//non uniform rational B-splines, n control points, order m, p[] is the output point
void nurb ( float control_points[][3], float u, float knot[], float p[] )
{
  // sum the control points mulitplied by their respective blending functions
   for ( int i = 0; i < 3; ++i ){        //x, y, z components
    p[i] = 0;
    for ( int k = 0; k < Npoints; ++k )
      p[i] += bSpline(k, m_order, u, knot ) * control_points[k][i];
  }
}


//polynomial interpretation for N points
float polyint ( float  points[][3], float x, int N )
{
  float y;

  float num = 1.0, den = 1.0;
  float sum = 0.0;

  for ( int i = 0; i < N; ++i ) {
    num = den = 1.0;
    for ( int j = 0; j < N; ++j ) {
      if ( j == i ) continue;

      num = num * ( x - points[j][0] );		 	//x - xj
    }
    for ( int j = 0; j < N; ++j ) {
      if ( j == i ) continue;
      den = den * ( points[i][0] - points[j][0] );	//xi - xj
    }
    sum += num / den * points[i][1];
  }
  y = sum;

  return y;
}

float aLine ( float x )
{
  return x + 2.5;
}

//cubic B-spline, a special case of NURB
void bspline ( float  points[][3], float t, float out[] )
{
  // the t value inverted
  float it = 1.0f-t;

  // calculate blending functions
  float b0 = it*it*it;
  float b1 = 3*t*it*it;
  float b2 = 3*t*t*it;
  float b3 = t*t*t;

  // sum the control points mulitplied by their respective blending functions
  out[0] = b0*points[0][0] + b1*points[1][0] + b2*points[2][0] + b3*points[3][0];       //x
  out[1] = b0*points[0][1] + b1*points[1][1] + b2*points[2][1] + b3*points[3][1];       //y
  out[2] = b0*points[0][2] + b1*points[1][2] + b2*points[2][2] + b3*points[3][2];       //z
}

void testing()
{
  int n = Npoints, m = m_order; 
  float knot[n+m];

  buildKnots ( m,  n, knot );

  for ( int i = 0; i < n + m; i++ )
    printf("%4.2f,", knot[i] );

  printf("\n");
}


void pawn (int nx, int ntheta, float startx, float endx )
{
   const int n = Npoints, m = m_order;	//n control points, degree m NURB
   float knot[n+m];
   
   const float dx = (endx - startx)/nx;	//x step size
   const float dtheta = 2*PI / ntheta;	//angular step size
   float theta = PI/2.0;		//from pi/2 to3pi/2
   buildKnots(m, n, knot);
   
   int i, j;
   float x, y, z, r;			//current coordinates
   float x1, y1, z1, r1;		//next coordinates
   float t, v[3];
   float va[3], vb[3], vc[3], normal[3];
   int nturn = 0; 
   x = startx;
   nurb ( ctrlpoints, 0, knot, v );
   x = v[0];
   r = v[1];
   bool first_point = true;
   for ( int k = m-1; k < n; ++k ) {	//step through the knots
      float dknot = knot[k+1] - knot[k];
      if ( dknot == 0 ) continue;

      theta = 0;	//PI / 2.0;
      int start=0, nn=60, end=nn;
    //  if ( k == n - 1 ) end = nn;
      for (i = start; i <= end; i++) {
       t = knot[k] + dknot * (float) i /nn;
       nurb (ctrlpoints, t, knot, v);
       if ( first_point ) {
          v[0] = ctrlpoints[0][0];
          v[1] = ctrlpoints[0][1];
          first_point = false;
       }
       x1 =  v[0];
       r1 = v[1];

       //draw the surface composed of quadrilaterals by sweeping theta
       glBegin( GL_QUAD_STRIP );
	for ( j = 0; j <= ntheta; ++j ) {
	  theta += dtheta;
	  double cosa = cos( theta );
	  double sina = sin ( theta );
	  y = r * cosa;  y1 = r1 * cosa;	//current and next y 
	  z = r * sina;	 z1 = r1 * sina;	//current and next z
	  if ( nturn == 0 ) {
	    va[0] = x;	va[1] = y; 	va[2] = z; 
	    vb[0] = x1;	vb[1] = y1; 	vb[2] = z1; 
	    nturn++;
	  } else {
	    nturn = 0;
	    vc[0] = x;	vc[1] = y; 	vc[2] = z; 
	    vector_normal ( normal, va, vb, vc );
	    glNormal3f ( normal[0], normal[1], normal[2] );	 
	  }
	  //edge from point at x to point at next x
	  glVertex3f (x, y, z);
	  glVertex3f (x1, y1, z1);
	  //forms quad with next pair of points with incremented theta value	
	}			  	
      glEnd();
      x = x1;
      r = r1;	
     }
   } //for k 
}

//revolve about y-axis
void display(void)
{

   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0, 1.0, 1.0);
   const float startx = 0, endx = 3.5;
   const int nx = 32;			//number of slices along x-direction
   const int ntheta = 64;		//number of angular slices

   glPushMatrix();
   glRotatef( anglex, 1.0, 0.0, 0.0); 	//rotate the object about x-axis
   glRotatef( angley, 0.0, 1.0, 0.0);  	//rotate about y-axis   
   glRotatef( anglez, 0.0, 0.0, 1.0);	//rotate about z-axis
   
   glEnable(GL_LIGHTING);
 
   glCallList ( thePawn );
   /* The following code displays the control points as dots. */

   glDisable(GL_LIGHTING);
   glPointSize(5.0);
   glColor3f(1.0, 0.0, 1.0);
   glBegin(GL_POINTS);
      for (int i = 0; i < Npoints; i++) 
         glVertex3fv(&ctrlpoints[i][0]);
   glEnd();

   glPopMatrix();
   glFlush();
}


void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w, 
               5.0*(GLfloat)h/(GLfloat)w, -5.0, 5.0);
   else
      glOrtho(-5.0*(GLfloat)w/(GLfloat)h, 
               5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -5.0, 5.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}


/*
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt ( 0, 0, 15, 0, 0, 0, 0, 1, 0 );
}
*/

void keyboard(unsigned char key, int x, int y)
{
  switch(key) {
    case 'x':
      anglex = ( anglex + 3 ) % 360;
      break;
    case 'X':
      anglex = ( anglex - 3 ) % 360;
      break;
    case 'y':
      angley = ( angley + 3 ) % 360;
      break;
    case 'Y':
      angley = ( angley - 3 ) % 360;
      break;
    case 'z':
      anglez = ( anglez + 3 ) % 360;
      break;
    case 'Z':
      anglez = ( anglez - 3 ) % 360;
      break;
    case 'r':					//reset
      anglez = angley = anglex = 0;
      glLoadIdentity();
      break;
    case 27: /* escape */
        glutDestroyWindow(window);
        exit(0);
  }
  glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (800, 800);
   glutInitWindowPosition (100, 100);
   window = glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc (keyboard);
   glutMainLoop();
   return 0;
}
