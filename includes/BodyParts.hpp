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
	LEFTARM,
	RIGHTARM,
	LEFTLEG,
	RIGHTLEG,
};

class BodyParts
{
private:
	std::vector<std::vector<SingleVertex>> body;
	std::vector<SingleVertex> combinedVertices;
	std::vector<float> computingMax;

	int bodyPartSize = 72;
	
	float headWidth;
	float headHeight;
	float headDepth;

	float torsoWidth;
	float torsoHeight;
	float torsoDepth;

	float armLeftWidth;
	float armLeftHeight;
	float armLeftDepth;

	float armRightWidth;
	float armRightHeight;
	float armRightDepth;

	float legLeftWidth;
	float legLeftHeight;
	float legLeftDepth;

	float legRightWidth;
	float legRightHeight;
	float legRightDepth;

public:
	BodyParts();
	~BodyParts();
	
	void computeFacesForRectVertices(std::vector<SingleVertex>& input, std::vector<SingleVertex>& output);
	void computeSizeToRectVertex(float width, float height, float depth, std::vector<SingleVertex>& result);
	
	void computeBody();
	std::vector<SingleVertex>& getCombinedBody();

	void computeHead();
	void setHeadWith(float value);
	void setHeadHeight(float value);
	void setHeadDepth(float value);

	void computeTorso();
	void setTorsoWidth(float value);
	void setTorsoHeight(float value);
	void setTorsoDepth(float value);
	
	void computeLeftArm();
	void setLeftArmWidth(float value);
	void setLeftArmHeight(float value);
	void setLeftArmDepth(float value);

	void computeRightArm();
	void setRightArmWidth(float value);
	void setRightArmHeight(float value);
	void setRightArmDepth(float value);

	void computeLeftLeg();
	void setLeftLegWidth(float value);
	void setLeftLegHeight(float value);
	void setLeftLegDepth(float value);

	void computeRightLeg();
	void setRightLegWidth(float value);
	void setRightLegHeight(float value);
	void setRightLegDepth(float value);
	
};

#endif