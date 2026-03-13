#ifndef MESH_HPP
# define MESH_HPP

#include "BodyParts.hpp"
#include "glad/glad.h"

class Mesh
{
private:
	GLuint VBO;
	GLuint VAO;
	std::size_t vertexCount;
	float* meshColor;

public:
	Mesh();
	Mesh(std::vector<SingleVertex>& bodyPart, float* bodyColor);
	~Mesh();

	std::size_t& getVertexCount();
	GLuint& getVAO();
	float* getColor();
	void updateColor(float* newColor);
	void updateVBO(std::vector<SingleVertex>& bodyPart);

	void deleteMesh();
};

#endif