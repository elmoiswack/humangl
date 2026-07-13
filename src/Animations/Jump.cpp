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
	if (i == 0) {
		this->incrementHeight();
		shader.setUniform1f(this->currentJumpHeight, "jumpHeight");
	}

	if (this->checkIfJumpFinished()) {
		this->resetAnimation(shader, matrix);
		return ;
	}
}

bool Animation::checkIfJumpFinished() {
	if ((this->roundTo2Decimals(this->currentJumpHeight) == 0.0f) && (this->incrementJumpHeight == true)) {
		return true;
	}
	return false;
}