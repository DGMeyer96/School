/*
	FigAB.vert
*/
uniform float time1;
attribute vec3 start;
attribute vec3 end;

void main(void)
{
	float s = 2000.0;
	float t;
	t = time1 / s;

	vec4 v4;
    v4 = gl_Vertex;

	v4.xy = mix(start.xy, end.xy, t);

    gl_Position = gl_ProjectionMatrix *  gl_ModelViewMatrix * v4;
}