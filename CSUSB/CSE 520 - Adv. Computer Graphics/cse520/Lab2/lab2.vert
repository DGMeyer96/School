//lab2.vert
//a minimal vertex shader
void main(void)
{
  //gl_Position     = ftransform();
  
  /*  Same as:
      gl_Position = gl_ProjectionMatrix *  gl_ModelViewMatrix * gl_Vertex;
    or

      gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
*/
   
    vec4 v4;
    v4 = gl_Vertex;
    v4.y = sin(v4.x); //apply sin to y-axis

    mat4 mRotateZ = mat4 ( 0.5, 0.867, 0, 0,//1st col
                        -0.867, 0.5, 0, 0,  //2nd col
                        0, 0, 1, 0,         //3rd col
                        0, 0, 0, 1  );      //4th col
    //v4 = mRotateZ * v4; //90degree about z-axis

    mat4 mTranslate = mat4 ( 1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            2.5, 0, 0, 1);

    //v4 = mTranslate * mRotateZ * v4;

    mat4 mReflect = mat4 ( 1, 0, 0, 0,      //1st col
                        0, -1, 0, 0,        //2nd col
                        0, 0, -1, 0,        //3rd col
                        0, 0, 0, 1  );      //4th col
    
    //v4 = mReflect * v4; //180 X-Roll or reflect about the y-z place

    mat4 mScale = mat4 (1, 0, 0, 0,
                        0, 3, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1);

    //v4 = mScale * v4;
    
    gl_Position = gl_ProjectionMatrix *  gl_ModelViewMatrix * v4;
}
