#ifndef VERTEX_HPP
# define VERTEX_HPP

#include <iostream>
#include <vector>

struct SingleVertex {
	float x;
	float y;
	float z;
};

class Vertex
{
private:
	float centerX;
	float centerY;
	int screenWidth;
	int screenHeight;
public:
	Vertex(const unsigned int screenWidth, const unsigned int screenHeight);
	~Vertex();

	void computeFacesForRectVertices(std::vector<SingleVertex>& input, std::vector<SingleVertex>& output);
	void computeSizeToRectVertex(float width, float height, float depth, std::vector<SingleVertex>& result);
};

#endif