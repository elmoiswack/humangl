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
	Shader();
	Shader(const char* pathToVertex, const char* pathToFragment);
	
	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other) noexcept;
	~Shader();

	char* readFromFile(const char* pathToFile);
	void useProgram();
	void setUniformMatrix4x4(const float *matrix, const char *name);
	void setUniformVec3(const float* vertex, const char* name);
	void setUniform1i(const int value, const char* name);
	void setUniform1f(const float value, const char* name);

	int getUniform1i(const char* name);

	class FailedReadingFile : public std::exception {
	public:
		const char *what() const throw() {
			return ("Failed to read to content of the shader file!");
		}
	};
	class FailedCompilingShader : public std::exception {
	public:
		const char *what() const throw() {
			return ("Failed to compile shader!");
		}
	};
};

#endif