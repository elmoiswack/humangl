#include "../../includes/Animation.hpp"

void Animation::computeAngleFlex(float& angle, bool decrease, bool left, bool lower) {
	float target = 0.0f;

	if (lower) {
		float maxAngleLower = 2.2f;
    	target = decrease ? 0.0f : (left ? maxAngleLower : -maxAngleLower);
	} else {
		float maxAngleUpper = 1.56f;
		target = decrease ? 0.0f : (left ? maxAngleUpper : -maxAngleUpper);
	}
    this->moveTowards(angle, target, this->rotationSpeed);
}

void Animation::applyFlexRotation(Shader& shader, Matrix& matrix, bool& forward, float& angle, SingleVertex3D& pivot, bool left, bool lower, float* outLocalComposite) {
    this->computeAngleFlex(angle, this->flexDecreaseAngle, left, lower);
    matrix.setRotationZMatrix(angle);

    float positivePivot[16];
    float negativePivot[16];
    this->setPivotPointFlex(pivot, shader, matrix, positivePivot, negativePivot);

    float temp[16];
    matrix.multiplyInto(temp, positivePivot, matrix.getModel());
    matrix.multiplyInto(outLocalComposite, temp, negativePivot);
}

void Animation::flexAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::vector<Mesh>& meshes, std::size_t i) {
	switch (i)
	{
	case BodyPartsIndex::LEFTUPARM:
	
		std::cout << "UPLEFT" << std::endl;
		shader.setUniformMatrix4x4(matrix.getIdentity(), "parentTransform");
		this->applyFlexRotation(shader, matrix,
			this->leftArmUpRotationForward, this->leftArmUpRotationAngle,
			body.getLeftUpArmPivot(), true, false,
			this->leftUpArmComposedTransform);
		break;


	case BodyPartsIndex::LEFTLOWARM:
	
		std::cout << "LOWLEFT" << std::endl;
		if (this->leftArmLowRotationAngle == 1.56f)
			shader.setUniformMatrix4x4(this->leftUpArmComposedTransform, "parentTransform");

		float unusedComposite[16];
		this->applyFlexRotation(shader, matrix,
			this->leftArmLowRotationForward, this->leftArmLowRotationAngle,
			body.getLeftUpArmPivot(), true, true,
			unusedComposite);
		break;

	
	case BodyPartsIndex::RIGHTUPARM:
	
		std::cout << "RIGHTUP" << std::endl;
		shader.setUniformMatrix4x4(matrix.getIdentity(), "parentTransform");
		this->applyFlexRotation(shader, matrix,
			this->rightArmUpRotationForward, this->rightArmUpRotationAngle,
			body.getRightUpArmPivot(), false, false,
			this->rightUpArmComposedTransform);
		break;


	case BodyPartsIndex::RIGHTLOWARM:
	
		std::cout << "RIGHTLOW" << std::endl;
		if (this->rightArmLowRotationAngle == 1.56f)
			shader.setUniformMatrix4x4(this->rightUpArmComposedTransform, "parentTransform");

		float unusedComposite[16];
		this->applyFlexRotation(shader, matrix,
			this->rightArmLowRotationForward, this->rightArmLowRotationAngle,
			body.getRightUpArmPivot(), false, true,
			unusedComposite);
		break; 


	default:
		matrix.setModelToIdentity();
		shader.setUniformMatrix4x4(matrix.getIdentity(), "parentTransform");
		shader.setUniformMatrix4x4(matrix.getIdentity(), "positivePivotMatrix");
		shader.setUniformMatrix4x4(matrix.getIdentity(), "negativePivotMatrix");
		break;
	}
	
	if ((i >= BodyPartsIndex::LEFTUPARM) && (i <= BodyPartsIndex::RIGHTLOWARM) && (this->checkIfFlexFinished())) {
		matrix.setModelToIdentity();
		shader.setUniformMatrix4x4(matrix.getIdentity(), "parentTransform");
		shader.setUniformMatrix4x4(matrix.getIdentity(), "positivePivotMatrix");
		shader.setUniformMatrix4x4(matrix.getIdentity(), "negativePivotMatrix");
		this->resetAnimation(shader, matrix);
		return ;
	}
	shader.setUniformMatrix4x4(matrix.getModel(), "model");
}

bool Animation::checkIfFlexFinished() {
	if ((this->roundTo2Decimals(this->leftArmUpRotationAngle) != 0.00) || \
		(this->roundTo2Decimals(this->leftArmLowRotationAngle) != 0.00) || \
		(this->roundTo2Decimals(this->rightArmUpRotationAngle) != 0.00) || \
		(this->roundTo2Decimals(this->rightArmLowRotationAngle) != 0.00) \
	) {
		return false;
	}
	return true;
}

void Animation::decreaseAngleFlex() {
	this->flexDecreaseAngle = true;
}