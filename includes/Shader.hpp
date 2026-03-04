#ifndef SHADER_HPP
# define SHADER_HPP

#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <fstream>


class Shader
{
private:
	GLuint shaderProgram;
	char* vertexShaderSource;
	char* fragmentShaderSource;
	
public:
	Shader(const char* pathToVertex, const char* pathToFragment);
	~Shader();

	char* readFromFile(const char* pathToFile);
	void useProgram();
	void setUniformMatrix4x4(const float *matrix, const char *name);

};




#endif