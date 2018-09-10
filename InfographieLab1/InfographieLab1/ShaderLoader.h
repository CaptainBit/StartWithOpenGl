#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>

using namespace std;

class ShaderLoader
{
private:
	string ReadShader(char* filename);
	GLuint CreateShader(GLenum shaderType, string source, char* shaderName);
public:
	ShaderLoader();
	GLuint CreateProgram(char* VertexShaderFilename, char* FragmentShaderFilename);
};

