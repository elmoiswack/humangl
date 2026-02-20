#include "../includes/Matrix.hpp"
#include <cmath>
#include <stdio.h>
#include <string.h>

Matrix::Matrix(const unsigned int width, const unsigned int height)
{
	float f = 1.0f / tan((45.0 * (M_PI / 180.0f)) / 2.0f);
	float aspectRatio = float(width) / float(height);
	float zNear = 0.01f;
	float zFar = 100.0f;

	this->perspective[0]  = f / aspectRatio;
	this->perspective[5]  = f;
	this->perspective[10] = (zFar + zNear) / (zNear - zFar);
	this->perspective[11] = -1.0f;
	this->perspective[14] = (2 * zFar * zNear) / (zNear - zFar);

	memcpy(this->model, this->identity, 16);
}

Matrix::~Matrix()
{
}

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