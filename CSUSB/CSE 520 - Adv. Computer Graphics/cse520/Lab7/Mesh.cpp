//Mesh.cpp : Mesh class member functions

#include "Mesh.h"

using namespace std;

Mesh::Mesh()
{
	nVertices = nNormals = nFaces = 0;
}

//Read mesh data from file
bool Mesh::readData(char fName[])
{
	fstream ins;
	ins.open(fName, ios::in);
	cout << "opening file " << fName << endl;
	if (ins.fail()) return false;                // error - can't open file
	if (ins.eof())  return false; 		// error - empty file
	ins >> nVertices >> nNormals >> nFaces; 	// read in number of vertices, normals, and faces
	for (int i = 0; i < nVertices; i++) {	//read vertices
		Point3 p;
		ins >> p.x >> p.y >> p.z;
		vertexList.push_back(p);
	}
	for (int i = 0; i < nNormals; i++) {	//read normals
		Vector3 v;
		ins >> v.x >> v.y >> v.z;
		normalList.push_back(v);
	}
	cout << endl;
	for (int i = 0; i < nFaces; i++) {
		Polygon p;

		ins >> p.n;
		for (int j = 0; j < p.n; j++) {
			int vertexIndex;
			ins >> vertexIndex;
			p.vertices.push_back(vertexIndex);
		}
		for (int j = 0; j < p.n; j++) {
			int normalIndex;
			ins >> normalIndex;
			p.normals.push_back(normalIndex);
		}
		faceList.push_back(p);
	}

	return true;
}

//render the mesh
void Mesh::renderMesh()
{
	//Draw each polygon of the mesh

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);	//do not render back faces

	//draw base
	glBegin(GL_POLYGON);
	for (int i = 0; i < nVertices / 2; i++)
	{
		glVertex3f(vertexList[i].x, vertexList[i].y, vertexList[i].z);
	}
	glEnd();

	//draw walls
	for (int i = 0; i < nFaces; i++) {
		setColor(i);
		glBegin(GL_POLYGON);
		//specifying vertices of the polygon
		for (int j = 0; j < faceList[i].n; j++) {
			int vi = faceList[i].vertices[j];	//vertex index
			int ni = faceList[i].normals[j];	//normal index
			//glNormal3f(normalList[ni].x, normalList[ni].y, normalList[ni].z);
			glVertex3f(vertexList[vi].x, vertexList[vi].y, vertexList[vi].z);
		} //for j
		glEnd();
	}  //for i

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);	//do not render back faces
	//draw cap
	glBegin(GL_POLYGON);
	for (int i = nVertices / 2; i < nVertices; i++)
	{
		glVertex3f(vertexList[i].x, vertexList[i].y, vertexList[i].z);
	}
	glEnd();
}

void Mesh::setColor(int n)
{
	if (n == 1 || n == 8)
		glColor3f(1, 0, 0);
	else if (n == 2 || n == 9)
		glColor3f(0, 1, 0);
	else if (n == 3 || n == 10)
		glColor3f(0, 0, 1);
	else if (n == 4 || n == 11)
		glColor3f(1, 1, 0);
	else if (n == 5 || n == 12)
		glColor3f(1, 0, 1);
	else if (n == 6 || n == 13)
		glColor3f(0, 1, 1);
	else if (n == 7 || n == 14)
		glColor3f(0, 0, 0);
	else
		glColor3f(0.5, 0.5, 0.5);
}
