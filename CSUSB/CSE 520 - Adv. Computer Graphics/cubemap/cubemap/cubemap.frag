//
// Fragment shader for cube map environment mapping
//
// Author: Randi Rost
//
// Copyright (c) 2003-2006: 3Dlabs, Inc.
//
// See 3Dlabs-License.txt for license information
//
/*
uniform vec3  BaseColor;
uniform float MixRatio;

uniform samplerCube EnvMap;

varying vec3  ReflectDir;
varying float LightIntensity;

varying vec3 Color;
varying vec2 Texcoord;
varying vec4 outColor;
uniform sampler2D tex;

void main()
{
    // Look up environment map value in cube map

    vec3 envColor = vec3(textureCube(EnvMap, ReflectDir));

    // Add lighting to base color and mix

    vec3 base = LightIntensity * BaseColor;
    envColor  = mix(envColor, base, MixRatio);

	outColor = texture(tex, Texcoord) * vec4(Color, 1.0);

    gl_FragColor = vec4(envColor, 1.0);
}
*/

uniform sampler2D colorMap;
uniform sampler2D envMap;

void main (void)
{
  vec4 color = texture2D( colorMap, gl_TexCoord[0].st);
  vec4 env = texture2D( envMap, gl_TexCoord[1].st);

  gl_FragColor = color * 0.5 + env * 0.5 ;
 //gl_FragColor = color;
 //  gl_FragColor = env;
}   
