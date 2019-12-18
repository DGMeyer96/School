   // skybox.vert: Source code of vertex shader
   uniform mat4 mvpMatrix;
   attribute vec4 vPosition;

   void main()
   {

      gl_TexCoord[0].stp = gl_Vertex.xyz;
      //gl_Position = mvpMatrix * gl_Vertex;
	  gl_Position = ftransform();
   }

