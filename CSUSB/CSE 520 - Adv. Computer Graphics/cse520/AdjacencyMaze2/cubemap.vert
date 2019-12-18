
/*
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
*/

// simpletex.vert
// Vertex shader for drawing an object with one texture
//

varying float LightIntensity;
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

    gl_TexCoord[0]  = gl_MultiTexCoord0;
    gl_Position     = ftransform();
}