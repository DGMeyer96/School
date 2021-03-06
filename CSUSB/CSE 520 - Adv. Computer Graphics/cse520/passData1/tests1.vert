//testfun.vert
//a minimal vertex shader
attribute float theta;
varying   float blueColor;
void main(void)
{
//  gl_Position     = ftransform();
 
    blueColor = 0.0;   
    vec4 v4;
    v4 = gl_Vertex;
//    v4.y = sin ( v4.x );
    float a = theta * ( 3.14159265 / 180.0 ); //convert to radians

    mat4 m0 = mat4 ( cos ( a ), sin (a), 0, 0,      // first col
		    -sin(a), cos (a), 0, 0,      // 2nd col
		    0, 0, 1, 0,      // 3rd col
                    0, 0, 0, 1  );    // 4th col

    v4 = m0 * v4;

    gl_Position = gl_ProjectionMatrix *  gl_ModelViewMatrix * v4;
}



/*
    v4.xy = v4.yx;
    v4.y = sin ( v4.x );
     v4.y = step ( 0, v4.x );
     v4.y = smoothstep ( -1, 1, v4.x );

    mat4 m0 = mat4 ( 0.5, 0.867, 0, 0,      // first col
		    -0.867, 0.5, 0, 0,      // 2nd col
		    0, 0, 1, 0,      // 3rd col
                    0, 0, 0, 1  );    // 4th col

    mat4 m = mat4 ( 1, 0, 0, 0,      // first col
		    0, 1, 0, 0,      // 2nd col
		    0, 0, 1, 0,      // 3rd col
                    2.5, 0, 0, 1  );    // 4th col
    v4 = m * m0 * v4;
   v4 = v4 * m;
*/

