#ifndef MATRIX_HPP
# define MATRIX_HPP

#include "Camera.hpp"

class Matrix
{
private:
	float perspective[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	float view[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	float model[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	float identity[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
public:
	Matrix(const unsigned int screenWidth, const unsigned int screenHeight, Camera& cam);
	~Matrix();

	float* getPerspective();
	float* getView();
	float* getModel();
	float* getIdentity();

	void getForward(float *forward, Camera& cam);
	void normalize(float v[3]);
	void cross(float out[3], const float a[3], const float b[3]);
	float dot(const float a[3], const float b[3]);
	void computeViewMatrix(Camera& cam);
};

#endif