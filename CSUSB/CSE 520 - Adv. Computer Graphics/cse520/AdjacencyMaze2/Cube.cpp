// Cube.cpp : 
#include <math.h>
#include <stdio.h>
#include <vector>
#include <string>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "imageio.h"
//#include "SOIL/SOIL.h"
#include "Cube.h"

using namespace std;

static GLuint texture;

//int anglex= 0, angley = 0, anglez = 0;          //rotation angles
char maps[][20] = { "back.png",  "front.png",  "top.png", "bottom.png",
												"left.png", "right.png" };
GLenum texAxis[] = { GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
						GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_X };


Cube::Cube(int  &success)
{
	string *vs, *fs;
	char *vsSource, *fsSource;

	// Read shader source code.
	readShaderFile((char *) "skybox.vert", &vsSource);
	readShaderFile((char *) "skybox.frag", &fsSource);
	vs = new string(vsSource);
	fs = new string(fsSource);
	success = createShader(vs, fs);
	if (!success) {
		printf("infoLog:: %s\n", infoLog);
		return;
	}
	delete vs;       delete fs;
	delete vsSource; delete fsSource;
	init2DTexture();
}

Cube::~Cube()
{
	while (vertices.size() > 0)
		vertices.pop_back();
}

void Cube::makeCheckImage(void)
{
	int i, j, c;

	for (i = 0; i < iWidth; i++) {
		for (j = 0; j < iHeight; j++) {
			c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
		}
	}
}

GLubyte* Cube::makeTexImage(char *loadfile)
{
	int i, j, c, width, height;
	GLubyte *texImage;

	//texImage = SOIL_load_image((char *)loadfile, &width, &height, 0, SOIL_LOAD_RGB);

	/*
	 *  Only works for .png or .tif images.  NULL is returned if errors occurred.
	 *  loadImageRGA() is from imageio library downloaded from Internet.
	 */
	texImage = loadImageRGBA((char *)loadfile, &width, &height);	//ImageIO
	texImageWidth = width;
	texImageHeight = height;

	return texImage;
}

void Cube::init2DTexture()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glActiveTexture(GL_TEXTURE0);

	glGenTextures(1, &tex_cube);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex_cube);        //now we work on tex_cube   
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP, GL_TRUE);

	for (int i = 0; i < 6; ++i) {
		GLubyte *texImage = makeTexImage(maps[i]);
		if (!texImage) {
			printf("\nError reading %s \n", maps[i]);
			continue;
		}

		glTexImage2D(texAxis[i], 0, GL_RGBA, texImageWidth, texImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);
		delete texImage;
	}

}


//void Cube::draw(float mvpMatrix[4][4])
void Cube::draw()
{
	// get handle to model-view projection matrix 

	/*
	int mvpMatrixHandle = glGetUniformLocation(this->programObject, "mvpMatrix");
	if (mvpMatrixHandle == -1)
		printf("No such uniform named %s\n", "mvpMatrix");
	// pass model-view projection matrix to vertex shader
	glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, &mvpMatrix[0][0]);
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//coordinates of vertices of 6 faces of cube
	float skyBoxVertices[] =
	{
		// a face consists of 2 triangles (6 vertices)
	   -8.0f,  8.0f, -8.0f,
	   -8.0f, -8.0f, -8.0f,
		8.0f, -8.0f, -8.0f,
		8.0f, -8.0f, -8.0f,
		8.0f,  8.0f, -8.0f,
	   -8.0f,  8.0f, -8.0f,

	   -8.0f, -8.0f,  8.0f,
	   -8.0f, -8.0f, -8.0f,
	   -8.0f,  8.0f, -8.0f,
	   -8.0f,  8.0f, -8.0f,
	   -8.0f,  8.0f,  8.0f,
	   -8.0f, -8.0f,  8.0f,

		8.0f, -8.0f, -8.0f,
		8.0f, -8.0f,  8.0f,
		8.0f,  8.0f,  8.0f,
		8.0f,  8.0f,  8.0f,
		8.0f,  8.0f, -8.0f,
		8.0f, -8.0f, -8.0f,

	   -8.0f, -8.0f,  8.0f,
	   -8.0f,  8.0f,  8.0f,
		8.0f,  8.0f,  8.0f,
		8.0f,  8.0f,  8.0f,
		8.0f, -8.0f,  8.0f,
	   -8.0f, -8.0f,  8.0f,

	   -8.0f,  8.0f, -8.0f,
		8.0f,  8.0f, -8.0f,
		8.0f,  8.0f,  8.0f,
		8.0f,  8.0f,  8.0f,
	   -8.0f,  8.0f,  8.0f,
	   -8.0f,  8.0f, -8.0f,

	   -8.0f, -8.0f, -8.0f,
	   -8.0f, -8.0f,  8.0f,
		8.0f, -8.0f, -8.0f,
		8.0f, -8.0f, -8.0f,
	   -8.0f, -8.0f,  8.0f,
		8.0f, -8.0f,  8.0f
	};

	// Use vertex buffer to hold data
	GLuint skyBoxVBO;
	glGenBuffers(1, &skyBoxVBO);
	glBindBuffer(GL_ARRAY_BUFFER, skyBoxVBO);
	glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), skyBoxVertices, GL_STATIC_DRAW);
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glDepthMask(GL_FALSE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex_cube);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);

}

