//template.frag
//a minimal fragment shader
varying vec4 fColor;

void main(void)
{
	gl_FragColor = fColor;
	//gl_FragColor = vec4( 1, 0, 0, 1);	// color
}

