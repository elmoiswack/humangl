#include "../includes/BodyParts.hpp"

BodyParts::BodyParts(Vertex& vertex)
{
	this->body.resize(6);

	this->headWidth = .1f;
	this->headHeight = .2f;
	this->headDepth = .1f;
	vertex.computeSizeToRectVertex(this->headWidth, this->headHeight, this->headDepth, this->body[BodyPartsIndex::HEAD]);

	this->torsoWidth = .15f;
	this->torsoHeight = .25f;
	this->torsoDepth = .15f;
	vertex.computeSizeToRectVertex(this->torsoWidth, this->torsoHeight, this->torsoDepth, this->body[BodyPartsIndex::TORSO]);
	
	this->armLeftWidth = 0.035f;
	this->armLeftHeight = .18f;
	this->armLeftDepth = .1f;
	vertex.computeSizeToRectVertex(this->armLeftWidth, this->armLeftHeight, this->armLeftDepth, this->body[BodyPartsIndex::LEFTARM]);
	
	this->armRightWidth = 0.035f;
	this->armRightHeight = .18f;
	this->armRightDepth = .1f;
	vertex.computeSizeToRectVertex(this->armRightWidth, this->armRightHeight, this->armRightDepth, this->body[BodyPartsIndex::RIGHTARM]);
	
	this->legLeftWidth = .05f;
	this->legLeftHeight = .15f;
	this->legLeftDepth = .05f;
	vertex.computeSizeToRectVertex(this->legLeftWidth, this->legLeftHeight, this->legLeftDepth, this->body[BodyPartsIndex::LEFTLEG]);
	
	this->legRightWidth = .05f;
	this->legRightHeight = .15f;
	this->legRightDepth = .05f;
	vertex.computeSizeToRectVertex(this->legRightWidth, this->legRightHeight, this->legRightDepth, this->body[BodyPartsIndex::RIGHTLEG]);
	
	this->computingMax.resize(this->body[BodyPartsIndex::HEAD].size());
	this->combinedVertices.resize(this->body[BodyPartsIndex::HEAD].size() * 6);
}

BodyParts::~BodyParts() {}

void BodyParts::computeBody() {
	for (std::size_t i = 0; i < 72; i++) {
		this->body[BodyPartsIndex::HEAD][i].y += this->torsoHeight;
		
		this->body[BodyPartsIndex::LEFTARM][i].x = -(this->body[BodyPartsIndex::LEFTARM][i].x - (-this->torsoWidth + -this->armLeftWidth));
		this->body[BodyPartsIndex::LEFTARM][i].y += ((this->torsoHeight - this->armLeftHeight) / 1.2);
		
		this->body[BodyPartsIndex::RIGHTARM][i].x = (this->body[BodyPartsIndex::RIGHTARM][i].x + (this->torsoWidth + this->armRightWidth));
		this->body[BodyPartsIndex::RIGHTARM][i].y += ((this->torsoHeight - this->armRightHeight) / 1.2);

		this->body[BodyPartsIndex::LEFTLEG][i].y = -(this->body[BodyPartsIndex::LEFTLEG][i].y - (-this->torsoHeight + -this->legLeftHeight));
		this->body[BodyPartsIndex::LEFTLEG][i].x += -this->torsoWidth + this->legLeftWidth;

		this->body[BodyPartsIndex::RIGHTLEG][i].y = -(this->body[BodyPartsIndex::RIGHTLEG][i].y - (-this->torsoHeight + -this->legRightHeight));
		this->body[BodyPartsIndex::RIGHTLEG][i].x += this->torsoWidth - this->legRightWidth;
	}

	std::size_t index = 0;

	for (std::size_t y = 0; y < 6; y++) {
		for (std::size_t x = 0; x < 72; x++) {
			this->combinedVertices[index] = this->body[y][x];
			index++;
		}
	}
}

std::vector<SingleVertex>& BodyParts::getCombinedBody() {
	return this->combinedVertices;
}

void BodyParts::setHeadWith(float value) {
	this->headWidth = value;
}

void BodyParts::setHeadHeight(float value) {
	this->headHeight = value;
}

void BodyParts::setHeadDepth(float value) {
	this->headDepth = value;
}

void BodyParts::setTorsoWidth(float value) {
	this->torsoWidth = value;
}

void BodyParts::setTorsoHeight(float value) {
	this->torsoHeight = value;
}

void BodyParts::setTorsoDepth(float value) {
	this->torsoDepth = value;
}