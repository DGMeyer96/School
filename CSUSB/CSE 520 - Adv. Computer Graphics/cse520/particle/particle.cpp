/*
  tests.cpp
  Sample program showing how to write GL shader programs.
  Shader sources are in files "tests.vert" and "tests.frag".
  @Author: T.L. Yu, 2008
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;
int timeParam;        // ~loc
int velParam;

/*
   Global handles for the currently active program object, with its two shader objects
*/
GLuint programObject = 0;
GLuint vertexShaderObject = 0;
GLuint fragmentShaderObject = 0;
static GLint win = 0;

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
        printf("\n%s shader info: %s\n", names[i], infoLog );
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

    //printf("linked=%d\n");
    if (!linked)
        return 0;

    // Install program object as part of current state

    glUseProgram(programObject);


    int loc;
    timeParam = glGetUniformLocation ( programObject, "time1" );
    velParam = glGetAttribLocation ( programObject, "vel" );

    return 1;
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
   readShaderSource((char *) "particle.vert", &VertexShaderSource );
   readShaderSource( (char *) "tests.frag", &FragmentShaderSource );
   loadstatus = installShaders(VertexShaderSource, FragmentShaderSource);
   
   return loadstatus;
}

static void Reshape(int width, int height)
{
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-1.0, 1.0, -1.0, 1.0, 5.0, 25.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0f, 0.0f, -15.0f);
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
   float t = glutGet ( GLUT_ELAPSED_TIME );
   while ( t > 3000 ) t -= 3000;
   glUniform1f ( timeParam, t );
   glutPostRedisplay();
}


static void Key(unsigned char key, int x, int y)
{
   switch(key) {
   case 27:
      CleanUp();
      exit(0);
      break;
   }
   glutPostRedisplay();
}

void display(void)
{
   GLfloat vec[4];
   srand(time(NULL));
   float vx1 = (rand() % (-3 + 2)) - 2;
   float vx2 = (rand() % (-3 + 2)) - 2;
   float vx3 = (rand() % (-3 + 2)) - 2;
   float vy1 = (rand() % (2 + 1)) - 1;
   float vy2 = (rand() % (2 + 1)) - 1;
   float vy3 = (rand() % (2 + 1)) - 1;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor( 1.0, 1.0, 1.0, 1.0 );	//get white background color
   glPointSize ( 8 );          
   glBegin ( GL_POINTS );
     glVertexAttrib3f ( velParam, 5.0, 5.0, 0 );
     //glVertex3f ( -2.5, 0.0, 1.0 );
      glVertex3f(vx1, vy1, 1.0);
      glVertex3f(vx2, vy2, 1.0);
      glVertex3f(vx3, vy3, 1.0);
   glEnd();
   glutSwapBuffers();
   glFlush();
}


int main(int argc, char *argv[])
{
   int success = 0;

   glutInit(&argc, argv);
   glutInitWindowPosition( 0, 0);
   glutInitWindowSize(500, 500);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   win = glutCreateWindow(argv[0]);
   glutReshapeFunc(Reshape);
   glutKeyboardFunc(Key);
   glutDisplayFunc(display);
   glutIdleFunc(Idle);

   // Initialize the "OpenGL Extension Wrangler" library
    glewInit();

   success = init();
  // printf("success=%d\n", success );
   if ( success )
     glutMainLoop();
   return 0;
}

