#ifndef BODYPARTS_HPP
# define BODYPARTS_HPP

#include <vector>
#include <algorithm>

struct SingleVertex {
	float x;
	float y;
	float z;
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
	std::vector<std::vector<SingleVertex>> body;
	int bodyPartSize = 72;
	
	float headWidth;
	float headHeight;
	float headDepth;

	float torsoWidth;
	float torsoHeight;
	float torsoDepth;

	float armLeftUpWidth;
	float armLeftUpHeight;
	float armLeftUpDepth;

	float armLeftLowWidth;
	float armLeftLowHeight;
	float armLeftLowDepth;

	float armRightUpWidth;
	float armRightUpHeight;
	float armRightUpDepth;

	float armRightLowWidth;
	float armRightLowHeight;
	float armRightLowDepth;

	float legLeftUpWidth;
	float legLeftUpHeight;
	float legLeftUpDepth;

	float legLeftLowWidth;
	float legLeftLowHeight;
	float legLeftLowDepth;

	float legRightUpWidth;
	float legRightUpHeight;
	float legRightUpDepth;

	float legRightLowWidth;
	float legRightLowHeight;
	float legRightLowDepth;

	SingleVertex armLeftUpPivotPoint;
	SingleVertex armLeftLowPivotPoint;

	SingleVertex armRightUpPivotPoint;
	SingleVertex armRightLowPivotPoint;

	SingleVertex legLeftUpPivotPoint;
	SingleVertex legLeftLowPivotPoint;

	SingleVertex legRightUpPivotPoint;
	SingleVertex legRightLowPivotPoint;

public:
	BodyParts();
	~BodyParts();
	
	void computeFacesForRectVertices(std::vector<SingleVertex>& input, std::vector<SingleVertex>& output);
	void computeSizeToRectVertex(float width, float height, float depth, std::vector<SingleVertex>& result);
	
	void computePivotPoint(SingleVertex& point, std::vector<SingleVertex>& array);
	void computeBody();
	std::vector<std::vector<SingleVertex>>& getBody();
	
	SingleVertex& getLeftUpArmPivot();
	SingleVertex& getLeftLowArmPivot();

	SingleVertex& getRightUpArmPivot();
	SingleVertex& getRightLowArmPivot();

	SingleVertex& getLeftUpLegPivot();
	SingleVertex& getLeftLowLegPivot();

	SingleVertex& getRightUpLegPivot();
	SingleVertex& getRightLowLegPivot();

};

#endif