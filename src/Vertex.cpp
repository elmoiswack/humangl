#include "../includes/Vertex.hpp"

Vertex::Vertex(const unsigned int screenWidth, const unsigned int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->centerX = screenWidth * 0.5;
	this->centerY = screenHeight * 0.5;
}

Vertex::~Vertex()
{
}

void Vertex::computeFacesForRectVertices(std::vector<SingleVertex>& input, std::vector<SingleVertex>& output) {

	int standardOrder[72] = {
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

void Vertex::computeSizeToRectVertex(float width, float height, float depth, std::vector<SingleVertex>& result) {
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
