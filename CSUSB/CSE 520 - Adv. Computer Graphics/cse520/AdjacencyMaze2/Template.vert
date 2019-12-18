
attribute vec4 vColor;
varying vec4 fColor;

void main(void)
{
	//fColor = vColor;
    gl_Position     = ftransform();
}