#include "../../includes/Animation.hpp"

void Animation::incrementHeight() {
	if (this->incrementJumpHeight && this->currentJumpHeight >= this->maxJumpHeight) {
		this->currentJumpHeight = this->maxJumpHeight;
		this->incrementJumpHeight = false;
		return ;
	}
	if (this->incrementJumpHeight && this->currentJumpHeight < this->maxJumpHeight) {
		this->currentJumpHeight += this->jumpSpeed;
		return ;
	}
	if (!this->incrementJumpHeight && this->currentJumpHeight <= 0.0f) {
		this->currentJumpHeight = 0.0f;
		this->incrementJumpHeight = true;
		return ;
	}
	if (!this->incrementJumpHeight && this->currentAnimation > 0.0f) {
		this->currentJumpHeight -= this->jumpSpeed;
		return ;
	}
}

void Animation::jumpAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i) {
	if (i == 0 ) {
		this->incrementHeight();
		shader.setUniform1f(this->currentJumpHeight, "jumpHeight");
	}
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

	if (this->checkIfJumpFinished()) {
		this->resetAnimation(shader, matrix);
		return ;
	}
	shader.setUniformMatrix4x4(matrix.getModel(), "model");
}

bool Animation::checkIfJumpFinished() {
	if ((this->roundTo2Decimals(this->currentJumpHeight) == 0.0f) && (this->incrementJumpHeight == true)) {
		return true;
	}
	return false;
}