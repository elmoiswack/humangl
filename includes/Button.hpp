#ifndef BUTTON_HPP
# define BUTTON_HPP

#include <iostream>
#include <vector>

#include "glad/glad.h"
#include "Mesh.hpp"
#include "BodyParts.hpp"
#define GLT_IMPLEMENTATION
#include "gltext.h"

enum ButtonType {
	PLUS,
	MINUS,
	WORD,
};

class Button
{
private:
	std::vector<SingleVertex3D> vertices;
	Mesh mesh;
	ButtonType type;
	GLTtext* name = nullptr;
	float width;
	float height;
	float posX;
	float posY;
	bool active = false;

public:
	Button(ButtonType type, float x, float y, int width, int height, int screenWidth, int screenHeight);
	~Button();

	void setVertices(float x, float y, int width, int height, int screenWidth, int screenHeight);
	std::vector<SingleVertex3D>& getVertices();
	
	void createName(std::string buttonName);
	void drawName();

	Mesh& getMesh();

	void deleteName();
};

#endif