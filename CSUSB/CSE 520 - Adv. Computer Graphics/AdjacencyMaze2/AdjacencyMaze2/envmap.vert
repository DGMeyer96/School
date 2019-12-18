void main()
{	
  gl_Position = ftransform();		
  gl_TexCoord[0] = gl_MultiTexCoord0;
	
  vec3 v = normalize( vec3(gl_ModelViewMatrix * gl_Vertex) );
  vec3 n = normalize( gl_NormalMatrix * gl_Normal );
  vec3 r = reflect( v, n );
  float m =  sqrt ( 2.0 * ( r.z + 1.0 ) )  ;
  gl_TexCoord[1].s = r.x/m + 0.5;
  gl_TexCoord[1].t = r.y/m + 0.5;
}    
