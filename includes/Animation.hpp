#ifndef ANIMATION_HPP
# define ANIMATION_HPP

#include "Shader.hpp"
#include "Matrix.hpp"
#include "BodyParts.hpp"
#include "Mesh.hpp"

enum AnimationTypes {
	IDLE,
	WALKING,
	JUMP,
	RUN,
	TPOSE,
	FLEX,
	CROUCH,
};

class Animation
{
private:
	AnimationTypes currentAnimation;
	float rotationSpeed;

	float headRotationAngle;
	float torsoRotationAngle;

	float leftArmUpRotationAngle;
	bool leftArmUpRotationForward;

	float leftArmLowRotationAngle;
	bool leftArmLowRotationForward;

	float rightArmUpRotationAngle;
	bool rightArmUpRotationForward;

	float rightArmLowRotationAngle;
	bool rightArmLowRotationForward;

	float leftLegUpRotationAngle;
	bool leftLegUpRotationForward;

	float leftLegLowRotationAngle;
	bool leftLegLowRotationForward;

	float rightLegUpRotationAngle;
	bool rightLegUpRotationForward;

	float rightLegLowRotationAngle;
	bool rightLegLowRotationForward;

	float currentJumpHeight;
	float maxJumpHeight;
	float jumpSpeed;
	bool incrementJumpHeight;

	bool tposeDecreaseAngle;
	bool flexDecreaseAngle;
	bool crouchDecreaseAngle;

	SingleVertex3D tmpPivot = {0.0f, 0.0f, 0.0f};

	float leftUpArmComposedTransform[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};;
	float rightUpArmComposedTransform[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};;
	SingleVertex3D leftUpArmPivotUsed;
	SingleVertex3D rightUpArmPivotUsed;

public:
	Animation();
	~Animation();

	void checkAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::vector<Mesh>& meshes, std::size_t i);
	void resetAnimation(Shader& shader, Matrix& matrix);
	
	bool isAnimationFinished();
	void startAnimation(AnimationTypes whichAnimation);
	AnimationTypes getCurrentAnimation();

	void moveTowards(float& value, float target, float speed);
	float roundTo2Decimals(float& angle);
	void setPivotPoint(SingleVertex3D& pivot, Shader& shader, Matrix& matrix);
	void setPivotPointFlex(SingleVertex3D& pivot, Shader& shader, Matrix& matrix, float* outPositivePivot, float* outNegativePivot);
	
	void walkingAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i);
	void computeAngleWalking(bool& forward, float& angle);
	void incrementAngle(float& angle, bool& forward);
	void decrementAngle(float& angle, bool& forward);
	void applyWalkingRotation(Shader& shader, Matrix& matrix, bool& forward, float& angle, SingleVertex3D& pivot);
	bool checkIfWalkingFinished();

	void jumpAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i);
	void incrementHeight();
	bool checkIfJumpFinished();

	void tposeAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i);
	void applyTposeRotation(Shader& shader, Matrix& matrix, bool& forward, float& angle, SingleVertex3D& pivot, bool left);
	void computeAngleTpose(float& angle, bool decrease, bool left);
	void decreaseAngleTpose();
	bool checkIfTposeFinished();

	void flexAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::vector<Mesh>& meshes, std::size_t i);
	void applyFlexRotation(Shader& shader, Matrix& matrix, bool& forward, float& angle, SingleVertex3D& pivot, bool left, bool lower, float* composedTransform);
	void computeAngleFlex(float& angle, bool left, bool lower);
	bool checkIfFlexFinished();	
	void decreaseAngleFlex();

	void crouchAnimation(Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i);
	bool checkIfCrouchFinished();
	void decreaseAngleCrouch();
	void crouchForward(float& angle);

};

#endif