#ifndef _CUBE_H
#define _CUBE_H
#include "Shader.h"
#include <vector>

using namespace std;

class XYZ {
public:
	float x, y, z;
};

class Cube : public Shader
{
private:
	static const string vsCode;   // Source code of vertex shader
	static const string fsCode;  // Source code of fragment shader
	GLubyte *makeTexImage(char *loadfile);
	static const int iWidth = 64;
	static const int iHeight = 64;
	GLubyte checkImage[iHeight][iWidth][3];

	void makeCheckImage(void);

	vector<XYZ> vertices;
	vector<XYZ> texPoints;
	// Set color with red, green, blue and alpha (opacity) values
	float *sphereCoords;
	float *texCoords;
	short *drawOrders;            //draw order list
	int nTriangles;
	//unsigned texName;
	unsigned tex_cube;
	int texImageWidth;
	int texImageHeight;
public:
	static const float eyePos[4];  // = {0, 0, 6.3, 1};	viewing position
	Cube(int &success);
	~Cube();
	void init2DTexture();
	void draw(float mvpMatrix[4][4]);
};
#endif

