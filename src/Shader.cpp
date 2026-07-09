#include "../includes/Shader.hpp"
#include <cstring>

Shader::Shader() {
    this->shaderProgram = 0;
    this->vertexShaderSource = nullptr;
    this->fragmentShaderSource = nullptr;
}

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
        throw Shader::FailedCompilingShader();
    }
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Fragment shader compilation failed:\n" << infoLog << std::endl;
        throw Shader::FailedCompilingShader();
	}

    this->shaderProgram = glCreateProgram();
    glAttachShader(this->shaderProgram, vertexShader);
    glAttachShader(this->shaderProgram, fragmentShader);
    glLinkProgram(this->shaderProgram);
    
    glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
        std::cout << "Shader program linking failed:\n" << infoLog << std::endl;
        throw Shader::FailedCompilingShader();
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::Shader(Shader&& other) noexcept
    : shaderProgram(other.shaderProgram),
      vertexShaderSource(other.vertexShaderSource),
      fragmentShaderSource(other.fragmentShaderSource)
{
    other.shaderProgram = 0;
    other.vertexShaderSource = nullptr;
    other.fragmentShaderSource = nullptr;
}

Shader& Shader::operator=(Shader&& other) noexcept
{
    if (this != &other) {
        glDeleteProgram(this->shaderProgram);
        delete[] this->vertexShaderSource;
        delete[] this->fragmentShaderSource;

        this->shaderProgram = other.shaderProgram;
        this->vertexShaderSource = other.vertexShaderSource;
        this->fragmentShaderSource = other.fragmentShaderSource;

        other.shaderProgram = 0;
        other.vertexShaderSource = nullptr;
        other.fragmentShaderSource = nullptr;
    }
    return *this;
}

Shader::~Shader()
{
    glDeleteProgram(this->shaderProgram);
	delete[] this->vertexShaderSource;
	delete[] this->fragmentShaderSource;
}

char* Shader::readFromFile(const char* pathToFile) {
	std::ifstream file(pathToFile);

	if (!file) {
		throw Shader::FailedReadingFile();
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

void Shader::setUniformMatrix4x4(const float* matrix, const char* name) {
	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram, name), 1, GL_FALSE, matrix);
}

void Shader::setUniformVec3(const float* vertex, const char* name) {
    glUniform3f(glGetUniformLocation(this->shaderProgram, name), vertex[0], vertex[1], vertex[2]);
}

void Shader::setUniform1i(const int value, const char* name) {
    glUniform1i(glGetUniformLocation(this->shaderProgram, name), value);
}

void Shader::setUniform1f(const float value, const char* name) {
    glUniform1f(glGetUniformLocation(this->shaderProgram, name), value);
}

int Shader::getUniform1i(const char* name) {
    GLint value;
    glGetUniformiv(this->shaderProgram, glGetUniformLocation(this->shaderProgram, name), &value);
    return value;
}

