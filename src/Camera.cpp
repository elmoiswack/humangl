#include "../includes/Camera.hpp"

Camera::Camera()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 3.0f;
}

Camera::~Camera()
{
}

float Camera::getX() {
	return this->x;
}

float Camera::getY() {
	return this->y;
}

float Camera::getZ() {
	return this->z;
}

void Camera::setX(float value) {
	this->x = value;
}

void Camera::setY(float value) {
	this->y = value;
}

void Camera::setZ(float value) {
	this->z = value;
}

