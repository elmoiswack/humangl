#include "../includes/Button.hpp"

Button::Button(ButtonType type, float x, float y, int width, int height, int screenWidth, int screenHeight) {
	this->type = type;
	this->setVertices(x, y, width, height, screenWidth, screenHeight);
	this->mesh = Mesh(this->vertices);
	this->active = false;
}

Button::~Button() {}

void Button::setVertices(float x, float y, int width, int height, int screenWidth, int screenHeight) {
	this->posX = x;
	this->posY = y;
	this->width = width;
	this->height = height;

	if (width == 0 || height == 0) {
		this->vertices = {};
		return ;
	}

	if (x > screenWidth || y > screenHeight) {
		this->vertices = {};
		return ;
	}

	float point1X = normalizeValue(x, screenWidth);
	float point1Y = -normalizeValue(y, screenHeight);

	float point2X = normalizeValue(x + width, screenWidth);
	float point2Y = -normalizeValue(y, screenHeight);
	
	float point3X = normalizeValue(x, screenWidth);
	float point3Y = -normalizeValue(y + height, screenHeight);
	
	float point4X = normalizeValue(x + width, screenWidth);
	float point4Y = -normalizeValue(y + height, screenHeight);

	this->vertices = {
		SingleVertex3D{point1X, point1Y, 0.0f},
		SingleVertex3D{point2X, point2Y, 0.0f},
		SingleVertex3D{point3X, point3Y, 0.0f},
		SingleVertex3D{point2X, point2Y, 0.0f},
		SingleVertex3D{point3X, point3Y, 0.0f},
		SingleVertex3D{point4X, point4Y, 0.0f},
	};
}

void Button::activateButton() {
	this->active = true;
	float color[3] = {0.6f, 0.6f, 0.6f};
	this->mesh.updateColor(color);
}

void Button::deactivateButton() {
	this->active = false;
	float color[3] = {0.4f, 0.4f, 0.4f};
	this->mesh.updateColor(color);
}

bool Button::getActive() {
	return this->active;
}

float Button::normalizeValue(float point, float screenValue) {
	return (((point / screenValue) * 2) - 1);
}

std::vector<SingleVertex3D>& Button::getVertices() {
	return this->vertices;
}

Mesh& Button::getMesh() {
	return this->mesh;
}

ButtonType Button::getType() {
	return this->type;
}

float Button::getX() {
	return this->posX;
}

float Button::getY() {
	return this->posY;
}

float Button::getWidth() {
	return this->width;
}

float Button::getHeight() {
	return this->height;
}
