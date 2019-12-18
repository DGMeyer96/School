uniform mat4 mvpMatrix;
attribute vec4 vPosition;

void main()
{
   gl_TexCoord[0].stp = gl_Vertex.xyz;
	gl_Position = ftransform();
}

