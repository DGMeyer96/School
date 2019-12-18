uniform vec4 color0;
uniform vec4 color1;
uniform vec4 color2;

varying float weight;   // from vertex shader
varying vec3 normale;
varying vec4 positione;

void main(void)
{ 
/*
  vec4 color;

  if ( weight < 0.01 )
     color = vec4 (0, 0, 0, 1 );
  else if ( weight < 0.3 )
     color = color0;
//     color = mix ( color0, color1, weight );
  else if ( weight < 0.6 )
     color = color1;
     //color = mix ( color1, color2, weight );
  else if ( weight < 0.8 )
     color = color2;
  else
     color = vec4 ( 0, 1, 1, 1 );
    // color = mix ( color2, color0, weight );
//  vec4 color = color0 + color1;
//  gl_FragColor = color;	// color
*/
// vec3 normale = vec3(1, 1, 0);
  vec3 norm = normalize(normale);
  //vec3 lightv = normalize(gl_LightSource[0].position.xyz);// - positione.xyz);
  vec3 lightv = normalize(gl_LightSource[0].position.xyz - positione.xyz);
  vec3 viewv;
  viewv = normalize(positione.xyz);
  vec3 halfv = normalize(lightv + viewv);
  vec4 diffuse = max(0, dot(lightv, norm)) //* vec4( 1, 1, 1, 1 );
           *gl_FrontMaterial.diffuse*gl_LightSource[0].diffuse;
  vec4 ambient = gl_FrontMaterial.ambient*gl_LightSource[0].ambient;
  float f;
  if(dot(lightv, viewv)> 0.0) f =1.0;
  else f = 0.0;
  //vec3 specular;
  vec4 specular = f*pow(max(0, dot(norm, halfv)), gl_FrontMaterial.shininess)*gl_FrontMaterial.specular*gl_LightSource[0].specular;
//  vec3 color = vec3(ambient + diffuse + specular);
  vec3 color = vec3(diffuse.rgb);
  gl_FragColor = vec4(color, 1.0);


}

