#include "../includes/BodyParts.hpp"
#include <iostream>
#include <cmath>

BodyParts::BodyParts()
{
	this->body.resize(10);
    this->bodySizes.resize(10);
    this->pivotPoints.resize(10);

    this->bodySizes[BodyPartsIndex::HEAD] = {.1f, .1f, .1f};
	this->computeSizeToRectVertex(.1f, .1f, .1f, this->body[BodyPartsIndex::HEAD]);

    this->bodySizes[BodyPartsIndex::TORSO] = {.12f, .18f, .12f};
	this->computeSizeToRectVertex(.12f, .18f, .12f, this->body[BodyPartsIndex::TORSO]);
	
    this->bodySizes[BodyPartsIndex::LEFTUPARM] = {.035f, .07f, .035f};
	this->computeSizeToRectVertex(.035f, .07f, .035f, this->body[BodyPartsIndex::LEFTUPARM]);

    this->bodySizes[BodyPartsIndex::LEFTLOWARM] = {.035f, .07f, .035f};
	this->computeSizeToRectVertex(.035f, .07f, .035f, this->body[BodyPartsIndex::LEFTLOWARM]);
	
    this->bodySizes[BodyPartsIndex::RIGHTUPARM] = {.035f, .07f, .035f};
	this->computeSizeToRectVertex(.035f, .07f, .035f, this->body[BodyPartsIndex::RIGHTUPARM]);

    this->bodySizes[BodyPartsIndex::RIGHTLOWARM] = {.035f, .07f, .035f};
	this->computeSizeToRectVertex(.035f, .07f, .035f, this->body[BodyPartsIndex::RIGHTLOWARM]);
	
    this->bodySizes[BodyPartsIndex::LEFTUPLEG] = {.025f, .07f, .025f};
	this->computeSizeToRectVertex(.025f, .07f, .025f, this->body[BodyPartsIndex::LEFTUPLEG]);

    this->bodySizes[BodyPartsIndex::LEFTLOWLEG] = {.025f, .07f, .025f};
	this->computeSizeToRectVertex(.025f, .07f, .025f, this->body[BodyPartsIndex::LEFTLOWLEG]);

    this->bodySizes[BodyPartsIndex::RIGHTUPLEG] = {.025f, .07f, .025f};
	this->computeSizeToRectVertex(.025f, .07f, .025f, this->body[BodyPartsIndex::RIGHTUPLEG]);

    this->bodySizes[BodyPartsIndex::RIGHTLOWLEG] = {.025f, .07f, .025f};
	this->computeSizeToRectVertex(.025f, .07f, .025f, this->body[BodyPartsIndex::RIGHTLOWLEG]);

	this->computeBody();
	this->computePivotPoints();
}

BodyParts::~BodyParts() {}

void BodyParts::computeSizeToRectVertex(float width, float height, float depth, std::vector<SingleVertex3D>& result) {
	std::vector<SingleVertex3D> standardRect = {};

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

	result.clear();
    for (int face = 0; face < 6; face++) {
        unsigned int i = face * 4;
        result.push_back(standardRect[i]);
		result.push_back(standardRect[i + 1]); 
		result.push_back(standardRect[i + 2]);
        result.push_back(standardRect[i + 2]); 
		result.push_back(standardRect[i + 3]); 
		result.push_back(standardRect[i]);
    }
}

void BodyParts::computePivotUpper(SingleVertex3D& point, std::vector<SingleVertex3D>& bodypart) {
	float maxY = std::max_element(bodypart.begin(), bodypart.end(),
		[](const SingleVertex3D& a, const SingleVertex3D& b) {
			return a.y < b.y;
		}
	)->y;

	const float epsilon = 1e-6f;
	std::vector<SingleVertex3D> topVerts;
	for (const auto& v : bodypart) {
		if (std::fabs(v.y - maxY) < epsilon)
			topVerts.push_back(v);
	}

	float bestX = topVerts.front().x;
	float bestAbsX = std::fabs(bestX);
	for (const auto& v : topVerts) {
		float absX = std::fabs(v.x);
		if (absX < bestAbsX) {
			bestAbsX = absX;
			bestX = v.x;
		}
	}

	float sumX = 0.0f;
	float sumZ = 0.0f;
	int count = 0;

	for (const auto& v : topVerts) {
		if (std::fabs(v.x - bestX) < epsilon) {
			sumX += v.x;
			sumZ += v.z;
			count++;
		}
	}

	point.x = sumX / count;
	point.y = maxY;
	point.z = sumZ / count;
}

void BodyParts::computePivotLowerArm(SingleVertex3D& point, std::vector<SingleVertex3D>& upperArm) {
	float minY = std::min_element(upperArm.begin(), upperArm.end(),
		[](const SingleVertex3D& a, const SingleVertex3D& b) {
			return a.y < b.y;
		}
	)->y;

	const float epsilon = 1e-6f;
	float sumX = 0.0f;
	float sumZ = 0.0f;
	int count = 0;

	for (const auto& v : upperArm) {
		if (std::fabs(v.y - minY) < epsilon) {
			sumX += v.x;
			sumZ += v.z;
			count++;
		}
	}

	point.x = sumX / count;
	point.y = minY;
	point.z = sumZ / count;
}

void BodyParts::computePivotLowerLeg(SingleVertex3D& point, std::vector<SingleVertex3D>& upperLeg) {
	float minZ = std::min_element(upperLeg.begin(), upperLeg.end(),
		[](const SingleVertex3D& a, const SingleVertex3D& b) {
			return a.z < b.z;
		}
	)->z;

	const float epsilon = 1e-6f;
	float sumX = 0.0f;
	float sumY = 0.0f;
	int count = 0;

	for (const auto& v : upperLeg) {
		if (std::fabs(v.z - minZ) < epsilon) {
			sumX += v.x;
			sumY += v.y;
			count++;
		}
	}

	point.x = sumX / count;
	point.y = sumY / count;
	point.z = minZ;
}

void BodyParts::computeBody() {
	float armOffset = 0.04f;

    for (std::size_t i = 0; i < this->bodyPartSize; i++) {
        this->body[BodyPartsIndex::HEAD][i].y += this->bodySizes[BodyPartsIndex::TORSO].height + this->bodySizes[BodyPartsIndex::HEAD].height;

        this->body[BodyPartsIndex::LEFTUPARM][i].x -= (this->bodySizes[BodyPartsIndex::TORSO].width + this->bodySizes[BodyPartsIndex::LEFTUPARM].width);
        this->body[BodyPartsIndex::LEFTUPARM][i].y += (this->bodySizes[BodyPartsIndex::TORSO].height - this->bodySizes[BodyPartsIndex::LEFTUPARM].height) - armOffset; 

        this->body[BodyPartsIndex::LEFTLOWARM][i].x -= (this->bodySizes[BodyPartsIndex::TORSO].width + this->bodySizes[BodyPartsIndex::LEFTLOWARM].width);
        this->body[BodyPartsIndex::LEFTLOWARM][i].y += (this->bodySizes[BodyPartsIndex::TORSO].height - this->bodySizes[BodyPartsIndex::LEFTLOWARM].height) - (this->bodySizes[BodyPartsIndex::LEFTUPARM].height * 2) - armOffset;

        this->body[BodyPartsIndex::RIGHTUPARM][i].x += (this->bodySizes[BodyPartsIndex::TORSO].width + this->bodySizes[BodyPartsIndex::RIGHTUPARM].width);
        this->body[BodyPartsIndex::RIGHTUPARM][i].y += (this->bodySizes[BodyPartsIndex::TORSO].height - this->bodySizes[BodyPartsIndex::RIGHTUPARM].height) - armOffset;

        this->body[BodyPartsIndex::RIGHTLOWARM][i].x += (this->bodySizes[BodyPartsIndex::TORSO].width + this->bodySizes[BodyPartsIndex::RIGHTLOWARM].width);
        this->body[BodyPartsIndex::RIGHTLOWARM][i].y += (this->bodySizes[BodyPartsIndex::TORSO].height - this->bodySizes[BodyPartsIndex::RIGHTLOWARM].height) - (this->bodySizes[BodyPartsIndex::RIGHTUPARM].height * 2) - armOffset;

        this->body[BodyPartsIndex::LEFTUPLEG][i].x += (-this->bodySizes[BodyPartsIndex::TORSO].width + this->bodySizes[BodyPartsIndex::LEFTUPLEG].width);
        this->body[BodyPartsIndex::LEFTUPLEG][i].y -= (this->bodySizes[BodyPartsIndex::TORSO].height + this->bodySizes[BodyPartsIndex::LEFTUPLEG].height);

        this->body[BodyPartsIndex::LEFTLOWLEG][i].x += (-this->bodySizes[BodyPartsIndex::TORSO].width + this->bodySizes[BodyPartsIndex::LEFTLOWLEG].width);
        this->body[BodyPartsIndex::LEFTLOWLEG][i].y -= (this->bodySizes[BodyPartsIndex::TORSO].height + this->bodySizes[BodyPartsIndex::LEFTLOWLEG].height) + (this->bodySizes[BodyPartsIndex::LEFTUPLEG].height * 2);

        this->body[BodyPartsIndex::RIGHTUPLEG][i].x += (this->bodySizes[BodyPartsIndex::TORSO].width - this->bodySizes[BodyPartsIndex::RIGHTUPLEG].width);
        this->body[BodyPartsIndex::RIGHTUPLEG][i].y -= (this->bodySizes[BodyPartsIndex::TORSO].height + this->bodySizes[BodyPartsIndex::RIGHTUPLEG].height);

        this->body[BodyPartsIndex::RIGHTLOWLEG][i].x += (this->bodySizes[BodyPartsIndex::TORSO].width - this->bodySizes[BodyPartsIndex::RIGHTLOWLEG].width);
        this->body[BodyPartsIndex::RIGHTLOWLEG][i].y -= (this->bodySizes[BodyPartsIndex::TORSO].height + this->bodySizes[BodyPartsIndex::RIGHTLOWLEG].height) + (this->bodySizes[BodyPartsIndex::RIGHTUPLEG].height * 2);
    }
}

void BodyParts::computePivotPoints() {
	for (std::size_t i = 0; i < this->body.size(); i++) {
		if (i != BodyPartsIndex::HEAD && i != BodyPartsIndex::TORSO && i != BodyPartsIndex::LEFTLOWARM && i != BodyPartsIndex::RIGHTLOWARM)
			this->computePivotUpper(this->pivotPoints[i], this->body[i]);
		else if (i == BodyPartsIndex::LEFTLOWARM || i == BodyPartsIndex::RIGHTLOWARM)
			this->computePivotLowerArm(this->pivotPoints[i], this->body[i - 1]);
		else if (i == BodyPartsIndex::LEFTLOWLEG || i == BodyPartsIndex::RIGHTLOWLEG) 
			this->computePivotLowerLeg(this->pivotPoints[i], this->body[i - 1]);
	}
}


void BodyParts::recomputeBody(float width, float height, float depth, BodyPartsIndex part) {
	for (std::size_t i = 0; i < this->body.size(); i++) {
  		this->computeSizeToRectVertex(this->bodySizes[i].width, this->bodySizes[i].height, this->bodySizes[i].depth, this->body[i]);
	}

	this->computeBody();
	this->computePivotPoints();
}

void BodyParts::updateWidth(BodyPartsIndex part, float value) {
    this->bodySizes[part].width += value;

    if (this->bodySizes[part].width < 0.01f) {
        this->bodySizes[part].width = 0.01;
    } else if (this->bodySizes[part].width > 1.0f) {
        this->bodySizes[part].width = 1.0f;
    }

    this->recomputeBody(this->bodySizes[part].width, this->bodySizes[part].height, this->bodySizes[part].depth, part);
}

void BodyParts::updateHeight(BodyPartsIndex part, float value) {
    this->bodySizes[part].height += value;
    
    if (this->bodySizes[part].height < 0.01f) {
        this->bodySizes[part].height = 0.01;
    } else if (this->bodySizes[part].height > 1.0f) {
        this->bodySizes[part].height = 1.0f;
    }
    this->recomputeBody(this->bodySizes[part].width, this->bodySizes[part].height, this->bodySizes[part].depth, part);
}

void BodyParts::updateDepth(BodyPartsIndex part, float value) {
    this->bodySizes[part].depth += value;

    if (this->bodySizes[part].depth < 0.01f) {
        this->bodySizes[part].depth = 0.01;
    } else if (this->bodySizes[part].depth > 1.0f) {
        this->bodySizes[part].depth = 1.0f;
    }

    this->recomputeBody(this->bodySizes[part].width, this->bodySizes[part].height, this->bodySizes[part].depth, part);
}

std::vector<std::vector<SingleVertex3D>>& BodyParts::getBody() {
	return this->body;
}

SingleVertex3D& BodyParts::getLeftUpArmPivot() {
    return this->pivotPoints[BodyPartsIndex::LEFTUPARM];
}

SingleVertex3D& BodyParts::getLeftLowArmPivot() {
    return this->pivotPoints[BodyPartsIndex::LEFTLOWARM];
}

SingleVertex3D& BodyParts::getRightUpArmPivot() {
    return this->pivotPoints[BodyPartsIndex::RIGHTUPARM];
}

SingleVertex3D& BodyParts::getRightLowArmPivot() {
    return this->pivotPoints[BodyPartsIndex::RIGHTLOWARM];
}

SingleVertex3D& BodyParts::getLeftUpLegPivot() {
    return this->pivotPoints[BodyPartsIndex::LEFTUPLEG];
}

SingleVertex3D& BodyParts::getLeftLowLegPivot() {
    return this->pivotPoints[BodyPartsIndex::LEFTLOWLEG];
}

SingleVertex3D& BodyParts::getRightUpLegPivot() {
    return this->pivotPoints[BodyPartsIndex::RIGHTUPLEG];
}

SingleVertex3D& BodyParts::getRightLowLegPivot() {
    return this->pivotPoints[BodyPartsIndex::RIGHTLOWLEG];
}