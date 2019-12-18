#ifndef _SHADER_H
#define _SHADER_H
#include <string>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

class Shader
{
public:
	int programObject;
	int vertexShaderObject;
	int fragmentShaderObject;
	char *infoLog;
	Shader();
	~Shader();
	int  loadShader(int shaderType, const string *shaderCode);
	bool createShader(const string *vs, const string *fs);
	int  readShaderFile(char *fileName, char **shader);
	void cleanUp();
};

#endif

