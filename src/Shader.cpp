#include "../includes/Shader.hpp"
#include <cstring>

Shader::Shader(const char* pathToVertex, const char* pathToFragment)
{
    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
	this->vertexShaderSource = this->readFromFile(pathToVertex);
	this->fragmentShaderSource = this->readFromFile(pathToFragment);

    glShaderSource(vertexShader, 1, &this->vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, &this->fragmentShaderSource, NULL);
    
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    GLint success;
    GLchar infoLog[512];
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Vertex shader compilation failed:\n" << infoLog << std::endl;
	}
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Fragment shader compilation failed:\n" << infoLog << std::endl;
	}

    this->shaderProgram = glCreateProgram();
    glAttachShader(this->shaderProgram, vertexShader);
    glAttachShader(this->shaderProgram, fragmentShader);
    glLinkProgram(this->shaderProgram);
    
    glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
        std::cout << "Shader program linking failed:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	delete[] this->vertexShaderSource;
	delete[] this->fragmentShaderSource;
}

char* Shader::readFromFile(const char* pathToFile) {
	std::ifstream file(pathToFile);

	if (!file) {
		std::cout << "Failed to open file: " << pathToFile << std::endl;
		exit(1);
	}

	std::string fileLine;
	std::string totalFile;

	while (getline(file, fileLine)) {
		totalFile.append(fileLine + "\n");
	}

	char* tmp = new char[totalFile.size() + 1];

	strcpy(tmp, totalFile.c_str());

	tmp[totalFile.size()] = '\0';

	return tmp;
}

void Shader::useProgram() {
	glUseProgram(this->shaderProgram);
}

