//Lab3.vert

attribute vec3 rotate;
attribute float VertexScale;
attribute vec4 vColor;

varying vec4 fColor;

void main(void)
{
	vec4 v4;
	v4 = gl_Vertex;

	mat4 mRotateX = mat4 ( 1, 0, 0, 0,//1st col
                        0, cos(rotate.x), sin(rotate.x), 0,  //2nd col
                        0, -sin(rotate.x), cos(rotate.x), 0,         //3rd col
                        0, 0, 0, 1  );      //4th col

	mat4 mRotateY = mat4 ( cos(rotate.y), 0, -sin(rotate.y), 0,//1st col
                        0, 1, 0, 0,  //2nd col
                        sin(rotate.y), 0, cos(rotate.y), 0,         //3rd col
                        0, 0, 0, 1  );      //4th col

	mat4 mRotateZ = mat4 ( cos(rotate.z), sin(rotate.z), 0, 0,//1st col
                        sin(rotate.z), cos(rotate.z), 0, 0,  //2nd col
                        0, 0, 1, 0,         //3rd col
                        0, 0, 0, 1  );      //4th col

	mat4 mScale = mat4 (VertexScale, 0, 0, 0,
                        0, VertexScale, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1);

	v4 = mScale * mRotateZ * mRotateY * mRotateX * v4;

	fColor = vColor;
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * v4;
}