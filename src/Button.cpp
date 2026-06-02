#include "../includes/Button.hpp"

Button::Button(ButtonType type, std::string name) {
	this->type = type;
	this->name = gltCreateText();
	gltSetText(this->name, name.c_str());

	this->vertices = {
		SingleVertex3D{0.5f,  0.5f, 0.0f},
		SingleVertex3D{0.5f,  -0.5f, 0.0f},
		SingleVertex3D{-0.5f, 0.5f, 0.0f},
		SingleVertex3D{0.5f,  -0.5f, 0.0f},
		SingleVertex3D{-0.5f,  -0.5f, 0.0f},
		SingleVertex3D{-0.5f, 0.5f, 0.0f},
	};
}

Button::~Button() {
	gltDeleteText(this->name);
	gltTerminate();
}

std::vector<SingleVertex3D>& Button::getVertices() {
	return this->vertices;
}

void Button::drawName() {
		gltDrawText2DAligned(
			this->name,
			(GLfloat)(50),
			(GLfloat)(50),
			1.5f,
			GLT_CENTER, GLT_TOP
	);
}