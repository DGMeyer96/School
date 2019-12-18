varying float LightIntensity;
varying vec2 f_texCoordinate;
uniform sampler2D texHandle;

void main (void)
{
    //vec3 lightColor = vec3 (texture2D(texHandle, gl_TexCoord[0].st));
	vec3 lightColor = vec3(texture2D(texHandle, f_texCoordinate));
    gl_FragColor    = vec4 (lightColor * LightIntensity, 1.0);
}