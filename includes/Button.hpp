#ifndef BUTTON_HPP
# define BUTTON_HPP

#include <iostream>
#include <vector>

#include "glad/glad.h"
#include "Mesh.hpp"
#include "BodyParts.hpp"
#define GLT_IMPLEMENTATION
#include "../includes/gltext.h"

enum ButtonType {
	PLUS,
	MINUS,
	WORD,
};

class Button
{
private:
	std::vector<SingleVertex3D> vertices;
	std::vector<Mesh> mesh;
	ButtonType type;
	GLTtext* name = nullptr;
	float width;
	float height;
	bool active = false;

public:
	Button(ButtonType type, std::string name);
	~Button();

	std::vector<SingleVertex3D>& getVertices();
	void drawName();
};

#endif