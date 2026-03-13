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

Mesh::Mesh(std::vector<SingleVertex>& bodyPart, float* bodyColor)
{
	this->meshColor = bodyColor;
	this->vertexCount = bodyPart.size();
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glBufferData(GL_ARRAY_BUFFER, bodyPart.size() * sizeof(SingleVertex), bodyPart.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SingleVertex), (void*)sizeof(SingleVertex));
	glEnableVertexAttribArray(0);
}

Mesh::~Mesh() {}

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
	this->meshColor = newColor;
}

void Mesh::updateVBO(std::vector<SingleVertex>& bodyPart) {
	this->vertexCount = bodyPart.size();
	glBufferData(GL_ARRAY_BUFFER, bodyPart.size() * sizeof(SingleVertex), bodyPart.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SingleVertex), (void*)0);
}

void Mesh::deleteMesh() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
}