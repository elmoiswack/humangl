#ifndef BODYPARTS_HPP
# define BODYPARTS_HPP

#include <vector>
#include <algorithm>
#include "Vertex.hpp"

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
	BodyParts(Vertex& vertex);
	~BodyParts();

	void computeBody();

	std::vector<SingleVertex>& getCombinedBody();

	void setHeadWith(float value);
	void setHeadHeight(float value);
	void setHeadDepth(float value);
	void setTorsoWidth(float value);
	void setTorsoHeight(float value);
	void setTorsoDepth(float value);
};

#endif