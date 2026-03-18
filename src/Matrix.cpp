#include "../includes/Matrix.hpp"
#include <cmath>
#include <stdio.h>
#include <string.h>

Matrix::Matrix(const unsigned int screenWidth, const unsigned int screenHeight, Camera& cam)
{
	float f = 1.0f / tan((45.0 * (M_PI / 180.0f)) / 2.0f);
	float aspectRatio = float(screenWidth) / float(screenHeight);
	float zNear = 0.01f;
	float zFar = 100.0f;

	this->perspective[0]  = f / aspectRatio;
	this->perspective[5]  = f;
	this->perspective[10] = (zFar + zNear) / (zNear - zFar);
	this->perspective[11] = -1.0f;
	this->perspective[14] = (2 * zFar * zNear) / (zNear - zFar);

	this->computeViewMatrix(cam);
}

Matrix::~Matrix() {}

float* Matrix::getPerspective() {
	return this->perspective;
}

float* Matrix::getView() {
	return this->view;
}

float* Matrix::getModel() {
	return this->model;
}

float* Matrix::getIdentity() {
	return this->identity;
}

void Matrix::getForward(float *forward) {
    float yRad = -90.0f * (M_PI / 180.0f);
    float xRad = 0.0f * (M_PI / 180.0f);

    forward[0] = cosf(yRad) * cosf(xRad);
    forward[1] = sinf(xRad);
    forward[2] = sinf(yRad) * cosf(xRad);
}

void Matrix::normalize(float v[3]) {
    float len = std::sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    if (len == 0.0f) 
        return;
    v[0] /= len;
    v[1] /= len;
    v[2] /= len;
}

void Matrix::cross(float out[3], const float a[3], const float b[3]) {
    out[0] = a[1]*b[2] - a[2]*b[1];
    out[1] = a[2]*b[0] - a[0]*b[2];
    out[2] = a[0]*b[1] - a[1]*b[0];
}

float Matrix::dot(const float a[3], const float b[3]) {
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

void Matrix::computeViewMatrix(Camera& cam) {
    float eye[3] = { cam.getX(), cam.getY(), cam.getZ() };
    float up[3]  = { 0.0f, 1.0f, 0.0f };

    float forward[3];
    this->getForward(forward);
    this->normalize(forward);

    float s[3];
    this->cross(s, forward, up);
    this->normalize(s);

    float u[3];
    this->cross(u, s, forward);

    this->view[0]  =  s[0];
    this->view[1]  =  u[0];
    this->view[2]  = -forward[0];
    this->view[3]  =  0.0f;

    this->view[4]  =  s[1];
    this->view[5]  =  u[1];
    this->view[6]  = -forward[1];
    this->view[7]  =  0.0f;

    this->view[8]  =  s[2];
    this->view[9]  =  u[2];
    this->view[10] = -forward[2];
    this->view[11] =  0.0f;

    this->view[12] = -dot(s, eye);
    this->view[13] = -dot(u, eye);
    this->view[14] =  dot(forward, eye);
    this->view[15] =  1.f;
}

void Matrix::setModelToIdentity() {
    memcpy(this->model, this->identity, 16 * sizeof(float));
}

void Matrix::setRotationXMatrix(float& angle) {
    memcpy(this->model, this->identity, 16 * sizeof(float));
    this->model[0] = cosf(angle);
    this->model[2] = sinf(angle);
    this->model[8] = -sinf(angle);
    this->model[10] = cosf(angle);
}

void Matrix::setRotationYMatrix(float& angle) {
    memcpy(this->model, this->identity, 16 * sizeof(float));
    this->model[5] = cosf(angle);
    this->model[6] = -sinf(angle);
    this->model[9] = sinf(angle);
    this->model[10] = cosf(angle);
}