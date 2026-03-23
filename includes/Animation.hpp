#ifndef ANIMATION_HPP
# define ANIMATION_HPP

#include "Shader.hpp"
#include "Matrix.hpp"
#include "BodyParts.hpp"

class Animation
{
private:
	float rotationSpeed;
	bool doneWithCycle;

	float leftArmRotationAngle;
	bool leftArmRotationForward;

	float rightArmRotationAngle;
	bool rightArmRotationForward;

	float leftLegRotationAngle;
	bool leftLegRotationForward;

	float rightLegRotationAngle;
	bool rightLegRotationForward;


public:
	Animation();
	~Animation();

	void incrementAngle(float& angle, bool& forward);
	void decrementAngle(float& angle, bool& forward);

	void walkingAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i);

	void leftArmRotation();
	void rightArmRotation();
	void leftLegRotation();
	void rightLegRotation();

	void startCycle();
	void cycleIsFinished();
	bool getDoneWithCycle();
};

#endif