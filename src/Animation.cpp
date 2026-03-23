#include "../includes/Animation.hpp"

Animation::Animation()
{
	this->rotationSpeed = 0.02f;
	this->doneWithCycle = true;

	this->leftArmRotationAngle = 0.0f;
	this->leftArmRotationForward = true;

	this->rightArmRotationAngle = 0.0f;
	this->rightArmRotationForward = false;

	this->leftLegRotationAngle = 0.0f;
	this->leftLegRotationForward = false;

	this->rightLegRotationAngle = 0.0f;
	this->rightLegRotationForward = true;
}

Animation::~Animation()
{
}

void Animation::incrementAngle(float& angle, bool& forward) {
    if (angle + this->rotationSpeed > .45f) {
        angle = 0.44f;
		forward = !forward;
    } else {
        angle += this->rotationSpeed;
    }
}

void Animation::decrementAngle(float& angle, bool& forward) {
    if (angle - this->rotationSpeed < -.45f) {
        angle = -0.44f;
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

void Animation::leftLegRotation() {
	if (this->leftLegRotationForward)
		this->incrementAngle(this->leftLegRotationAngle, this->leftLegRotationForward);
	else
		this->decrementAngle(this->leftLegRotationAngle, this->leftLegRotationForward);
}

void Animation::rightLegRotation() {
	if (this->rightLegRotationForward)
		this->incrementAngle(this->rightLegRotationAngle, this->rightLegRotationForward);
	else
		this->decrementAngle(this->rightLegRotationAngle, this->rightLegRotationForward);
}

void Animation::walkingAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i) {
	auto& pivotLeftArm = body.getLeftArmPivot();
	auto& pivotRightArm = body.getRightArmPivot();
	auto& pivotLeftLeg = body.getLeftLegPivot();
	auto& pivotRightLeg = body.getRightLegPivot();
	
	switch (i)
	{
	case BodyPartsIndex::LEFTARM:
		this->leftArmRotation();
		matrix.setRotationYMatrix(this->leftArmRotationAngle);
		matrix.setPivotMatrix(pivotLeftArm.x, pivotLeftArm.y, pivotLeftArm.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
		matrix.setPivotMatrix(-pivotLeftArm.x, -pivotLeftArm.y, -pivotLeftArm.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "negativePivotMatrix");
		break;
	
	case BodyPartsIndex::RIGHTARM:
		this->rightArmRotation();
		matrix.setRotationYMatrix(this->rightArmRotationAngle);
		matrix.setPivotMatrix(pivotRightArm.x, pivotRightArm.y, pivotRightArm.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
		matrix.setPivotMatrix(-pivotRightArm.x, -pivotRightArm.y, -pivotRightArm.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "negativePivotMatrix");
		break; 
	
	case BodyPartsIndex::LEFTLEG:
		this->leftLegRotation();
		matrix.setRotationYMatrix(this->leftLegRotationAngle);
		matrix.setPivotMatrix(pivotLeftLeg.x, pivotLeftLeg.y, pivotLeftLeg.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
		matrix.setPivotMatrix(-pivotLeftLeg.x, -pivotLeftLeg.y, -pivotLeftLeg.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "negativePivotMatrix");
		break; 
	
	case BodyPartsIndex::RIGHTLEG:
		this->rightLegRotation();
		matrix.setRotationYMatrix(this->rightLegRotationAngle);
		matrix.setPivotMatrix(pivotRightLeg.x, pivotRightLeg.y, pivotRightLeg.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
		matrix.setPivotMatrix(-pivotRightLeg.x, -pivotRightLeg.y, -pivotRightLeg.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "negativePivotMatrix");
		break;

	default:
		matrix.setModelToIdentity();
		shader.setUniformMatrix4x4(matrix.getIdentity(), "positivePivotMatrix");
		shader.setUniformMatrix4x4(matrix.getIdentity(), "negativePivotMatrix");
		break;
	}
	
	std::cout << this->leftArmRotationAngle << std::endl;
	if (this->leftArmRotationAngle == 0.0f)
		std::cout << "AHWDWADASFEA" << std::endl;

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