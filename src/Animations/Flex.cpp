#include "../../includes/Animation.hpp"

void Animation::computeAngleFlex(float& angle, bool decrease, bool left, bool lower) {
	float target = 0.0f;

	if (lower) {
		float maxAngleLower = 2.0f;
    	target = decrease ? 0.0f : (left ? maxAngleLower : -maxAngleLower);
	} else {
		float maxAngleUpper = 1.56f;
		target = decrease ? 0.0f : (left ? maxAngleUpper : -maxAngleUpper);
	}
    this->moveTowards(angle, target, this->rotationSpeed);
}


struct tmp4Vertex {
	float x;
	float y;
	float z;
	float a;
};

SingleVertex3D computeNewPivotPoint(Matrix& matrix, std::vector<SingleVertex3D> bodyPart) {
	auto rotationMatrix = matrix.getModel();
	std::vector<tmp4Vertex> vertices;
	for (auto& v : bodyPart) {
		vertices.push_back({v.x, v.y, v.z, 1.0f});
	}

	//IDEA: mult every index of vertices with the rotation matrix, compute back to singleVertex3D, compute and return new pivot point

}

void Animation::applyFlexRotation(Shader& shader, Matrix& matrix, bool& forward, float& angle, SingleVertex3D& pivot, bool left, bool lower) {
	std::cout << "pivotx = " << pivot.x << ", pivoty: " << pivot.y  << ", pivot.z: " << pivot.z << std::endl;
	
	this->computeAngleFlex(angle, this->flexDecreaseAngle, left, lower);
	matrix.setRotationZMatrix(angle);
	this->setPivotPoint(pivot, shader, matrix);
}

void Animation::flexAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i) {
	switch (i)
	{
	case BodyPartsIndex::LEFTUPARM:
		std::cout << "UPLEFT" << std::endl;
		this->applyFlexRotation(shader, matrix,
			this->leftArmUpRotationForward, this->leftArmUpRotationAngle,
			body.getLeftUpArmPivot(), true, false);
		break;

	case BodyPartsIndex::LEFTLOWARM:
		std::cout << "LOWLEFT" << std::endl;
		if (this->leftArmLowRotationAngle >= 1.56f) {
			SingleVertex3D pivot = computeNewPivotPoint(matrix, body.getBody()[i]);

			this->applyFlexRotation(shader, matrix,
				this->leftArmLowRotationForward, this->leftArmLowRotationAngle,
				pivot, true, true);
		} else {
			this->applyFlexRotation(shader, matrix,
				this->leftArmLowRotationForward, this->leftArmLowRotationAngle,
				body.getLeftUpArmPivot(), true, true);			
		}
		break;
	
	case BodyPartsIndex::RIGHTUPARM:
		this->applyFlexRotation(shader, matrix,
			this->rightArmUpRotationForward, this->rightArmUpRotationAngle,
			body.getRightUpArmPivot(), false, false);
		break; 

	case BodyPartsIndex::RIGHTLOWARM:
		this->applyFlexRotation(shader, matrix,
			this->rightArmLowRotationForward, this->rightArmLowRotationAngle,
			body.getRightUpArmPivot(), false, true);
		break; 

	default:
		matrix.setModelToIdentity();
		shader.setUniformMatrix4x4(matrix.getIdentity(), "positivePivotMatrix");
		shader.setUniformMatrix4x4(matrix.getIdentity(), "negativePivotMatrix");
		break;
	}
	
	if ((i >= BodyPartsIndex::LEFTUPARM) && (i <= BodyPartsIndex::RIGHTLOWARM) && (this->checkIfFlexFinished())) {
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