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

	float leftArmUpRotationAngle;
	bool leftArmUpRotationForward;

	float leftArmLowRotationAngle;
	bool leftArmLowRotationForward;

	float rightArmUpRotationAngle;
	bool rightArmUpRotationForward;

	float rightArmLowRotationAngle;
	bool rightArmLowRotationForward;

	float leftLegUpRotationAngle;
	bool leftLegUpRotationForward;

	float leftLegLowRotationAngle;
	bool leftLegLowRotationForward;

	float rightLegUpRotationAngle;
	bool rightLegUpRotationForward;

	float rightLegLowRotationAngle;
	bool rightLegLowRotationForward;


public:
	Animation();
	~Animation();

	void incrementAngle(float& angle, bool& forward);
	void decrementAngle(float& angle, bool& forward);

	float roundTo2Decimals(float& angle);
	bool checkIfPartsFinished();

	void walkingAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i);

	void leftArmUpRotation();
	void leftArmLowRotation();

	void rightArmUpRotation();
	void rightArmLowRotation();
	
	void leftLegUpRotation();
	void leftLegLowRotation();

	void rightLegUpRotation();
	void rightLegLowRotation();

	void startCycle();
	void cycleIsFinished();
	bool getDoneWithCycle();
};

#endif