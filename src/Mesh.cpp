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

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glBufferData(GL_ARRAY_BUFFER, bodyPart.size() * sizeof(SingleVertex3D), bodyPart.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SingleVertex3D), (void*)sizeof(SingleVertex3D));
	glEnableVertexAttribArray(0);
}

Mesh::~Mesh() {
	// this->deleteMesh(); //need to fix
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
	this->vertexCount = bodyPart.size();
	glBufferData(GL_ARRAY_BUFFER, bodyPart.size() * sizeof(SingleVertex3D), bodyPart.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SingleVertex3D), (void*)0);
}

void Mesh::deleteMesh() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
}