#include "../includes/Mesh.hpp"
#include <iostream>

Mesh::Mesh() {
	this->VAO = 0;
	this->VBO = 0;
	this->vertexCount = 0;
	this->meshColor[0] = 0.0f;
	this->meshColor[1] = 0.0f;
	this->meshColor[2] = 0.0f;
}

Mesh::Mesh(std::vector<SingleVertex3D>& bodyPart, float* bodyColor)
{
	this->meshColor[0] = bodyColor[0];
	this->meshColor[1] = bodyColor[1];
	this->meshColor[2] = bodyColor[2];
	this->vertexCount = bodyPart.size();
	
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glGenBuffers(1, &this->SSBO);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->SSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER,
				vertexCount * (4 * sizeof(float)),
				nullptr,
				GL_DYNAMIC_COPY);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, this->SSBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glBufferData(GL_ARRAY_BUFFER, bodyPart.size() * sizeof(SingleVertex3D), bodyPart.data(), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SingleVertex3D), (void*)0);
}

Mesh::Mesh(std::vector<SingleVertex3D>& button)
{
	this->meshColor[0] = 0.4f;
	this->meshColor[1] = 0.4f;
	this->meshColor[2] = 0.4f;
	this->vertexCount = button.size();
	
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glBufferData(GL_ARRAY_BUFFER, button.size() * sizeof(SingleVertex3D), button.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SingleVertex3D), (void*)0);
}

Mesh::~Mesh() {
	// this->deleteMesh(); //TODO: need to fix
}

std::size_t& Mesh::getVertexCount() {
	return this->vertexCount;
}

GLuint& Mesh::getVAO() {
	return this->VAO;
}

float* Mesh::getColor() {
	return this->meshColor;
}

void Mesh::updateColor(float* newColor) {
	this->meshColor[0] = newColor[0];
	this->meshColor[1] = newColor[1];
	this->meshColor[2] = newColor[2];
}

void Mesh::updateVBO(std::vector<SingleVertex3D>& bodyPart) {
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	SingleVertex3D* vboData = static_cast<SingleVertex3D*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	if (vboData == nullptr) {
		std::cout << "ERROR: VBO data is null" << std::endl;
		return ;
	}
	auto data = bodyPart.data();
	for (std::size_t i = 0; i < bodyPart.size(); i++) {
		vboData[i] = data[i];
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
}

void Mesh::deleteMesh() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
}

float* Mesh::fetchSSBOData() {
	return (float*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
}
