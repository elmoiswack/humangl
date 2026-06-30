#ifndef CAMERA_HPP
# define CAMERA_HPP

#include "Matrix.hpp"

class Camera
{
private:
	float x, y, z;
	float yRotation, xRotation, rotationSpeed;
	float angle;

public:
	Camera();
	~Camera();

	float getX();
	float getY();
	float getZ();
	float getXRotation(); 
	float getYRotation(); 
	float getRotationSpeed();

	void setX(float value);
	void setY(float value);
	void setZ(float value);

	float getAngle();
	void setAngle(float newAngle);
};

#endif