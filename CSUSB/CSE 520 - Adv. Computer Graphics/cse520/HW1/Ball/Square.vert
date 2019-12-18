/*
	Square.vert
*/

attribute vec3 rotate;
attribute vec4 vColor;

varying vec4 fColor;

void main(void)
{
	vec4 v4;
	v4 = gl_Vertex;

	mat4 mRotateZ = mat4 ( cos(rotate.z), sin(rotate.z), 0, 0,//1st col
                        sin(rotate.z), cos(rotate.z), 0, 0,  //2nd col
                        0, 0, 1, 0,         //3rd col
                        0, 0, 0, 1  );      //4th col

	v4 = mRotateZ * v4;

	fColor = vColor;
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * v4;
}