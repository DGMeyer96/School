//tests.frag
//a minimal fragment shader
uniform vec4 color;
varying float blueColor;

void main(void)
{
  gl_FragColor = color;           

  gl_FragColor.b = blueColor;

//  gl_FragColor = vec4( 0, 1, 1, 1);	// color
}

