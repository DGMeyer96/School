  uniform samplerCube cubeMap;

  void main()
  {
    gl_FragColor = textureCube(cubeMap, gl_TexCoord[0].stp);
  }