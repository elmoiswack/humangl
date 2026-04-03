#include "../includes/Animation.hpp"

Animation::Animation()
{
	this->rotationSpeed = 0.05f;
	this->doneWithCycle = true;

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
}

Animation::~Animation() {}

void Animation::incrementAngle(float& angle, bool& forward) {
    if (angle + this->rotationSpeed >= .45f) {
        angle = 0.45f;
		forward = !forward;
    } else {
        angle += this->rotationSpeed;
    }
}

void Animation::decrementAngle(float& angle, bool& forward) {
	if (angle - this->rotationSpeed <= -.45f) {
		angle = -0.45f;
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

bool Animation::checkIfPartsFinished() {
	if ((this->roundTo2Decimals(this->leftArmUpRotationAngle) != 0.00) || \
		(this->roundTo2Decimals(this->leftArmLowRotationAngle) != 0.00) || \
		(this->roundTo2Decimals(this->rightArmUpRotationAngle) != 0.00) || \
		(this->roundTo2Decimals(this->rightArmLowRotationAngle) != 0.00) || \
		(this->roundTo2Decimals(this->leftLegUpRotationAngle) != 0.00) || \
		(this->roundTo2Decimals(this->leftLegLowRotationAngle) != 0.00) || \
		(this->roundTo2Decimals(this->rightLegUpRotationAngle) != 0.00) || \
		(this->roundTo2Decimals(this->rightLegLowRotationAngle) != 0.00) \
	) {
		return false;
	}
	return true;
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

void Animation::walkingAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i) {
	auto& pivotLeftUpArm = body.getLeftUpArmPivot();
	auto& pivotLeftLowArm = body.getLeftLowArmPivot();

	auto& pivotRightUpArm = body.getRightUpArmPivot();
	auto& pivotRightLowArm = body.getRightLowArmPivot();

	auto& pivotLeftUpLeg = body.getLeftUpLegPivot();
	auto& pivotLeftLowLeg = body.getLeftLowLegPivot();

	auto& pivotRightUpLeg = body.getRightUpLegPivot();
	auto& pivotRightLowLeg = body.getRightLowLegPivot();

	switch (i)
	{
	case BodyPartsIndex::LEFTUPARM:
		this->leftArmUpRotation();
		matrix.setRotationYMatrix(this->leftArmUpRotationAngle);
		matrix.setPivotMatrix(pivotLeftUpArm.x, pivotLeftUpArm.y, pivotLeftUpArm.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
		matrix.setPivotMatrix(-pivotLeftUpArm.x, -pivotLeftUpArm.y, -pivotLeftUpArm.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "negativePivotMatrix");
		break;

	case BodyPartsIndex::LEFTLOWARM:
		this->leftArmLowRotation();
		matrix.setRotationYMatrix(this->leftArmLowRotationAngle);
		matrix.setPivotMatrix(pivotLeftLowArm.x, pivotLeftLowArm.y, pivotLeftLowArm.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
		matrix.setPivotMatrix(-pivotLeftLowArm.x, -pivotLeftLowArm.y, -pivotLeftLowArm.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "negativePivotMatrix");
		break;
	
	case BodyPartsIndex::RIGHTUPARM:
		this->rightArmUpRotation();
		matrix.setRotationYMatrix(this->rightArmUpRotationAngle);
		matrix.setPivotMatrix(pivotRightUpArm.x, pivotRightUpArm.y, pivotRightUpArm.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
		matrix.setPivotMatrix(-pivotRightUpArm.x, -pivotRightUpArm.y, -pivotRightUpArm.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "negativePivotMatrix");
		break; 

	case BodyPartsIndex::RIGHTLOWARM:
		this->rightArmLowRotation();
		matrix.setRotationYMatrix(this->rightArmLowRotationAngle);
		matrix.setPivotMatrix(pivotRightLowArm.x, pivotRightLowArm.y, pivotRightLowArm.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
		matrix.setPivotMatrix(-pivotRightLowArm.x, -pivotRightLowArm.y, -pivotRightLowArm.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "negativePivotMatrix");
		break; 
	
	case BodyPartsIndex::LEFTUPLEG:
		this->leftLegUpRotation();
		matrix.setRotationYMatrix(this->leftLegUpRotationAngle);
		matrix.setPivotMatrix(pivotLeftUpLeg.x, pivotLeftUpLeg.y, pivotLeftUpLeg.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
		matrix.setPivotMatrix(-pivotLeftUpLeg.x, -pivotLeftUpLeg.y, -pivotLeftUpLeg.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "negativePivotMatrix");
		break;

	case BodyPartsIndex::LEFTLOWLEG:
		this->leftLegLowRotation();
		matrix.setRotationYMatrix(this->leftLegLowRotationAngle);
		matrix.setPivotMatrix(pivotLeftLowLeg.x, pivotLeftLowLeg.y, pivotLeftLowLeg.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
		matrix.setPivotMatrix(-pivotLeftLowLeg.x, -pivotLeftLowLeg.y, -pivotLeftLowLeg.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "negativePivotMatrix");
		break;
	
	case BodyPartsIndex::RIGHTUPLEG:
		this->rightLegUpRotation();
		matrix.setRotationYMatrix(this->rightLegUpRotationAngle);
		matrix.setPivotMatrix(pivotRightUpLeg.x, pivotRightUpLeg.y, pivotRightUpLeg.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
		matrix.setPivotMatrix(-pivotRightUpLeg.x, -pivotRightUpLeg.y, -pivotRightUpLeg.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "negativePivotMatrix");
		break; 

	case BodyPartsIndex::RIGHTLOWLEG:
		this->rightLegLowRotation();
		matrix.setRotationYMatrix(this->rightLegLowRotationAngle);
		matrix.setPivotMatrix(pivotRightLowLeg.x, pivotRightLowLeg.y, pivotRightLowLeg.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
		matrix.setPivotMatrix(-pivotRightLowLeg.x, -pivotRightLowLeg.y, -pivotRightLowLeg.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "negativePivotMatrix");
		break;

	default:
		matrix.setModelToIdentity();
		shader.setUniformMatrix4x4(matrix.getIdentity(), "positivePivotMatrix");
		shader.setUniformMatrix4x4(matrix.getIdentity(), "negativePivotMatrix");
		break;
	}
	
	
	if ((i != BodyPartsIndex::HEAD) && (i != BodyPartsIndex::TORSO) &&(checkIfPartsFinished() == true)) {
		this->doneWithCycle = true;
		matrix.setModelToIdentity();
		shader.setUniformMatrix4x4(matrix.getModel(), "model");
		shader.setUniform1i(0, "walkingAnimation");
		return ;
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