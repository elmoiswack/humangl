#include "../../includes/Animation.hpp"

void Animation::walkingAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i) {
	auto& pivotLeftUpArm = body.getLeftUpArmPivot();
	auto& pivotRightUpArm = body.getRightUpArmPivot();
	auto& pivotLeftUpLeg = body.getLeftUpLegPivot();
	auto& pivotRightUpLeg = body.getRightUpLegPivot();


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
		matrix.setPivotMatrix(pivotLeftUpArm.x, pivotLeftUpArm.y, pivotLeftUpArm.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
		matrix.setPivotMatrix(-pivotLeftUpArm.x, -pivotLeftUpArm.y, -pivotLeftUpArm.z);
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
		matrix.setPivotMatrix(pivotRightUpArm.x, pivotRightUpArm.y, pivotRightUpArm.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
		matrix.setPivotMatrix(-pivotRightUpArm.x, -pivotRightUpArm.y, -pivotRightUpArm.z);
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
		matrix.setPivotMatrix(pivotLeftUpLeg.x, pivotLeftUpLeg.y, pivotLeftUpLeg.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
		matrix.setPivotMatrix(-pivotLeftUpLeg.x, -pivotLeftUpLeg.y, -pivotLeftUpLeg.z);
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
		matrix.setPivotMatrix(pivotRightUpLeg.x, pivotRightUpLeg.y, pivotRightUpLeg.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "positivePivotMatrix");
		matrix.setPivotMatrix(-pivotRightUpLeg.x, -pivotRightUpLeg.y, -pivotRightUpLeg.z);
		shader.setUniformMatrix4x4(matrix.getPivot(), "negativePivotMatrix");
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