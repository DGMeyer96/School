//template.vert
//a minimal vertex shader
attribute float theta;

void main(void)
{
//  gl_Position     = ftransform();
    
    vec4 v4;
    v4 = gl_Vertex;
    v4.y = sin ( v4.x );
    float a = theta * ( 3.14159265 / 180.0 ); //convert to radians

    mat4 m0 = mat4 ( cos ( a ), sin (a), 0, 0,      // first col
		    -sin(a), cos (a), 0, 0,      // 2nd col
		    0, 0, 1, 0,      // 3rd col
                    0, 0, 0, 1  );    // 4th col

    v4 = m0 * v4;

    gl_Position = gl_ProjectionMatrix *  gl_ModelViewMatrix * v4;
}

/*
    mat4 mRotateX = mat4 ( 1, 0, 0, 0,//1st col
                        0, cos(rotate.x), sin(rotate.x), 0,  //2nd col
                        0, -sin(rotate.x), cos(rotate.x), 0,         //3rd col
                        0, 0, 0, 1  );      //4th col

	mat4 mRotateY = mat4 ( cos(rotate.y), 0, -sin(rotate.y), 0,//1st col
                        0, 1, 0, 0,  //2nd col
                        sin(rotate.y), 0, cos(rotate.y), 0,         //3rd col
                        0, 0, 0, 1  );      //4th col

	mat4 mRotateZ = mat4 ( cos(rotate.z), sin(rotate.z), 0, 0,//1st col
                        sin(rotate.z), cos(rotate.z), 0, 0,  //2nd col
                        0, 0, 1, 0,         //3rd col
                        0, 0, 0, 1  );      //4th col

	mat4 mScale = mat4 (vScale, 0, 0, 0,
                        0, vScale, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1);
*/

//gl_Position     = ftransform();
/*
    Same as

    gl_Position = gl_ProjectionMatrix *  gl_ModelViewMatrix * v4;
    gl_Position = ProjectModelViewMatrix * v4;
*/