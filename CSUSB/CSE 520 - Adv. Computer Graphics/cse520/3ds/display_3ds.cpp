/*display_3ds.cpp
 *This program demonstrates the use of 3dslib to render
 *3ds objects without textures.
 *
 *@Author: T.L. Yu
 *Winter 2009, CS 520, CSUSB
*/
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "lib3ds.h"			//3ds library header

extern char *testfile;

struct Vertex {
  float x;
  float y;
  float z;
};

extern int anglex;			//rotation angles
extern int angley;
extern int anglez;
extern float tx;			//translation values
extern float ty;
extern float tz;
extern float tinc[3];

//set IO functions, in 3dsdump.cpp
void set_io_func ( Lib3dsIo *io );		

//open a 3ds file and return a handle to it
Lib3dsFile *get3dsFile ( char *filename )
{
  FILE *fp;
  Lib3dsFile *f = 0;
  Lib3dsIo io;
  int result;

  fp = fopen ( filename, "rb" );
  if (!fp) {
        fprintf(stderr, "***ERROR***\nFile not found: %s\n", filename );
        exit(1);
  }
  f = lib3ds_file_new();

  memset(&io, 0, sizeof(io));
  io.self = fp;
  set_io_func ( &io );
  result =  lib3ds_file_read(f, &io);

  fclose(fp);

  if (!result) {
    fprintf(stderr, "***ERROR***\nLoading file failed: %s\n", filename);
    exit(1);
  }

  return f;
}

//Get the vertices of a mesh and calculates the maximum and minumum ranges
struct Vertex *getVertices( Lib3dsMesh *mesh  )
{
  int i, j;
  float p[3];
  struct Vertex *vs;
  float min[3] = { 1000, 1000, 1000 };
  float max[3] = { -1000, -1000, -1000 };

  assert ( mesh );
  //allocate memory to hold all the vertices of the mesh
  vs = ( struct Vertex * ) malloc ( mesh->nvertices * sizeof ( struct Vertex ) );
  
  assert ( vs );	//ensure that we have successfully allocated the memory
 
  for (i = 0; i < mesh->nvertices; ++i) {
    lib3ds_vector_copy(p, mesh->vertices[i]);
    for ( j = 0; j < 3; ++j ) {
	if ( min[j] > p[j] ) min[j] = p[j];
	if ( max[j] < p[j] ) max[j] = p[j];
    }
    vs[i].x = p[0];
    vs[i].y = p[1];
    vs[i].z = p[2];
  }
  for ( j = 0; j < 3; ++j ) 
    tinc[j] = ( max[j] - min[j] ) / 10.0;	//translation increment values

  return vs;
}

//Find the minimum and maximum x, y, z coordinates
void find_min_max (  Lib3dsFile *f, float min[], float max[] )
{
  Lib3dsMesh *mesh;
  float p[3];
  min[0] = min[1] = min[2] = 100000.0;
  max[0] = max[1] = max[2] = -100000.0;
  
  for ( int k = 0; k < f->nmeshes; ++k ) {
    mesh = f->meshes[k];
  
    for (int i = 0; i < mesh->nvertices; ++i) {
      lib3ds_vector_copy(p, mesh->vertices[i]);
      for ( int j = 0; j < 3; ++j ) {
        if ( min[j] > p[j] ) min[j] = p[j];
        if ( max[j] < p[j] ) max[j] = p[j];
      }
    }
  }
/*
  for (int j = 0; j < 3; ++j ) {
    printf("(min[%d]=%f, max[%d]=%f) ", j, min[j], j, max[j] ); 
  }
  printf("\n");
*/
}

static const char* node_names_table[] = {
    "Ambient",
    "Mesh",
    "Camera",
    "Camera Target",
    "Omnilight",
    "Spotlight",
    "Spotlight Target"
};

void set_color ( int k )
{
    if ( k == 1 ) 
       glColor3f ( 1.0, 0, 0 );
    else if ( k == 2 ) 
       glColor3f ( 0.0, 1.0, 0 );
    else if ( k == 3 ) 
       glColor3f ( 0, 0, 1 );
    else
       glColor3f ( 0.5, 0.5, 0.5 );
} 

void display_meshes (  Lib3dsFile *f )
{ 
  struct Vertex *vs;
  struct Vertex v;
  Lib3dsMesh *mesh;

  glPolygonMode( GL_BACK, GL_LINE );
  glPolygonMode( GL_FRONT, GL_LINE );
  Lib3dsMaterial *mat=0;

  glEnable( GL_CULL_FACE );
  glCullFace ( GL_BACK );
  glPolygonMode( GL_FRONT, GL_FILL ); 
  Lib3dsNode *node;
  int l = 0;
  for ( int k = 0; k < f->nmeshes; ++k ) {
    mesh = f->meshes[k];
    vs = getVertices( f->meshes[k] );
    float  (*normals)[3] = (float (*)[3])  malloc ( 3 * 3 * sizeof ( float ) * mesh->nfaces );
    lib3ds_mesh_calculate_face_normals ( mesh,  normals );
    
    for ( int i = 0; i < mesh->nfaces; ++i ) {

      int k = mesh->faces[i].material;
      mat = f->materials[k];
      if (mat) {
        float s;
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat->ambient );
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat->diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat->specular);
        s = pow(2, 10.0*mat->shininess);
        if (s>128.0) {
          s=128.0;
        }
        glMaterialf(GL_FRONT, GL_SHININESS, s);
      }
      glBegin ( GL_TRIANGLES );
      for ( int j = 0; j < 3; ++ j ) {
	glNormal3fv(normals[3*i+j]);
	int index;	
      	index = mesh->faces[i].index[j];
	v = vs[index];
  	glVertex3f ( v.x, v.y, v.z );
       // glVertex3fv ( ( float*)&v );	//this is fine too
      }
      glEnd();
    }
    free ( normals );
  }
  free ( vs );			//deallocate memory
}

//set the lights
void lighting ( Lib3dsFile *f  )
{
  int li = GL_LIGHT0;
  Lib3dsLight *light;

  if ( f->nlights > 0 ) {
    glEnable(GL_LIGHTING);
    for ( int i = 0; i < f->nlights; ++i ) {
      float color[3];
      light = f->lights[i];
      glLightfv( li, GL_DIFFUSE, light->color );
      glLightfv( li, GL_SPECULAR, light->color );
      glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light->color);
      glLightfv(li, GL_POSITION, light->position); 
      if ( light->spot_light) {
        glLightfv(li, GL_SPOT_DIRECTION, light->position); 
      }
      glEnable(li);
 
      ++li;
    }
  } else {				//no lights provided by 3ds file
    printf("No lights provided by 3ds file.\n");
    GLfloat light[] = { 1.0, 1.0, 1.0 };
    GLfloat light1[] = { 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_position1[] = { -1, -1, -1, 0.0 };
    GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light );
    glLightfv(GL_LIGHT0, GL_SPECULAR, light );
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1 );
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1 );

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
  }
}

void display()
{

  Lib3dsNode *c,*t;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glClearColor( 0.8, 0.8, 0.8, 0.5 );
 
  Lib3dsCamera *camera;
  glShadeModel ( GL_SMOOTH );
  
  glEnable(GL_DEPTH_TEST); 

  Lib3dsFile *f;
  f = get3dsFile ( (char *) testfile );

  lighting( f );

  if ( f->ncameras > 0 ) {
    camera = f->cameras[0];
    printf("Camera Information: ");
    printf("  name:       %s\n", camera->name);
    printf("  position:   (%f, %f, %f)\n",
        camera->position[0], camera->position[1], camera->position[2]);
    printf("  target      (%f, %f, %f)\n",
        camera->target[0], camera->target[1], camera->target[2]);
    printf("  roll:       %f\n", camera->roll);
    printf("  fov:        %f\n", camera->fov);
    printf("  see_cone:   %s\n", camera->see_cone ? "yes" : "no");
    printf("  near_range: %f\n", camera->near_range);
    printf("  far_range:  %f\n", camera->far_range);
    printf("\n");
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective ( 45, 1.0, 100, camera->far_range );
    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt ( camera->position[0], camera->position[1], camera->position[2],
	camera->target[0], camera->target[1], camera->target[2],
	0, 1, 0 );
 } else {
    printf("No camera detected, set our own coordinates!\n");
    float min[3], max[3], minx, maxx, miny, maxy, minz, maxz;
    find_min_max ( f, min, max );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float delta = 3;
    minx = min[0] - ( max[0] - min[0] ) / delta;
    maxx = max[0] + ( max[0] - min[0] ) / delta;
    miny = min[1] - ( max[1] - min[1] ) / delta;
    maxy = max[1] + ( max[1] - min[1] ) / delta;
    minz = min[2] - ( max[2] - min[2] ) / delta;
    maxz = max[2] + ( max[2] - min[2] ) / delta;
    if ( minz > 0 )
 	minz = -minz;
    if ( maxz - minz < 0.1 ) 				
      glOrtho ( minx, maxx, miny, maxy, -10, 10 );
    else
      glOrtho ( minx, maxx, miny, maxy, minz, maxz );
    glMatrixMode(GL_MODELVIEW);
  }
  glPushMatrix();
  glTranslatef ( tx, ty, tz );

  glRotatef( anglex, 1.0, 0.0, 0.0);
  glRotatef( angley, 0.0, 1.0, 0.0);
  glRotatef( anglez, 0.0, 0.0, 1.0);
  display_meshes (  f ); 
  glPopMatrix();

  glFlush();
  glutSwapBuffers();
}

