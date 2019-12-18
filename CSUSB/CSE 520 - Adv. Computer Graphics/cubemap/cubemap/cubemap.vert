//
// Vertex shader for cube map environment mapping
//
// Author: Randi Rost
//
// Copyright (c) 2003-2006: 3Dlabs, Inc.
//
// See 3Dlabs-License.txt for license information
//
/*
varying vec3  ReflectDir;
varying float LightIntensity;

uniform vec3  LightPos;

	varying vec2 position;
    varying vec3 color;
    varying vec2 texcoord;
    varying vec3 Color;
    varying vec2 Texcoord;

void main() 
{
    gl_Position    = ftransform();
    vec3 normal    = normalize(gl_NormalMatrix * gl_Normal);
    vec4 pos       = gl_ModelViewMatrix * gl_Vertex;
    vec3 eyeDir    = pos.xyz;
    ReflectDir     = reflect(eyeDir, normal);
    LightIntensity = max(dot(normalize(LightPos - eyeDir), normal),0.0);
	Color = color;
    Texcoord = texcoord;
}
*/

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
