#include "../../includes/Animation.hpp"

void moveTowards(float& value, float target, float speed)
{
    if (value < target)
        value = std::min(value + speed, target);
    else
        value = std::max(value - speed, target);
}

void computeAngleForRotation(float& angle, float speed, bool decrease, bool left) {
	float maxAngle = 1.56f;
    float target = decrease ? 0.0f : (left ? maxAngle : -maxAngle);
    moveTowards(angle, target, speed);
}

void Animation::applyTposeRotation(Shader& shader, Matrix& matrix, bool& forward, float& angle, SingleVertex3D& pivot, bool left) {
	computeAngleForRotation(angle, this->rotationSpeed, this->tposeDecreaseAngle, left);
	matrix.setRotationZMatrix(angle);
	matrix.setPivotMatrix(pivot.x, pivot.y, pivot.z);
	shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
	matrix.setPivotMatrix(-pivot.x, -pivot.y, -pivot.z);
	shader.setUniformMatrix4x4(matrix.getPivot(), "negativePivotMatrix");
}

void Animation::tposeAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i) {
	switch (i)
	{
	case BodyPartsIndex::LEFTUPARM:
		this->applyTposeRotation(shader, matrix,
			this->leftArmUpRotationForward, this->leftArmUpRotationAngle,
			body.getLeftUpArmPivot(), true);
		break;

	case BodyPartsIndex::LEFTLOWARM:
		this->applyTposeRotation(shader, matrix,
			this->leftArmLowRotationForward, this->leftArmLowRotationAngle,
			body.getLeftUpArmPivot(), true);
		break;
	
	case BodyPartsIndex::RIGHTUPARM:
		this->applyTposeRotation(shader, matrix,
			this->rightArmUpRotationForward, this->rightArmUpRotationAngle,
			body.getRightUpArmPivot(), false);
		break; 

	case BodyPartsIndex::RIGHTLOWARM:
		this->applyTposeRotation(shader, matrix,
			this->rightArmLowRotationForward, this->rightArmLowRotationAngle,
			body.getRightUpArmPivot(), false);
		break; 

	default:
		matrix.setModelToIdentity();
		shader.setUniformMatrix4x4(matrix.getIdentity(), "positivePivotMatrix");
		shader.setUniformMatrix4x4(matrix.getIdentity(), "negativePivotMatrix");
		break;
	}
	
	if ((i >= BodyPartsIndex::LEFTUPARM) && (i <= BodyPartsIndex::RIGHTLOWARM) && (this->checkIfTposeFinished())) {
		this->resetAnimation(shader, matrix);
		return ;
	}
	shader.setUniformMatrix4x4(matrix.getModel(), "model");
}

bool Animation::checkIfTposeFinished() {
	if ((this->roundTo2Decimals(this->leftArmUpRotationAngle) != 0.00) || \
		(this->roundTo2Decimals(this->leftArmLowRotationAngle) != 0.00) || \
		(this->roundTo2Decimals(this->rightArmUpRotationAngle) != 0.00) || \
		(this->roundTo2Decimals(this->rightArmLowRotationAngle) != 0.00) \
	) {
		return false;
	}
	return true;
}

void Animation::decreaseAngleTpose() {
	this->tposeDecreaseAngle = true;
}