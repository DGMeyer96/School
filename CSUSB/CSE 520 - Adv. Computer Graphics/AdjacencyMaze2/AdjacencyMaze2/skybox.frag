  // skybox.frag: Source code of fragment shader

   //in vec3 texcoords;
   uniform samplerCube cubeMap;

   void main()
   {
     gl_FragColor = textureCube(cubeMap, gl_TexCoord[0].stp);
   }

