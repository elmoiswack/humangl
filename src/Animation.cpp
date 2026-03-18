#include "../includes/Animation.hpp"
#include <BodyParts.hpp>

Animation::Animation()
{
	this->rotationSpeed = 0.07f;
	this->doneWithCycle = true;

	this->leftArmRotationAngle = 0.0f;
	this->leftArmRotationForward = true;

	this->rightArmRotationAngle = 0.0f;
	this->rightArmRotationForward = false;
}

Animation::~Animation()
{
}

void Animation::incrementAngle(float& angle, bool& forward) {
    if (angle + this->rotationSpeed > 1.5f) {
        angle = 1.49f;
		forward = !forward;
    } else {
        angle += this->rotationSpeed;
    }
}

void Animation::decrementAngle(float& angle, bool& forward) {
    if (angle - this->rotationSpeed < -1.5f) {
        angle = -1.49f;
		forward = !forward;
    } else {
        angle -= this->rotationSpeed;
    }
}

void Animation::leftArmRotation() {
	if (this->leftArmRotationForward)
		this->incrementAngle(this->leftArmRotationAngle, this->leftArmRotationForward);
	else
		this->decrementAngle(this->leftArmRotationAngle, this->leftArmRotationForward);
}

void Animation::rightArmRotation() {
	if (this->rightArmRotationForward)
		this->incrementAngle(this->rightArmRotationAngle, this->rightArmRotationForward);
	else
		this->decrementAngle(this->rightArmRotationAngle, this->rightArmRotationForward);
}

void Animation::walkingAnimation(Shader& shader, Matrix& matrix, std::size_t i) {
	switch (i)
	{
	case static_cast<std::size_t>(BodyPartsIndex::LEFTARM):
		this->leftArmRotation();
		matrix.setRotationYMatrix(this->leftArmRotationAngle);
		break;
	
	case static_cast<std::size_t>(BodyPartsIndex::RIGHTARM):
		this->rightArmRotation();
		matrix.setRotationYMatrix(this->rightArmRotationAngle);
		break; 
	default:
		matrix.setModelToIdentity();
		break;
	}
	
	shader.setUniformMatrix4x4(matrix.getModel(), "model");
}

void Animation::startCycle() {
	this->doneWithCycle = false;
}

void Animation::cycleIsFinished() {
	this->doneWithCycle = true;
}

bool Animation::getDoneWithCycle() {
	return this->doneWithCycle;
}