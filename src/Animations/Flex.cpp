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

void testMultMatrixVertice(float* matrix, SingleVertex3D& vertice) {
	float x = vertice.x;
	float y = vertice.y;
	float z = vertice.z;
	float a = 1.0f;

	vertice.x = (x * matrix[0]) + (y * matrix[4]) + (z * matrix[8]) + (a * matrix[12]);
	vertice.y = (x * matrix[1]) + (y * matrix[5]) + (z * matrix[9]) + (a * matrix[13]);
	vertice.z = (x * matrix[2]) + (y * matrix[6]) + (z * matrix[10]) + (a * matrix[14]);
	// vertice.a = (x * matrix[3]) + (y * matrix[7]) + (z * matrix[11]) + (a * matrix[15]);

}
#include <cmath>

void newPivotLowerArm(SingleVertex3D& point, std::vector<SingleVertex3D>& uppperarm) { 
	float minY = std::min_element(
		uppperarm.begin(),
		uppperarm.end(),
		[](const SingleVertex3D& a, const SingleVertex3D& b) {
			return a.y < b.y;
		}
	)->y;

	
	std::vector<SingleVertex3D> topVerts;
	for (const auto& v : uppperarm) {
		if (v.y <= minY)
			topVerts.push_back(v);
	}

	for (const auto& v : topVerts ) {
		std::cout << "v.x: " << v.x << ", v.y: " << v.y << ", v.z: " << v.z << std::endl;
	}

	float sumX = 0.0f;
	float sumZ = 0.0f;
	int count = 0;
	for (const auto& v : topVerts) {
			sumX += v.x;
			sumZ += v.z;
			count++;
	}

	point.x = -0.120000f;
	point.y = 0.150000f;
	point.z = 0.10000f;
}

SingleVertex3D computeNewPivotPoint(Matrix& matrix, BodyParts& body, std::size_t i) {

	auto rotationMatrix = matrix.getModel();
	std::vector<SingleVertex3D> copy(body.getBody()[i]);

	std::cout << copy.size() << std::endl;

	for (auto& v : copy) {
		testMultMatrixVertice(rotationMatrix, v);
	}

	SingleVertex3D pivotPoint;

	newPivotLowerArm(pivotPoint, copy);

	std::cout << "NEW PIVOTX: " << pivotPoint.x << ", PIVOTY: " << pivotPoint.y << ", PIVOTZ: " << pivotPoint.z << std::endl;
	// pivotPoint.x = fabs(pivotPoint.x);
	// pivotPoint.y = fabs(pivotPoint.y);
	// pivotPoint.z = fabs(pivotPoint.z);
	// std::cout << "AFTER FABS PIVOTX: " << pivotPoint.x << ", PIVOTY: " << pivotPoint.y << ", PIVOTZ: " << pivotPoint.z << std::endl;
	

	return pivotPoint;

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
			SingleVertex3D pivot = computeNewPivotPoint(matrix, body, BodyPartsIndex::LEFTUPARM);

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
		std::cout << "RIGHTUP" << std::endl;

		this->applyFlexRotation(shader, matrix,
			this->rightArmUpRotationForward, this->rightArmUpRotationAngle,
			body.getRightUpArmPivot(), false, false);
		break; 

	case BodyPartsIndex::RIGHTLOWARM:
		std::cout << "RIGHTLOW" << std::endl;

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