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
	this->leftLegUpRotationForward = true;

	this->leftLegLowRotationAngle = 0.0f;
	this->leftLegLowRotationForward = true;

	this->rightLegUpRotationAngle = 0.0f;
	this->rightLegUpRotationForward = false;

	this->rightLegLowRotationAngle = 0.0f;
	this->rightLegLowRotationForward = false;

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
	shader.setUniform1i(0, "animation");
}

void Animation::incrementAngle(float& angle, bool& forward) {
    if (angle + this->rotationSpeed >= .90f) {
        angle = 0.90f;
		forward = !forward;
    } else {
        angle += this->rotationSpeed;
    }
}

void Animation::decrementAngle(float& angle, bool& forward) {
	if (angle - this->rotationSpeed <= -.90f) {
		angle = -0.90f;
		forward = !forward;
    } else {
		angle -= this->rotationSpeed;
    }
}

float Animation::roundTo2Decimals(float& angle) {
	float var = angle;
	float value = (int)(var * 100 + .5);
    return (float)value / 100;	
}

void Animation::leftArmUpRotation() {
	if (this->leftArmUpRotationForward)
		this->incrementAngle(this->leftArmUpRotationAngle, this->leftArmUpRotationForward);
	else
		this->decrementAngle(this->leftArmUpRotationAngle, this->leftArmUpRotationForward);
}

void Animation::leftArmLowRotation() {
	if (this->leftArmLowRotationForward)
		this->incrementAngle(this->leftArmLowRotationAngle, this->leftArmLowRotationForward);
	else
		this->decrementAngle(this->leftArmLowRotationAngle, this->leftArmLowRotationForward);
}

void Animation::rightArmUpRotation() {
	if (this->rightArmUpRotationForward)
		this->incrementAngle(this->rightArmUpRotationAngle, this->rightArmUpRotationForward);
	else
		this->decrementAngle(this->rightArmUpRotationAngle, this->rightArmUpRotationForward);
}

void Animation::rightArmLowRotation() {
	if (this->rightArmLowRotationForward)
		this->incrementAngle(this->rightArmLowRotationAngle, this->rightArmLowRotationForward);
	else
		this->decrementAngle(this->rightArmLowRotationAngle, this->rightArmLowRotationForward);
}

void Animation::leftLegUpRotation() {
	if (this->leftLegUpRotationForward)
		this->incrementAngle(this->leftLegUpRotationAngle, this->leftLegUpRotationForward);
	else
		this->decrementAngle(this->leftLegUpRotationAngle, this->leftLegUpRotationForward);
}

void Animation::leftLegLowRotation() {
	if (this->leftLegLowRotationForward)
		this->incrementAngle(this->leftLegLowRotationAngle, this->leftLegLowRotationForward);
	else
		this->decrementAngle(this->leftLegLowRotationAngle, this->leftLegLowRotationForward);
}

void Animation::rightLegUpRotation() {
	if (this->rightLegUpRotationForward)
		this->incrementAngle(this->rightLegUpRotationAngle, this->rightLegUpRotationForward);
	else
		this->decrementAngle(this->rightLegUpRotationAngle, this->rightLegUpRotationForward);
}

void Animation::rightLegLowRotation() {
	if (this->rightLegLowRotationForward)
		this->incrementAngle(this->rightLegLowRotationAngle, this->rightLegLowRotationForward);
	else
		this->decrementAngle(this->rightLegLowRotationAngle, this->rightLegLowRotationForward);
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
