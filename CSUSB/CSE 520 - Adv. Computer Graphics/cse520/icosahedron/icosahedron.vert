// vertex

attribute float c;
//attribute float ax, ay, az;
attribute vec3 a;
attribute float tx;

varying float weight;    //pass from vertex shader to fragment shader
//matrix4 m4;
void main(void)
{
    bool turn = true;  
    float x = 2.0; 
    float t = tx;
    vec4 v4;
    v4 = gl_Vertex;
    mat4 m0 = mat4 ( cos (a.x), sin ( a.x ), 0, 0,      // first col
		    -sin ( a.x ), cos (a.x), 0, 0,      // 2nd col
		    0, 0, 1, 0,      // 3rd col
                    0, 0, 0, 1  );    // 4th col
    
    mat4 m1 = mat4 ( cos (a.y), 0, -sin ( a.y ), 0,      // first col
		    0, 1, 0, 0,      
		    sin ( a.y ), 0, cos (a.y),  0,      // 2nd col
                    0, 0, 0, 1  );    // 4th col
   weight = c; 
   v4 = m1 * m0 * v4;
  // v4.x += 20.0 * sin ( t );
  // v4.y += 10.0 * cos ( t );
   v4.x += 2.0 * sin ( t );
   v4.y += 1.0 * cos ( t );
   //v4.x += t;
   //v4.x += t;
   
  gl_Position = gl_ProjectionMatrix *  gl_ModelViewMatrix * v4;
 //gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; 
}
