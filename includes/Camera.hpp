#ifndef CAMERA_HPP
# define CAMERA_HPP

class Camera
{
private:
	float x, y, z;

public:
	Camera();
	~Camera();

	float getX();
	float getY();
	float getZ();

	void setX(float value);
	void setY(float value);
	void setZ(float value);

	void rotateLeft();
	void rotateRight();
};

#endif