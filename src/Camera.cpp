#include "../includes/Camera.hpp"
#include <SDL3/SDL_video.h>
#include <SDL3/SDL.h>
#include <cmath>

Camera::Camera()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 2.0f;
}

Camera::~Camera()
{
}

void Camera::rotateLeft() {
	this->setX(sin(SDL_GetTicks()) * 3.f);
	this->setZ(cos(SDL_GetTicks()) * 3.f);
}

void Camera::rotateRight() {

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