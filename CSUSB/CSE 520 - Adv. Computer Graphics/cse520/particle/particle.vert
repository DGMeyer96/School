//testfun.vert
//a minimal vertex shader
attribute vec3 vel;
uniform float time1;

void main(void)
{
   float s = 1000.0;
   float g = -10.0;
   float t;
   t = time1 / s;

   vec4 objPos = gl_Vertex;

   objPos.x = objPos.x + vel.x * t;   
   objPos.y = objPos.y + vel.y * t + g * t * t /2.0;   
   objPos.z = objPos.z + vel.z * t;   
 
    gl_Position = gl_ProjectionMatrix *  gl_ModelViewMatrix * objPos;
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

