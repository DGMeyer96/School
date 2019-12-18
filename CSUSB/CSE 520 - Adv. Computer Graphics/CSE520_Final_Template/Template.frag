//template.frag
//a minimal fragment shader

varying vec4 fColor;

void main(void)
{
  //make a color with alpha of 1.0
  //gl_FragColor = vec4(color, 1.0);	
  gl_FragColor = fColor;

  //gl_FragColor = vec4(1, 0, 0, 1);
}
