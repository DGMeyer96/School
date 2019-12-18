attribute vec2 v_texCoordinate;
varying float LightIntensity;
varying vec2 f_texCoordinate;
uniform vec3 LightPosition;

const float specularContribution = 0.1;
const float diffuseContribution  = 1.0 - specularContribution;

void main(void)
{
    vec3 ecPosition = vec3 (gl_ModelViewMatrix * gl_Vertex);
    vec3 tnorm      = normalize(gl_NormalMatrix * gl_Normal);
    vec3 lightVec   = normalize(LightPosition - ecPosition);
    vec3 reflectVec = reflect(-lightVec, tnorm);
    vec3 viewVec    = normalize(-ecPosition);

    float spec      = clamp(dot(reflectVec, viewVec), 0.0, 1.0);
    spec            = pow(spec, 16.0);

    LightIntensity  = diffuseContribution * max(dot(lightVec, tnorm), 0.0)
                      + specularContribution * spec;

	f_texCoordinate = v_texCoordinate;

    //gl_TexCoord[0]  = gl_MultiTexCoord0;
	//gl_TexCoord[1]  = gl_MultiTexCoord1;
	//gl_TexCoord[2]  = gl_MultiTexCoord2;
	//gl_TexCoord[3]  = gl_MultiTexCoord3;

    gl_Position     = ftransform();
}