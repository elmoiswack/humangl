#include "../../includes/Animation.hpp"

void Animation::crouchForward(float& angle) {
    float target = this->crouchDecreaseAngle ? 0.0f : .25f;
	this->moveTowards(angle, target, this->rotationSpeed);
}

void Animation::crouchAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i) {
	float unusedComposite[16];

	switch (i)
	{
	case BodyPartsIndex::HEAD:
		this->crouchForward(this->headRotationAngle);
		matrix.setRotationXMatrix(this->headRotationAngle);
		break;

	case BodyPartsIndex::TORSO:
		this->crouchForward(this->torsoRotationAngle);
		matrix.setRotationXMatrix(this->torsoRotationAngle);

		break;

	case BodyPartsIndex::LEFTUPARM:
		this->crouchForward(this->leftArmUpRotationAngle);
		matrix.setRotationXMatrix(this->leftArmUpRotationAngle);
		
		break;

	case BodyPartsIndex::LEFTLOWARM:
		this->crouchForward(this->leftLegLowRotationAngle);
		matrix.setRotationXMatrix(this->leftLegLowRotationAngle);

		break;
	
	case BodyPartsIndex::RIGHTUPARM:
		this->crouchForward(this->rightArmUpRotationAngle);
		matrix.setRotationXMatrix(this->rightArmUpRotationAngle);
		
		break;

	case BodyPartsIndex::RIGHTLOWARM:
		this->crouchForward(this->rightArmLowRotationAngle);
		matrix.setRotationXMatrix(this->rightArmLowRotationAngle);
		
		break;
	
	case BodyPartsIndex::LEFTUPLEG:
		matrix.setModelToIdentity();
		break;

	case BodyPartsIndex::LEFTLOWLEG:
		matrix.setModelToIdentity();
		break;
	
	case BodyPartsIndex::RIGHTUPLEG:
		matrix.setModelToIdentity();
		break; 

	case BodyPartsIndex::RIGHTLOWLEG:
		matrix.setModelToIdentity();
		break;

	default:
		matrix.setModelToIdentity();
		shader.setUniformMatrix4x4(matrix.getIdentity(), "positivePivotMatrix");
		shader.setUniformMatrix4x4(matrix.getIdentity(), "negativePivotMatrix");
		break;
	}
	
	if (this->checkIfCrouchFinished()) {
		this->resetAnimation(shader, matrix);
		return ;
	}
	shader.setUniformMatrix4x4(matrix.getModel(), "model");
}

bool Animation::checkIfCrouchFinished() {
	if ((this->roundTo2Decimals(this->headRotationAngle) != 0.00) || \
		(this->roundTo2Decimals(this->torsoRotationAngle) != 0.00) || \
		(this->roundTo2Decimals(this->leftArmUpRotationAngle) != 0.00) || \
		(this->roundTo2Decimals(this->leftArmLowRotationAngle) != 0.00) || \
		(this->roundTo2Decimals(this->rightArmUpRotationAngle) != 0.00) || \
		(this->roundTo2Decimals(this->rightArmLowRotationAngle) != 0.00) \
	) {
		return false;
	}
	return true;
}

void Animation::decreaseAngleCrouch() {
	this->crouchDecreaseAngle = true;
}