/*
  brick.cpp
  Sample program showing how to write GL shader programs.
  Shader sources are in files "brick.vert" and "tests.frag".
  @Author: T.L. Yu, 2009
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>


using namespace std;

/*
   Global handles for the currently active program object, with its two shader objects
*/
GLuint programObject = 0;
GLuint vertexShaderObject = 0;
GLuint fragmentShaderObject = 0;
static GLint win = 0;

int anglex= 0, angley = 0, anglez = 0;          //rotation angles
int objectType = 0; 

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

    if (!vertCompiled || !fragCompiled)
        return 0;

    // Create a program object and attach the two compiled shaders

    programObject = glCreateProgram();
    glAttachShader( programObject, vertexShaderObject);
    glAttachShader( programObject, fragmentShaderObject);

    // Link the program object 

    glLinkProgram(programObject);
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

    if (!linked)
        return 0;

    // Install program object as part of current state

    glUseProgram(programObject);

    // Set up initial uniform values
    glUniform3f(glGetUniformLocation(programObject, "BrickColor"), 1.0, 0.3, 0.2);
    glUniform3f(glGetUniformLocation(programObject, "MortarColor"), 0.85, 0.86, 0.84);
    glUniform2f(glGetUniformLocation(programObject, "BrickSize"), 0.20, 0.1);
    glUniform2f(glGetUniformLocation(programObject, "BrickPct"), 0.90, 0.85);
    glUniform3f(glGetUniformLocation(programObject, "LightPosition"), 0.0, 0.0, 4.0);

    return 1;
}

void drawCube(void)
{
    float size = 1.0f;
    float scale = 0.2f;
    float delta = 0.1f;

    float A[3] = { size,  size,  size * scale + delta };
    float B[3] = { size,  size, -size * scale + delta };
    float C[3] = { size, -size, -size * scale };
    float D[3] = { size, -size,  size * scale };
    float E[3] = {-size,  size,  size * scale + delta };
    float F[3] = {-size,  size, -size * scale + delta };
    float G[3] = {-size, -size, -size * scale };
    float H[3] = {-size, -size,  size * scale };

    float I[3] = { 1.0f,  0.0f,  0.0f};
    float K[3] = {-1.0f,  0.0f,  0.0f};
    float L[3] = { 0.0f,  0.0f, -1.0f};
    float M[3] = { 0.0f,  0.0f,  1.0f};
    float N[3] = { 0.0f,  1.0f,  0.0f};
    float O[3] = { 0.0f, -1.0f,  0.0f};

    glBegin(GL_QUADS);

    glNormal3fv(I);

    glVertex3fv(D);
    glVertex3fv(C);
    glVertex3fv(B);
    glVertex3fv(A);

    glNormal3fv(K);

    glVertex3fv(G);
    glVertex3fv(H);
    glVertex3fv(E);
    glVertex3fv(F);

    glNormal3fv(L);

    glVertex3fv(C);
    glVertex3fv(G);
    glVertex3fv(F);
    glVertex3fv(B);

    glNormal3fv(M);

    glVertex3fv(H);
    glVertex3fv(D);
    glVertex3fv(A);
    glVertex3fv(E);

    glNormal3fv(N);

    glVertex3fv(E);
    glVertex3fv(A);
    glVertex3fv(B);
    glVertex3fv(F);

    glNormal3fv(O);
    glVertex3fv(G);
    glVertex3fv(C);
    glVertex3fv(D);
    glVertex3fv(H);

    glEnd();
}


int init(void)
{
   
   const char *version;
   GLchar *VertexShaderSource, *FragmentShaderSource;
   int loadstatus = 0;

   version = (const char *) glGetString(GL_VERSION);
   if (version[0] < '2' || version[1] != '.') {
      printf("This program requires OpenGL >= 2.x, found %s\n", version);
      exit(1);
   }

   glDepthFunc(GL_LESS);
   glEnable(GL_DEPTH_TEST);
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


   readShaderSource("brick.vert", &VertexShaderSource );
   readShaderSource("brick.frag", &FragmentShaderSource );
   loadstatus = installShaders(VertexShaderSource, FragmentShaderSource);
  
 //  timeParam = glGetUniformLocation ( programObject, "time" ); 
 //  velParam = glGetAttribLocation ( programObject, "vel" ); 
   return loadstatus;
}

static void Reshape(int w, int h)
{
    float vp = 0.8f;
    float aspect = (float) w / (float) h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // glOrtho(-1.0, 1.0, -1.0, 1.0, -10.0, 10.0);
    glFrustum(-vp, vp, -vp / aspect, vp / aspect, 3, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}
    
void CleanUp(void)
{
   glDeleteShader(vertexShaderObject);
   glDeleteShader(fragmentShaderObject);
   glDeleteProgram(programObject);
   glutDestroyWindow(win);
}

static void Key(unsigned char key, int x, int y)
{
   switch(key) {
   case 27:
      CleanUp();
      exit(0);
      break;
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
    case 'r':
      anglex = angley = anglez = 0;
      break;
    case 't':
      objectType = (objectType + 1 ) % 4;
      break;     
   }
   glutPostRedisplay();
}

void display(void)
{
   GLfloat vec[4];

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClearColor( 1.0, 1.0, 1.0, 0.0 );		//get white background color
 
   glPushMatrix();
   glRotatef( anglex, 1.0, 0.0, 0.0);                   //rotate the cube along x-axis
   glRotatef( angley, 0.0, 1.0, 0.0);                   //rotate along y-axis   
   glRotatef( anglez, 0.0, 0.0, 1.0);                   //rotate along z-axis 
   if ( objectType == 0 )
     drawCube();
   else if ( objectType == 1 )
     glutSolidSphere ( 0.6, 64, 64 );
   else if ( objectType == 2 )
     glutSolidTorus(0.2, 0.6, 32, 32);
   else
      glutSolidTeapot(0.6f);
   
   glPopMatrix();
   glutSwapBuffers();
   glFlush();

}


int main(int argc, char *argv[])
{
   int success = 0;

   glutInit(&argc, argv);
   glutInitWindowPosition( 0, 0);
   glutInitWindowSize(800, 800);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   win = glutCreateWindow(argv[0]);
   glutReshapeFunc(Reshape);
   glutKeyboardFunc(Key);
   glutDisplayFunc(display);
   
   // Initialize the "OpenGL Extension Wrangler" library
    glewInit();

   success = init();
   if ( success )
     glutMainLoop();
   return 0;
}

