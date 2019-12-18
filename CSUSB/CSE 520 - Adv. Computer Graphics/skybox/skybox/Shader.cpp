/*  Shader.cpp
 *  Compile: g++ -c Shader.cpp
 */
#include <string>
#include "Shader.h"
#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

Shader::Shader()
{
	infoLog = NULL;
}

Shader::~Shader()
{
	if (infoLog != NULL)
		delete infoLog;
}
// Create a Shader object
// User provides vertex shader code (vs) and fragement shader code (fs)
bool  Shader::createShader(const string *vs, const string *fs)
{
	// create empty OpenGL   Program,load,attach,and link shaders
	programObject = glCreateProgram();
	if (vs != NULL) {
		vertexShaderObject = loadShader(GL_VERTEX_SHADER, vs);
		// add the vertex shader to program
		glAttachShader(programObject, vertexShaderObject);
	}
	if (fs != NULL) {
		fragmentShaderObject = loadShader(GL_FRAGMENT_SHADER, fs);
		// add the fragment shader to program
		glAttachShader(programObject, fragmentShaderObject);
	}
	glLinkProgram(programObject); // creates   program executables
	int linked;
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

	if (!linked) {
		printf("Shader not linked!\n");
		return false;
	}

	glUseProgram(programObject); // use shader program

	return true;
}

int Shader::loadShader(int shaderType, const string *shaderCode)
{

	// create a vertex shader type ( GL_VERTEX_SHADER)
	// or a fragment shader type ( GL_FRAGMENT_SHADER)
	int shader = glCreateShader(shaderType);

	// pass source code to the shader and compile it
	char *strPointer = (char *)shaderCode->c_str();
	glShaderSource(shader, 1, &strPointer, NULL);
	glCompileShader(shader);
	int compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	printf("Shader type=%d\n", shaderType );
	if (!compiled)
		printf("Compiling %d failed!\n", shaderType);
	else
	{
		printf("------------\n");
		printf("%s", strPointer);
		printf("\n--------------\n");
	}

	int maxLength;
	glGetShaderiv(shaderType, GL_INFO_LOG_LENGTH, &maxLength);

	// maxLength includes NULL character
	infoLog = (char *)malloc(sizeof(char) * maxLength);
	glGetShaderInfoLog(vertexShaderObject, maxLength, &maxLength, infoLog);

	//cout << infoLog << endl;

	return shader;
}

void Shader::cleanUp()
{
	glDeleteProgram(programObject);
	glDeleteShader(vertexShaderObject);
	glDeleteShader(fragmentShaderObject);
}

int Shader::readShaderFile(char *fileName, char **shader)
{
	// Allocate memory to hold the source of our shaders.
	FILE *fp;
	int count, pos, shaderSize;

	fp = fopen(fileName, "r");
	if (!fp)
		return 0;

	pos = (int)ftell(fp);
	fseek(fp, 0, SEEK_END);			//move to end
	shaderSize = (int)ftell(fp) - pos;	//calculates file size	
	fseek(fp, 0, SEEK_SET); 			//rewind to beginning

	if (shaderSize <= 0) {
		printf("Shader %s empty\n", fileName);
		return 0;
	}

	*shader = (char *)malloc(shaderSize + 1);

	if (*shader == NULL)
		printf("memory allocation error\n");
	// Read the source code
	count = (int)fread(*shader, 1, shaderSize, fp);
	(*shader)[count] = '\0';

	if (ferror(fp))
		count = 0;

	fclose(fp);

	return 1;
}

