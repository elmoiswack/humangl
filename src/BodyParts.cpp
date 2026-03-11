#include "../includes/BodyParts.hpp"

BodyParts::BodyParts()
{
	this->body.resize(6);

	this->headWidth = .1f;
	this->headHeight = .1f;
	this->headDepth = .1f;

	this->torsoWidth = .15f;
	this->torsoHeight = .25f;
	this->torsoDepth = .15f;
	
	this->armLeftWidth = 0.035f;
	this->armLeftHeight = .18f;
	this->armLeftDepth = .1f;
	
	this->armRightWidth = 0.035f;
	this->armRightHeight = .18f;
	this->armRightDepth = .1f;
	
	this->legLeftWidth = .05f;
	this->legLeftHeight = .15f;
	this->legLeftDepth = .05f;
	
	this->legRightWidth = .05f;
	this->legRightHeight = .15f;
	this->legRightDepth = .05f;

	this->computeSizeToRectVertex(this->headWidth, this->headHeight, this->headDepth, this->body[BodyPartsIndex::HEAD]);
	this->computeSizeToRectVertex(this->torsoWidth, this->torsoHeight, this->torsoDepth, this->body[BodyPartsIndex::TORSO]);
	this->computeSizeToRectVertex(this->armLeftWidth, this->armLeftHeight, this->armLeftDepth, this->body[BodyPartsIndex::LEFTARM]);
	this->computeSizeToRectVertex(this->armRightWidth, this->armRightHeight, this->armRightDepth, this->body[BodyPartsIndex::RIGHTARM]);
	this->computeSizeToRectVertex(this->legLeftWidth, this->legLeftHeight, this->legLeftDepth, this->body[BodyPartsIndex::LEFTLEG]);
	this->computeSizeToRectVertex(this->legRightWidth, this->legRightHeight, this->legRightDepth, this->body[BodyPartsIndex::RIGHTLEG]);
	
	this->computingMax.resize(this->bodyPartSize);
	this->combinedVertices.resize(this->bodyPartSize * this->body.size());
}

BodyParts::~BodyParts() {}

void BodyParts::computeFacesForRectVertices(std::vector<SingleVertex>& input, std::vector<SingleVertex>& output) {
	const int standardOrder[72] = {
		0, 0, 0,
		1, 1, 0,
		2, 2, 0,
		3, 3, 0,

		4, 4, 1,
		5, 5, 1,
		6, 6, 1,
		7, 7, 1,

		8, 8, 2,
		9, 9, 2,
		10, 10, 2,
		11, 11, 2,

		12, 12, 3,
		13, 13, 3,
		14, 14, 3,
		15, 15, 3,
		
		16, 16, 4,
		17, 17, 4,
		18, 18, 4,
		19, 19, 4,

		20, 20, 5,
		21, 21, 5,
		22, 22, 5,
		23, 23, 0,
	};

	for (int i = 0; i < 72; i++) {
		output.push_back(input[standardOrder[i]]);
	}

}

void BodyParts::computeSizeToRectVertex(float width, float height, float depth, std::vector<SingleVertex>& result) {
	std::vector<SingleVertex> standardRect = {};

	standardRect.push_back({-width, -height, depth});
	standardRect.push_back({width, -height, depth});
	standardRect.push_back({width, height, depth});
	standardRect.push_back({-width, height, depth});

	standardRect.push_back({width, -height, -depth});
	standardRect.push_back({-width, -height, -depth});
	standardRect.push_back({-width, height, -depth});
	standardRect.push_back({width, height, -depth});

	standardRect.push_back({-width, -height, -depth});
	standardRect.push_back({-width, -height, depth});
	standardRect.push_back({-width, height, depth});
	standardRect.push_back({-width, height, -depth});

	standardRect.push_back({width, -height, depth});
	standardRect.push_back({width, -height, -depth});
	standardRect.push_back({width, height, -depth});
	standardRect.push_back({width, height, depth});

	standardRect.push_back({-width, height, depth});
	standardRect.push_back({width, height, depth});
	standardRect.push_back({width, height, -depth});
	standardRect.push_back({-width, height, -depth});

	standardRect.push_back({-width, -height, -depth});
	standardRect.push_back({width, -height, -depth});
	standardRect.push_back({width, -height, depth});
	standardRect.push_back({-width, -height, depth});

	this->computeFacesForRectVertices(standardRect, result);
}

void BodyParts::computeBody() {
    for (std::size_t i = 0; i < this->bodyPartSize; i++) {
        this->body[BodyPartsIndex::HEAD][i].y += this->torsoHeight + this->headHeight;

        this->body[BodyPartsIndex::LEFTARM][i].x = -(this->body[BodyPartsIndex::LEFTARM][i].x - (-this->torsoWidth + -this->armLeftWidth));
        this->body[BodyPartsIndex::LEFTARM][i].y += (this->torsoHeight - this->armLeftHeight);
        this->body[BodyPartsIndex::LEFTARM][i].z -= (this->torsoDepth - this->armLeftDepth);

        this->body[BodyPartsIndex::RIGHTARM][i].x = (this->body[BodyPartsIndex::RIGHTARM][i].x + (this->torsoWidth + this->armRightWidth));
        this->body[BodyPartsIndex::RIGHTARM][i].y += (this->torsoHeight - this->armRightHeight);
        this->body[BodyPartsIndex::RIGHTARM][i].z -= (this->torsoDepth - this->armRightDepth);

        this->body[BodyPartsIndex::LEFTLEG][i].y = -(this->body[BodyPartsIndex::LEFTLEG][i].y - (-this->torsoHeight + -this->legLeftHeight));
        this->body[BodyPartsIndex::LEFTLEG][i].x += -this->torsoWidth + this->legLeftWidth;
        this->body[BodyPartsIndex::LEFTLEG][i].z -= (this->torsoDepth - this->legLeftDepth);

        this->body[BodyPartsIndex::RIGHTLEG][i].y = -(this->body[BodyPartsIndex::RIGHTLEG][i].y - (-this->torsoHeight + -this->legRightHeight));
        this->body[BodyPartsIndex::RIGHTLEG][i].x += this->torsoWidth - this->legRightWidth;
        this->body[BodyPartsIndex::RIGHTLEG][i].z -= (this->torsoDepth - this->legRightDepth);
    }

	std::size_t index = 0;

	for (std::size_t y = 0; y < this->body.size(); y++) {
		for (std::size_t x = 0; x < this->bodyPartSize; x++) {
			this->combinedVertices[index] = this->body[y][x];
			index++;
		}
	}
}

std::vector<SingleVertex>& BodyParts::getCombinedBody() {
	return this->combinedVertices;
}


///////////////////HEAD///////////////////////
void BodyParts::computeHead() {
	this->computeSizeToRectVertex(this->headWidth, this->headHeight, this->headDepth, this->body[BodyPartsIndex::HEAD]);
	this->computeBody();
}

void BodyParts::setHeadWith(float value) {
	this->headWidth = value;
	this->computeHead();
}

void BodyParts::setHeadHeight(float value) {
	this->headHeight = value;
	this->computeHead();
}

void BodyParts::setHeadDepth(float value) {
	this->headDepth = value;
	this->computeHead();
}

///////////////////TORSO//////////////////////
void BodyParts::computeTorso() {
	this->computeSizeToRectVertex(this->torsoWidth, this->torsoHeight, this->torsoDepth, this->body[BodyPartsIndex::TORSO]);
	this->computeBody();
}

void BodyParts::setTorsoWidth(float value) {
	this->torsoWidth = value;
	this->computeTorso();
}

void BodyParts::setTorsoHeight(float value) {
	this->torsoHeight = value;
	this->computeTorso();
}

void BodyParts::setTorsoDepth(float value) {
	this->torsoDepth = value;
	this->computeTorso();
}

///////////////////LEFT ARM////////////////////
void BodyParts::computeLeftArm() {
	this->computeSizeToRectVertex(this->armLeftWidth, this->armLeftHeight, this->armLeftDepth, this->body[BodyPartsIndex::LEFTARM]);
	this->computeBody();
}

void BodyParts::setLeftArmWidth(float value) {
	this->armLeftWidth = value;
	this->computeLeftArm();
}

void BodyParts::setLeftArmHeight(float value) {
	this->armLeftHeight = value;
	this->computeLeftArm();
}

void BodyParts::setLeftArmDepth(float value) {
	this->armLeftDepth = value;
	this->computeLeftArm();
}

///////////////////RIGHT ARM///////////////////
void BodyParts::computeRightArm() {
	this->computeSizeToRectVertex(this->armRightWidth, this->armRightHeight, this->armRightDepth, this->body[BodyPartsIndex::RIGHTARM]);
	this->computeBody();
}

void BodyParts::setRightArmWidth(float value) {
	this->armRightWidth = value;
	this->computeRightArm();
}

void BodyParts::setRightArmHeight(float value) {
	this->armRightHeight = value;
	this->computeRightArm();
}

void BodyParts::setRightArmDepth(float value) {
	this->armRightDepth = value;
	this->computeRightArm();
}

///////////////////LEFT LEG////////////////////
void BodyParts::computeLeftLeg() {
	this->computeSizeToRectVertex(this->legLeftWidth, this->legLeftHeight, this->legLeftDepth, this->body[BodyPartsIndex::LEFTLEG]);
	this->computeBody();
}

void BodyParts::setLeftLegWidth(float value) {
	this->legLeftWidth = value;
	this->computeLeftLeg();
}

void BodyParts::setLeftLegHeight(float value) {
	this->legLeftHeight = value;
	this->computeLeftLeg();
}

void BodyParts::setLeftLegDepth(float value) {
	this->legLeftDepth = value;
	this->computeLeftLeg();
}

///////////////////RIGHT LEG///////////////////
void BodyParts::computeRightLeg() {
	this->computeSizeToRectVertex(this->legRightWidth, this->legRightHeight, this->legRightDepth, this->body[BodyPartsIndex::RIGHTLEG]);
	this->computeBody();
}

void BodyParts::setRightLegWidth(float value) {
	this->legRightWidth = value;
	this->computeRightLeg();
}

void BodyParts::setRightLegHeight(float value) {
	this->legRightHeight = value;
	this->computeRightLeg();
}

void BodyParts::setRightLegDepth(float value) {
	this->legRightDepth = value;
	this->computeRightLeg();
}

