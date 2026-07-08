#include "../includes/Camera.hpp"
#include <SDL3/SDL_video.h>
#include <SDL3/SDL.h>
#include <cmath>
#include <iostream>

Camera::Camera()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 2.0f;
	this->yRotation = -90.0f;
	this->xRotation = 0.0f;
	this->rotationSpeed = 1.05f;
	this->angle = 0.0f;
}

Camera::~Camera() {}

float Camera::getX() {
	return this->x;
}

float Camera::getY() {
	return this->y;
}

float Camera::getZ() {
	return this->z;
}

float Camera::getXRotation() {
	return this->xRotation;
}

float Camera::getYRotation() {
	return this->yRotation;
}

float Camera::getRotationSpeed() {
	return this->rotationSpeed;
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

float Camera::getAngle() {
	return this->angle;
}

void Camera::setAngle(float newAngle) {
	this->angle = newAngle;
}
