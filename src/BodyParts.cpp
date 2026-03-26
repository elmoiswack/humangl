#include "../includes/BodyParts.hpp"

BodyParts::BodyParts()
{
	this->body.resize(10);

	this->headWidth = .1f;
	this->headHeight = .1f;
	this->headDepth = .1f;
	this->computeSizeToRectVertex(this->headWidth, this->headHeight, this->headDepth, this->body[BodyPartsIndex::HEAD]);


	this->torsoWidth = .15f;
	this->torsoHeight = .25f;
	this->torsoDepth = .15f;
	this->computeSizeToRectVertex(this->torsoWidth, this->torsoHeight, this->torsoDepth, this->body[BodyPartsIndex::TORSO]);
	
	this->armLeftUpWidth = 0.035f;
	this->armLeftUpHeight = .07f;
	this->armLeftUpDepth = 0.035f;
	this->computeSizeToRectVertex(this->armLeftUpWidth, this->armLeftUpHeight, this->armLeftUpDepth, this->body[BodyPartsIndex::LEFTUPARM]);
	this->computePivotPoint(this->armLeftUpPivotPoint, this->body[BodyPartsIndex::LEFTUPARM]);

	this->armLeftLowWidth = 0.035f;
	this->armLeftLowHeight = .07f;
	this->armLeftLowDepth = 0.035f;
	this->computeSizeToRectVertex(this->armLeftLowWidth, this->armLeftLowHeight, this->armLeftLowDepth, this->body[BodyPartsIndex::LEFTLOWARM]);
	this->computePivotPoint(this->armLeftLowPivotPoint, this->body[BodyPartsIndex::LEFTLOWARM]);
	
	this->armRightUpWidth = 0.035f;
	this->armRightUpHeight = .07f;
	this->armRightUpDepth = 0.035f;
	this->computeSizeToRectVertex(this->armRightUpWidth, this->armRightUpHeight, this->armRightUpDepth, this->body[BodyPartsIndex::RIGHTUPARM]);
	this->computePivotPoint(this->armRightUpPivotPoint, this->body[BodyPartsIndex::RIGHTUPARM]);

	this->armRightLowWidth = 0.035f;
	this->armRightLowHeight = .07f;
	this->armRightLowDepth = 0.035f;
	this->computeSizeToRectVertex(this->armRightLowWidth, this->armRightLowHeight, this->armRightLowDepth, this->body[BodyPartsIndex::RIGHTLOWARM]);
	this->computePivotPoint(this->armRightLowPivotPoint, this->body[BodyPartsIndex::RIGHTLOWARM]);
	
	this->legLeftUpWidth = .025;
	this->legLeftUpHeight = .07;
	this->legLeftUpDepth = .025;
	this->computeSizeToRectVertex(this->legLeftUpWidth, this->legLeftUpHeight, this->legLeftUpDepth, this->body[BodyPartsIndex::LEFTUPLEG]);
	this->computePivotPoint(this->legLeftUpPivotPoint, this->body[BodyPartsIndex::LEFTUPLEG]);

	this->legLeftLowWidth = .025;
	this->legLeftLowHeight = .07;
	this->legLeftLowDepth = .025;
	this->computeSizeToRectVertex(this->legLeftLowWidth, this->legLeftLowHeight, this->legLeftLowDepth, this->body[BodyPartsIndex::LEFTLOWLEG]);
	this->computePivotPoint(this->legLeftLowPivotPoint, this->body[BodyPartsIndex::LEFTLOWLEG]);

	this->legRightUpWidth = .025;
	this->legRightUpHeight = .07;
	this->legRightUpDepth = .025;
	this->computeSizeToRectVertex(this->legRightUpWidth, this->legRightUpHeight, this->legRightUpDepth, this->body[BodyPartsIndex::RIGHTUPLEG]);
	this->computePivotPoint(this->legRightUpPivotPoint, this->body[BodyPartsIndex::RIGHTUPLEG]);

	this->legRightLowWidth = .025;
	this->legRightLowHeight = .07;
	this->legRightLowDepth = .025;
	this->computeSizeToRectVertex(this->legRightLowWidth, this->legRightLowHeight, this->legRightLowDepth, this->body[BodyPartsIndex::RIGHTLOWLEG]);
	this->computePivotPoint(this->legRightLowPivotPoint, this->body[BodyPartsIndex::RIGHTLOWLEG]);

	this->computeBody();
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

void BodyParts::computePivotPoint(SingleVertex& point, std::vector<SingleVertex>& array) {
	float maxY = std::max_element(
		array.begin(),
		array.end(),
		[](const SingleVertex& a, const SingleVertex& b) {
			return a.y < b.y;
    	}
	)->y;

	float sumX = 0.0f;
	float sumZ = 0.0f;
	int count = 0;

	for (const auto& v : array)
	{
		if (v.y == maxY)
		{
			sumX += v.x;
			sumZ += v.z;
			count++;
		}
	}

	point.x = sumX / count;
	point.y = maxY;
	point.z = sumZ / count;
}

void BodyParts::computeBody() {
    for (std::size_t i = 0; i < this->bodyPartSize; i++) {
        this->body[BodyPartsIndex::HEAD][i].y += this->torsoHeight + this->headHeight;

        this->body[BodyPartsIndex::LEFTUPARM][i].x -= (this->torsoWidth + this->armLeftUpWidth);
        this->body[BodyPartsIndex::LEFTUPARM][i].y += (this->torsoHeight - this->armLeftUpHeight);
        this->body[BodyPartsIndex::LEFTUPARM][i].z -= ((this->torsoDepth / 2) - this->armLeftUpDepth);

        this->body[BodyPartsIndex::LEFTLOWARM][i].x -= (this->torsoWidth + this->armLeftLowWidth);
        this->body[BodyPartsIndex::LEFTLOWARM][i].y += (this->torsoHeight - this->armLeftLowHeight) - (this->armLeftUpHeight * 2);
        this->body[BodyPartsIndex::LEFTLOWARM][i].z -= ((this->torsoDepth / 2) - this->armLeftLowDepth);

        this->body[BodyPartsIndex::RIGHTUPARM][i].x += (this->torsoWidth + this->armRightUpWidth);
        this->body[BodyPartsIndex::RIGHTUPARM][i].y += (this->torsoHeight - this->armRightUpHeight);
        this->body[BodyPartsIndex::RIGHTUPARM][i].z -= ((this->torsoDepth / 2) - this->armRightUpDepth);

        this->body[BodyPartsIndex::RIGHTLOWARM][i].x += (this->torsoWidth + this->armRightLowWidth);
        this->body[BodyPartsIndex::RIGHTLOWARM][i].y += (this->torsoHeight - this->armRightLowHeight) - (this->armRightUpHeight * 2);
        this->body[BodyPartsIndex::RIGHTLOWARM][i].z -= ((this->torsoDepth / 2) - this->armRightLowDepth);

        this->body[BodyPartsIndex::LEFTUPLEG][i].y -= (this->torsoHeight + this->legLeftUpHeight);
        this->body[BodyPartsIndex::LEFTUPLEG][i].x += (-this->torsoWidth + this->legLeftUpWidth);
        this->body[BodyPartsIndex::LEFTUPLEG][i].z -= ((this->torsoDepth / 2) - this->legLeftUpDepth);

        this->body[BodyPartsIndex::LEFTLOWLEG][i].y -= (this->torsoHeight + this->legLeftLowHeight) + (this->legLeftUpHeight * 2);
        this->body[BodyPartsIndex::LEFTLOWLEG][i].x += (-this->torsoWidth + this->legLeftLowWidth);
        this->body[BodyPartsIndex::LEFTLOWLEG][i].z -= ((this->torsoDepth / 2) - this->legLeftLowDepth);

        this->body[BodyPartsIndex::RIGHTUPLEG][i].y -= (this->torsoHeight + this->legRightUpHeight);
        this->body[BodyPartsIndex::RIGHTUPLEG][i].x += (this->torsoWidth - this->legRightUpWidth);
        this->body[BodyPartsIndex::RIGHTUPLEG][i].z -= ((this->torsoDepth / 2) - this->legRightUpDepth);

        this->body[BodyPartsIndex::RIGHTLOWLEG][i].y -= (this->torsoHeight + this->legRightLowHeight) + (this->legRightUpHeight * 2);
        this->body[BodyPartsIndex::RIGHTLOWLEG][i].x += (this->torsoWidth - this->legRightLowWidth);
        this->body[BodyPartsIndex::RIGHTLOWLEG][i].z -= ((this->torsoDepth / 2) - this->legRightLowDepth);
    }
}

std::vector<std::vector<SingleVertex>>& BodyParts::getBody() {
	return this->body;
}

SingleVertex& BodyParts::getLeftUpArmPivot() {
	return this->armLeftUpPivotPoint;
}

SingleVertex& BodyParts::getLeftLowArmPivot() {
	return this->armLeftLowPivotPoint;
}

SingleVertex& BodyParts::getRightUpArmPivot() {
	return this->armRightUpPivotPoint;
}

SingleVertex& BodyParts::getRightLowArmPivot() {
	return this->armRightLowPivotPoint;
}

SingleVertex& BodyParts::getLeftUpLegPivot() {
	return this->legLeftUpPivotPoint;
}

SingleVertex& BodyParts::getLeftLowLegPivot() {
	return this->legLeftLowPivotPoint;
}

SingleVertex& BodyParts::getRightUpLegPivot() {
	return this->legRightUpPivotPoint;
}

SingleVertex& BodyParts::getRightLowLegPivot() {
	return this->legRightLowPivotPoint;
}
