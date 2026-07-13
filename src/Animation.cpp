#include "../includes/Animation.hpp"

Animation::Animation()
{
	this->currentAnimation = AnimationTypes::IDLE;
	this->rotationSpeed = 0.05f;

	this->leftArmUpRotationAngle = 0.0f;
	this->leftArmUpRotationForward = true;

	this->leftArmLowRotationAngle = 0.0f;
	this->leftArmLowRotationForward = true;

	this->rightArmUpRotationAngle = 0.0f;
	this->rightArmUpRotationForward = false;

	this->rightArmLowRotationAngle = 0.0f;
	this->rightArmLowRotationForward = false;

	this->leftLegUpRotationAngle = 0.0f;
	this->leftLegUpRotationForward = false;

	this->leftLegLowRotationAngle = 0.0f;
	this->leftLegLowRotationForward = false;

	this->rightLegUpRotationAngle = 0.0f;
	this->rightLegUpRotationForward = true;

	this->rightLegLowRotationAngle = 0.0f;
	this->rightLegLowRotationForward = true;

	this->currentJumpHeight = 0.0f;
	this->maxJumpHeight = .2f;
	this->jumpSpeed = 0.015;
	this->incrementJumpHeight = true;
}

Animation::~Animation() {}

void Animation::checkAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i) {
	switch (this->currentAnimation)
	{
	case AnimationTypes::IDLE:
		return ;
	case AnimationTypes::WALKING:
		this->walkingAnimation(shader, matrix, body, i);
		return ;
	case AnimationTypes::JUMP:
		this->jumpAnimation(shader, matrix, body, i);
		return ;
	case AnimationTypes::RUN:
		this->walkingAnimation(shader, matrix, body, i);
		return ;
	default:
		return ;
	}
}

void Animation::resetAnimation(Shader& shader, Matrix& matrix) {
	this->currentAnimation = AnimationTypes::IDLE;
	this->leftArmUpRotationAngle = 0.0f;
	this->leftArmLowRotationAngle = 0.0f;
	this->rightArmUpRotationAngle = 0.0f;
	this->rightArmLowRotationAngle = 0.0f;
	this->leftLegUpRotationAngle = 0.0f;
	this->leftLegLowRotationAngle = 0.0f;
	this->rightLegUpRotationAngle = 0.0f;
	this->rightLegLowRotationAngle = 0.0f;
	this->currentJumpHeight = 0.0f;
	matrix.setModelToIdentity();
	shader.setUniformMatrix4x4(matrix.getModel(), "model");
	shader.setUniform1f(0.0f, "jumpHeight");
	shader.setUniform1i(AnimationTypes::IDLE, "animation");
}

bool Animation::isAnimationFinished() {
	return (this->currentAnimation == AnimationTypes::IDLE);
}
	
void Animation::startAnimation(AnimationTypes whichAnimation) {
	this->currentAnimation = whichAnimation;
}

AnimationTypes Animation::getCurrentAnimation() {
	return this->currentAnimation;
}
