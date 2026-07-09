#ifndef ANIMATION_HPP
# define ANIMATION_HPP

#include "Shader.hpp"
#include "Matrix.hpp"
#include "BodyParts.hpp"

enum AnimationTypes {
	IDLE,
	WALKING,
	JUMP,
	RUN,
};

class Animation
{
private:
	AnimationTypes currentAnimation;
	float rotationSpeed;

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

	float currentJumpHeight;
	float maxJumpHeight;
	float jumpSpeed;
	bool incrementJumpHeight;

public:
	Animation();
	~Animation();

	void checkAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i);
	void resetAnimation(Shader& shader, Matrix& matrix);
	
	void incrementAngle(float& angle, bool& forward);
	void decrementAngle(float& angle, bool& forward);

	float roundTo2Decimals(float& angle);
	
	void walkingAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i);
	bool checkIfWalkingFinished();
	void runAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i);

	void jumpAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i);
	void incrementHeight();
	bool checkIfJumpFinished();

	void leftArmUpRotation();
	void leftArmLowRotation();

	void rightArmUpRotation();
	void rightArmLowRotation();
	
	void leftLegUpRotation();
	void leftLegLowRotation();

	void rightLegUpRotation();
	void rightLegLowRotation();

	bool isAnimationFinished();
	void startAnimation(AnimationTypes whichAnimation);
	AnimationTypes getCurrentAnimation();
};

#endif