#include "../../includes/Animation.hpp"

void Animation::incrementAngle(float& angle, bool& forward) {
	float speed = this->currentAnimation != AnimationTypes::RUN ? this->rotationSpeed : this->rotationSpeed * 1.5;

    if (angle + speed >= .90f) {
        angle = 0.90f;
		forward = !forward;
    } else {
        angle += speed;
    }
}

void Animation::decrementAngle(float& angle, bool& forward) {
	float speed = this->currentAnimation != AnimationTypes::RUN ? this->rotationSpeed : this->rotationSpeed * 1.5;

	if (angle - speed <= -.90f) {
		angle = -0.90f;
		forward = !forward;
    } else {
		angle -= speed;
    }
}

void Animation::computeRotationAngle(bool& forward, float& angle) {
	if (forward)
		this->incrementAngle(angle, forward);
	else
		this->decrementAngle(angle, forward);
}

void Animation::applyRotation(Shader& shader, Matrix& matrix, bool& forward, float& angle, SingleVertex3D& pivot) {
	this->computeRotationAngle(forward, angle);
	matrix.setRotationYMatrix(angle);
	matrix.setPivotMatrix(pivot.x, pivot.y, pivot.z);
	shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
	matrix.setPivotMatrix(-pivot.x, -pivot.y, -pivot.z);
	shader.setUniformMatrix4x4(matrix.getPivot(), "negativePivotMatrix");
}

void Animation::walkingAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i) {
	switch (i)
	{
	case BodyPartsIndex::LEFTUPARM:
		this->applyRotation(shader, matrix,
			this->leftArmUpRotationForward, this->leftArmUpRotationAngle,
			body.getLeftUpArmPivot());
		break;

	case BodyPartsIndex::LEFTLOWARM:
		this->applyRotation(shader, matrix,
			this->leftArmLowRotationForward, this->leftArmLowRotationAngle,
			body.getLeftUpArmPivot());
		break;
	
	case BodyPartsIndex::RIGHTUPARM:
		this->applyRotation(shader, matrix,
			this->rightArmUpRotationForward, this->rightArmUpRotationAngle,
			body.getRightUpArmPivot());
		break; 

	case BodyPartsIndex::RIGHTLOWARM:
		this->applyRotation(shader, matrix,
			this->rightArmLowRotationForward, this->rightArmLowRotationAngle,
			body.getRightUpArmPivot());
		break; 
	
	case BodyPartsIndex::LEFTUPLEG:
		this->applyRotation(shader, matrix,
			this->leftLegUpRotationForward, this->leftLegUpRotationAngle,
			body.getLeftUpLegPivot());
		break;

	case BodyPartsIndex::LEFTLOWLEG:
		this->applyRotation(shader, matrix,
			this->leftLegLowRotationForward, this->leftLegLowRotationAngle,
			body.getLeftUpLegPivot());
		break;
	
	case BodyPartsIndex::RIGHTUPLEG:
		this->applyRotation(shader, matrix,
			this->rightLegUpRotationForward, this->rightLegUpRotationAngle,
			body.getRightUpLegPivot());
		break; 

	case BodyPartsIndex::RIGHTLOWLEG:
		this->applyRotation(shader, matrix,
			this->rightLegLowRotationForward, this->rightLegLowRotationAngle,
			body.getRightUpLegPivot());
		break;

	default:
		matrix.setModelToIdentity();
		shader.setUniformMatrix4x4(matrix.getIdentity(), "positivePivotMatrix");
		shader.setUniformMatrix4x4(matrix.getIdentity(), "negativePivotMatrix");
		break;
	}
	
	if ((i != BodyPartsIndex::HEAD) && (i != BodyPartsIndex::TORSO) && (this->checkIfWalkingFinished())) {
		this->resetAnimation(shader, matrix);
		return ;
	}
	shader.setUniformMatrix4x4(matrix.getModel(), "model");
}

float Animation::roundTo2Decimals(float& angle) {
	float var = angle;
	float value = (int)(var * 100 + .5);
    return (float)value / 100;	
}

bool Animation::checkIfWalkingFinished() {
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