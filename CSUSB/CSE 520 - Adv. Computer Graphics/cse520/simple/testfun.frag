//testfun.frag
//a minimal fragment shader

void main(void)
{
  vec4 c1 = vec4 ( 1, 0.1, 0.1, 1 );
  vec4 c2 = vec4 ( 0, 1, 0.1, 1 );
  float r = 0.5;
  vec4 color = mix ( c1, c2, r );
  //gl_FragColor = vec4( 0, 0, 0, 1);	// color
  gl_FragColor = color;	// color
}

