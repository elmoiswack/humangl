#include "../includes/Animation.hpp"
#include <string.h>

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

	this->tposeDecreaseAngle = false;
	this->flexDecreaseAngle = false;
}

Animation::~Animation() {}

void Animation::checkAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::vector<Mesh>& meshes, std::size_t i) {
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
	case AnimationTypes::TPOSE:
		this->tposeAnimation(shader, matrix, body, i);
		return ;
	case AnimationTypes::FLEX:
		this->flexAnimation(shader, matrix, body, meshes, i);
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
	this->tposeDecreaseAngle = false;
	this->flexDecreaseAngle = false;
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

void Animation::setPivotPoint(SingleVertex3D& pivot, Shader& shader, Matrix& matrix) {
	matrix.setPivotMatrix(pivot.x, pivot.y, pivot.z);
	shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
	matrix.setPivotMatrix(-pivot.x, -pivot.y, -pivot.z);
	shader.setUniformMatrix4x4(matrix.getPivot(), "negativePivotMatrix");
}

void Animation::setPivotPointFlex(SingleVertex3D& pivot, Shader& shader, Matrix& matrix,float* outPositivePivot, float* outNegativePivot) {
    matrix.setPivotMatrix(pivot.x, pivot.y, pivot.z);
    memcpy(outPositivePivot, matrix.getPivot(), 16 * sizeof(float));
    shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");

    matrix.setPivotMatrix(-pivot.x, -pivot.y, -pivot.z);
    memcpy(outNegativePivot, matrix.getPivot(), 16 * sizeof(float));
    shader.setUniformMatrix4x4(matrix.getPivot(), "negativePivotMatrix");
}

void Animation::moveTowards(float& value, float target, float speed) {
    if (value < target)
        value = std::min(value + speed, target);
    else
        value = std::max(value - speed, target);
}

float Animation::roundTo2Decimals(float& angle) {
	float var = angle;
	float value = (int)(var * 100 + .5);
    return (float)value / 100;	
}