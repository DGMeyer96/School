/*
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
*/


// simpletex.frag
// Fragment shader for drawing an object with one texture
//

varying float LightIntensity;
uniform sampler2D texHandle;

void main (void)
{
    vec3 lightColor = vec3 (texture2D(texHandle, gl_TexCoord[0].st));
    gl_FragColor    = vec4 (lightColor * LightIntensity, 1.0);
}