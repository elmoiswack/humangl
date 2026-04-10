#ifndef BODYPARTS_HPP
# define BODYPARTS_HPP

#include <vector>
#include <algorithm>

struct SingleVertex3D {
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
	std::vector<std::vector<SingleVertex3D>> body;
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

	SingleVertex3D armLeftUpPivotPoint;
	SingleVertex3D armLeftLowPivotPoint;

	SingleVertex3D armRightUpPivotPoint;
	SingleVertex3D armRightLowPivotPoint;

	SingleVertex3D legLeftUpPivotPoint;
	SingleVertex3D legLeftLowPivotPoint;

	SingleVertex3D legRightUpPivotPoint;
	SingleVertex3D legRightLowPivotPoint;

public:
	BodyParts();
	~BodyParts();
	
	void computeFacesForRectVertices(std::vector<SingleVertex3D>& input, std::vector<SingleVertex3D>& output);
	void computeSizeToRectVertex(float width, float height, float depth, std::vector<SingleVertex3D>& result);
	
	void computePivotPoint(SingleVertex3D& point, std::vector<SingleVertex3D>& array);
	void computeBody();
	std::vector<std::vector<SingleVertex3D>>& getBody();
	
	SingleVertex3D& getLeftUpArmPivot();
	SingleVertex3D& getLeftLowArmPivot();

	SingleVertex3D& getRightUpArmPivot();
	SingleVertex3D& getRightLowArmPivot();

	SingleVertex3D& getLeftUpLegPivot();
	SingleVertex3D& getLeftLowLegPivot();

	SingleVertex3D& getRightUpLegPivot();
	SingleVertex3D& getRightLowLegPivot();

};

#endif