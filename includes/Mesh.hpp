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
	float meshColor[3] = {0.0f, 0.0f, 0.0f};

public:
	Mesh();
	Mesh(std::vector<SingleVertex3D>& bodyPart, float* bodyColor);
	Mesh(std::vector<SingleVertex3D>& button);
	~Mesh();

	std::size_t& getVertexCount();
	GLuint& getVAO();
	float* getColor();
	void updateColor(float* newColor);
	void updateVBO(std::vector<SingleVertex3D>& bodyPart);

	void deleteMesh();
};

#endif