#ifndef BODYPARTS_HPP
# define BODYPARTS_HPP

#include <vector>
#include <algorithm>

struct SingleVertex3D {
	float x;
	float y;
	float z;
};

struct BodyPartDimensions {
	float width;
	float height;
	float depth;
};

enum BodyPartsIndex {
	HEAD,
	TORSO,
	LEFTUPARM,
	LEFTLOWARM,
	RIGHTUPARM,
	RIGHTLOWARM,
	LEFTUPLEG,
	LEFTLOWLEG,
	RIGHTUPLEG,
	RIGHTLOWLEG,
};

class BodyParts
{
private:
	std::vector<std::vector<SingleVertex3D>> body;
	std::vector<BodyPartDimensions> bodySizes;
	std::vector<SingleVertex3D> pivotPoints;
	int bodyPartSize = 36;
	float incrementingValueBody = 0.05;
	float incrementingValueColor = 0.1;

public:
	BodyParts();
	~BodyParts();
	
	void computeSizeToRectVertex(float width, float height, float depth, std::vector<SingleVertex3D>& result);
	void computePivotPoint(SingleVertex3D& point, std::vector<SingleVertex3D>& bodypart);
	void computeBody();
	void recomputeBody(float width, float height, float depth, BodyPartsIndex part);
	
	void updateWidth(BodyPartsIndex part, float value);
	void updateHeight(BodyPartsIndex part, float value);
	void updateDepth(BodyPartsIndex part, float value);
	
	std::vector<std::vector<SingleVertex3D>>& getBody();

	SingleVertex3D& getLeftUpArmPivot();
	SingleVertex3D& getRightUpArmPivot();
	SingleVertex3D& getLeftUpLegPivot();
	SingleVertex3D& getRightUpLegPivot();

};

#endif