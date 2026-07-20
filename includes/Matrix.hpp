#ifndef MATRIX_HPP
# define MATRIX_HPP

class Matrix
{
private:
	float perspective[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	float view[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	float model[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	float identity[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	float pivot[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

public:
	Matrix();
	Matrix(const unsigned int screenWidth, const unsigned int screenHeight);
	~Matrix();

	float* getPerspective();
	float* getView();
	float* getModel();
	float* getIdentity();
	float* getPivot();

	float degreesToRadians(float degrees);
	void normalize(float v[3]);
	void cross(float out[3], const float a[3], const float b[3]);
	float dot(const float a[3], const float b[3]);
	void computeViewMatrix(float targetX, float targetY, float targetZ, float angle, float radius);

	void setModelToIdentity();
	void setRotationXMatrix(float& angle);
	void setRotationYMatrix(float& angle);
	void setRotationZMatrix(float& angle);

	void setPivotMatrix(float x, float y, float z);

	void multiplyInto(float* out, const float* a, const float* b);

};

#endif