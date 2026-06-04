#include "../includes/Button.hpp"

Button::Button(ButtonType type, float x, float y, int width, int height, int screenWidth, int screenHeight) {
	this->type = type;
	this->name = nullptr;
	this->setVertices(x, y, width, height, screenWidth, screenHeight);
	this->mesh = Mesh(this->vertices);
}

Button::~Button() {}

void Button::setVertices(float x, float y, int width, int height, int screenWidth, int screenHeight) {
	this->posX = x;
	this->posY = y;
	this->width = width;
	this->height = height;

	float halfScreenWidth = screenWidth / 2;
	float halfScreenHeight = screenHeight / 2;

	float point1X = (x > halfScreenWidth ? ((x + halfScreenWidth) / screenWidth) : -((x + halfScreenWidth) / screenWidth));
	float point1Y = (y > halfScreenHeight ? -((y + halfScreenHeight) / screenHeight) : ((y + halfScreenHeight) / screenHeight));

	float point2X = ((x + width) > halfScreenWidth ? (((x + width) + halfScreenWidth) / screenWidth) : -(((x + width) + halfScreenWidth) / screenWidth));
	float point2Y = (y > halfScreenHeight ? -((y + halfScreenHeight) / screenHeight) : ((y + halfScreenHeight) / screenHeight));
	
	float point3X = (x > halfScreenWidth ? ((x + halfScreenWidth) / screenWidth) : -((x + halfScreenWidth) / screenWidth));
	float point3Y = ((y + height) > halfScreenHeight ? -(((y + height) + halfScreenHeight) / screenHeight) : (((y + height) + halfScreenHeight) / screenHeight));
	
	float point4X = ((x + width) > halfScreenWidth ? (((x + width) + halfScreenWidth) / screenWidth) : -(((x + width) + halfScreenWidth) / screenWidth));
	float point4Y = ((y + height) > halfScreenHeight ? -(((y + height) + halfScreenHeight) / screenHeight) : (((y + height) + halfScreenHeight) / screenHeight));

	this->vertices = {
		SingleVertex3D{point1X, point1Y, 0.0f},
		SingleVertex3D{point2X, point2Y, 0.0f},
		SingleVertex3D{point3X, point3Y, 0.0f},
		SingleVertex3D{point2X, point2Y, 0.0f},
		SingleVertex3D{point3X, point3Y, 0.0f},
		SingleVertex3D{point4X, point4Y, 0.0f},
	};
}

std::vector<SingleVertex3D>& Button::getVertices() {
	return this->vertices;
}

Mesh& Button::getMesh() {
	return this->mesh;
}

void Button::createName(std::string buttonName) {
	this->name = gltCreateText();
	gltSetText(this->name, "-");
}

void Button::drawName() {
	gltBeginDraw();
	gltColor(1.0f, 1.0f, 1.0f, 1.0f);
	std::cout << this->name->_text << std::endl;
	std::cout << this->name->_textLength << std::endl;
	std::cout << this->name->_vao << std::endl;
	std::cout << this->name->_vbo << std::endl;
	if (this->name->_vertices == nullptr) {
		std::cout << "dasdsad MEHDJHDSBDUSD" << std::endl;
	}
	std::cout << this->name->_vertices << std::endl;
	gltDrawText2D(
		this->name,
		(GLfloat)(this->posX + (this->posX * 0.25)),
		(GLfloat)(this->posY + (this->posY * 0.25)),
		2.0f
	);
	gltEndDraw();
}

void Button::deleteName() {
	gltDeleteText(this->name);
	this->name = nullptr;
}