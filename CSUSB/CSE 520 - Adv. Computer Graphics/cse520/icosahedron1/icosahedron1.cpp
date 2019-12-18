/*
  icosahedron1.cpp
  Sample program showing how to write GL shader programs.
  Shader sources are in files "icosahedron.vert" and "icosahedron.frag".
  @Author: T.L. Yu, 2008
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <cmath>
#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

/*
   Global handles for the currently active program object, with its two shader objects
*/
GLuint programObject = 0;
GLuint vertexShaderObject = 0;
GLuint fragmentShaderObject = 0;
static GLint win = 0;
int cLoc;
float theta[3];
int  thetaLoc[3];
int  aLoc;
int  txLoc;
float tx = 0.0;
int timeCounter = 0;	// time counter
int time_interval = 10;	// how much time has to be before action is done
float x = 0, y = 0, z = 0;
bool test = true;

GLfloat diffuseMaterial[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light[] = { 1, 1, 1 };


int readShaderSource(char *fileName, GLchar **shader )
{
    // Allocate memory to hold the source of our shaders.
    FILE *fp;
    int count, pos, shaderSize;
     
    fp = fopen( fileName, "r");
    if ( !fp )
        return 0;

    pos = (int) ftell ( fp );
    fseek ( fp, 0, SEEK_END );			//move to end
    shaderSize = ( int ) ftell ( fp ) - pos;	//calculates file size	
    fseek ( fp, 0, SEEK_SET ); 			//rewind to beginning
     
    if ( shaderSize <= 0 ){
        printf("Shader %s empty\n", fileName);
        return 0;
    }

    *shader = (GLchar *) malloc( shaderSize + 1);
    
    // Read the source code
   
    count = (int) fread(*shader, 1, shaderSize, fp);
    (*shader)[count] = '\0';

    if (ferror(fp))
        count = 0;

    fclose(fp);
    
    return 1;
}

void checkError()
{
    char *infoLog;
    int  infoLen, len;
    unsigned int shaders[2] = {vertexShaderObject,  fragmentShaderObject};
    char names[][50] = {"Vertex shader", "Fragment shader"};  
    for ( int i = 0; i < 2; i++ ) {
      glGetShaderiv( shaders[i], GL_INFO_LOG_LENGTH, &infoLen);
      if ( infoLen > 0 ) {
	infoLog = (char *) malloc ( infoLen + 1 );
	glGetShaderInfoLog ( shaders[i], infoLen, &len, infoLog );
	printf("\n***** %s: %s\n", names[i], infoLog );
	delete infoLog;
      }
    }
}

//  public 
int installShaders(const GLchar *vertex, const GLchar *fragment)
{
    GLint  vertCompiled, fragCompiled;  // status values
    GLint  linked;
   
    // Create a vertex shader object and a fragment shader object

    vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
    fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Load source code strings into shaders, compile and link

    glShaderSource(vertexShaderObject, 1, &vertex, NULL);
    glShaderSource(fragmentShaderObject, 1, &fragment, NULL);

    glCompileShader(vertexShaderObject);
    glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &vertCompiled);

    glCompileShader( fragmentShaderObject );
    glGetShaderiv( fragmentShaderObject, GL_COMPILE_STATUS, &fragCompiled);

    checkError();
    printf("vertCompiled, fragCompiled: %d, %d\n", vertCompiled, fragCompiled);
    if (!vertCompiled || !fragCompiled)
        return 0;

    // Create a program object and attach the two compiled shaders

    programObject = glCreateProgram();
    glAttachShader( programObject, vertexShaderObject);
    glAttachShader( programObject, fragmentShaderObject);

    // Link the program object 

    glLinkProgram(programObject);
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

    printf("linked=%d\n");
    if (!linked)
        return 0;

    // Install program object as part of current state

    glUseProgram(programObject);

    return 1;
}

void init_lighting()
{
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
//   GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light );
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

  // glColorMaterial(GL_FRONT, GL_DIFFUSE);  //default color blue?
 //  glEnable(GL_COLOR_MATERIAL);
}

int init(void)
{
   
   const char *version;
   GLchar *VertexShaderSource, *FragmentShaderSource;
   int loadstatus = 0;

   version = (const char *) glGetString(GL_VERSION);
   if (version[0] < '2' || version[1] != '.') {
      printf("This program requires OpenGL > 2.x, found %s\n", version);
      exit(1);
   }
   printf("version=%s\n", version );
   readShaderSource((char *) "icosahedron1.vert", &VertexShaderSource );
   readShaderSource( (char *) "icosahedron1.frag", &FragmentShaderSource );
   loadstatus = installShaders(VertexShaderSource, FragmentShaderSource);
  
   char names[][20] = {"color0", "color1", "color2"};
   int loc[3];
   for ( int i = 0; i < 3; i++ ) {
     loc[i] = glGetUniformLocation (programObject, names[i] ); 
     if ( loc[i] < 0 ) {
       cout << "No such name: " << names[i] << endl;
     }
   }

   glUniform4f ( loc[0], 1.0, 0, 0, 1 );
   glUniform4f ( loc[1], 0.0, 1.0, 0.0, 1 );
   glUniform4f ( loc[2], 0.0, 0, 1.0, 1 );
  
    
   char names1[][20] = { "ax", "ay", "az" };
   for ( int i = 0; i < 3; i++ ) { 
     thetaLoc[i] = glGetAttribLocation ( programObject, names1[i] );
     if ( thetaLoc[i] < 0 ) {
       cout << "No such name: " << names[i] << endl;
     }
    }

   cLoc = glGetAttribLocation ( programObject, "c" );
   aLoc = glGetAttribLocation ( programObject, "a" );
   txLoc = glGetAttribLocation ( programObject, "tx" );

   init_lighting();
   return loadstatus;
}

static void Reshape(int width, int height)
{
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-1.0, 1.0, -1.0, 1.0, 5.0, 25.0);
  // glFrustum(-20.0, 20.0, -20.0, 20.0, 150.0, 500.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0f, 0.0f, -15.0f);
   //glTranslatef(0.0f, 0.0f, -200.0f);
}

void CleanUp(void)
{
   glDeleteShader(vertexShaderObject);
   glDeleteShader(fragmentShaderObject);
   glDeleteProgram(programObject);
   glutDestroyWindow(win);
}

static void Idle(void)
{
  static int sign = 1;

  tx += 0.010f; // * sign;
  //tx = 1.0;
  if ( tx > 2 )
    sign = -1;
  else if ( tx < -2 )
    sign = 1;
        if ( timeCounter < time_interval) timeCounter++;       // increment time
        else    // time reached interval, increase rotation
        {
           timeCounter = 0;       //reset time
	   //for ( int i = 0; i < 3; i++ )
           //  theta[i]++;
           x++; y++; z++;
        }

   glutPostRedisplay();
}


static void Key(unsigned char key, int x, int y)
{
   switch(key) {
   case 27:
      CleanUp();
      exit(0);
      break;
   case 'r':
   case 't':
      theta[0] += 5;
      theta[1] += 10;
      theta[2] += 10;
      break;
   }
   glutPostRedisplay();
}

#define X .525731112119133606 
#define Z .850650808352039932

// rotation about different axis
//int x = 0;	int y = 0;	int z = 0;


// prototypes
void draw();	

//normalize a vector
void normalize(float v[3]) {    
   GLfloat d = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]); 
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

   out[0] = v1[1]*v2[2] - v1[2]*v2[1]; 
   out[1] = v1[2]*v2[0] - v1[0]*v2[2]; 
   out[2] = v1[0]*v2[1] - v1[1]*v2[0]; 
   normalize(out); 
}

/*
  Use subdivision to create 80-sided spherical approximation
*/
void drawtriangle(float *v1, float *v2, float *v3, float c ) 
{ 
   //glColor3fv ( color );
   glBegin(GL_TRIANGLES); 
      glVertexAttrib1f ( cLoc, c );
      glNormal3fv(v1); glVertex3fv(v1);    
      glVertexAttrib1f ( cLoc, c );
      glNormal3fv(v2); glVertex3fv(v2);    
      glVertexAttrib1f ( cLoc, c );
      glNormal3fv(v3); glVertex3fv(v3);    
   glEnd(); 
		
   //glColor3f ( 0.0, 0.0, 0.0 );
   glBegin(GL_LINE_LOOP);  
      glVertexAttrib1f ( cLoc, 0.0 );
      glVertex3fv(v1);
      glVertex3fv(v2);
      glVertex3fv(v3);
   glEnd(); 
}

void subdivide(float *v1, float *v2, float *v3, float color, int level ) 
{ 
   GLfloat v12[3], v23[3], v31[3];    
   GLint i;

   for (i = 0; i < 3; i++) { 
      v12[i] = ( v1[i]+v2[i] ) / 2.0; 
      v23[i] = ( v2[i]+v3[i] ) / 2.0;     
      v31[i] = ( v3[i]+v1[i] ) / 2.0;    
   } 
   normalize(v12);	//The normalize procedure 'push out' the vertex ( make it 3-D )    
   normalize(v23); 
   normalize(v31); 
   if ( level > 0 ) {
     subdivide ( v12, v23, v31, color, level-1);
     subdivide (v1, v12, v31, color, level-1);
     subdivide (v2, v23, v12, color, level-1);
     subdivide (v3, v31, v23,color, level-1);
   } else {
     drawtriangle(v1, v12, v31, color);    
     drawtriangle(v2, v23, v12, color);    
     drawtriangle(v3, v31, v23,color);    
     drawtriangle(v12, v23, v31, color); 
   }
}

void draw()	// draw icosahedron
{		
	static GLfloat vdata[12][3] = 
	{    
		{-X ,  0.0,  Z }, 
		{ X ,  0.0,  Z }, 
		{-X ,  0.0, -Z }, 
		{ X ,  0.0, -Z },    
		{ 0.0,  Z ,  X }, 
		{ 0.0,  Z , -X }, 
		{ 0.0, -Z ,  X }, 
		{ 0.0, -Z , -X },    
		{ Z ,  X ,  0.0}, 
		{-Z ,  X ,  0.0}, 
		{ Z , -X ,  0.0}, 
		{-Z , -X ,  0.0} 
	};
	
	static GLuint tindices[20][3] = 
	{ 
		 {0,4,1},  {0,9,4},  {9,5,4},  {4,5,8}, {4,8,1},    
		{8,10,1}, {8,3,10},  {5,3,8},  {5,2,3}, {2,7,3},    
		{7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
		{6,1,10}, {9,0,11}, {9,11,2}, { 9,2,5}, {7,2,11} 
	};

      float color;
        for (int i = 0; i < 20; i++) { 
	  color = ( i % 5 ) / 4.0 + 0.05;
	  // glColor3f(i*i/19.0/19.0, (i * 3) % 4 / 4, 1 - i/19.0);
/*	 if ( i % 2 == 0 )
	    color = i*i/19.0/19.0;
         else
	    color = 1.05 - i*i/19.0/19.0;
  */       // color =  (i * 3) % 4 / 4.0;
          //color =  1 - i/19.0;
           subdivide(&vdata[tindices[i][0]][0],       
             &vdata[tindices[i][1]][0],       
             &vdata[tindices[i][2]][0], color, 2 ); 
        }
		
	// draw the black outline
	glColor3f(0.0,0.0,0.0);
	for (int i = 0; i < 20; i++) 
	{    
		glBegin(GL_LINE_LOOP);  
			glVertex3fv( &vdata[ tindices[i][0] ][0]); 
			glVertex3fv( &vdata[ tindices[i][1] ][0]); 
			glVertex3fv( &vdata[ tindices[i][2] ][0]);
		glEnd(); 
	}
}

void display(void)
{
   GLfloat vec[4];

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor( 1.0, 1.0, 1.0, 1.0 );	//get white background color
   glColor3f ( 0, 0, 1 );  		//red, this will have no effect if shader is loaded

   for ( int i = 0; i < 3; i++ )  
     glVertexAttrib1f ( thetaLoc[i], theta[i] );
     
   glVertexAttrib3f ( aLoc, x, y, z );
   glVertexAttrib1f ( txLoc, tx );
   
   draw();
  // glutSolidSphere(1.0, 20, 16);

   glutSwapBuffers();
   glFlush();
}



int main(int argc, char *argv[])
{
   int success = 0;

   glutInit(&argc, argv);
   glutInitWindowPosition( 0, 0);
   glutInitWindowSize(600, 600);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   win = glutCreateWindow(argv[0]);
   glutReshapeFunc(Reshape);
   glutKeyboardFunc(Key);
   glutDisplayFunc(display);
   glutIdleFunc(Idle);

   // Initialize the "OpenGL Extension Wrangler" library
    glewInit();

   success = init();
   printf("success=%d\n", success );
   if ( success )
     glutMainLoop();
   return 0;
}

