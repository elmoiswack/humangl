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

void Vertex::computeSizeToRectVertex(float width, float height, float depth, float* result) {
	if (width == 0.0f || height == 0.0f) {
		float tmp[18] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0, 0.0f, 0.0f, 0.0f, 0.0f};
		result = tmp;
		return ;
	}
	
	float halfW = width / 2;
	float halfH = height / 2;
	float halfD = depth / 2;

	result[0] = halfW;
	result[1] = halfH;
	result[2] = 0.0f;
	result[3] = -halfW;
	result[4] = -halfH;
	result[5] = 0.0f;
	result[6] = halfW;
	result[7] = -halfH;
	result[8] = 0.0f;

	result[9] = halfW;
	result[10] = halfH;
	result[11] = 0.0f;
	result[12] = -halfW;
	result[13] = -halfH;
	result[14] = 0.0f;
	result[15] = -halfW;
	result[16] = halfH;
	result[17] = 0.0f;
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
		23, 23, 5,
	};

	for (int i = 0; i < 72; i++) {
		output.push_back(input[standardOrder[i]]);
	}

}

void Vertex::computeSizeToRectVertex(float width, float height, float depth, std::vector<SingleVertex>& result) {
	float halfW = width / 2;
	float halfH = height / 2;
	float halfD = depth / 2;

	std::vector<SingleVertex> standardRect = {};

	standardRect.push_back({-halfW, -halfH, halfD});
	standardRect.push_back({halfW, -halfH, halfD});
	standardRect.push_back({halfW, halfH, halfD});
	standardRect.push_back({-halfW, halfH, halfD});

	standardRect.push_back({halfW, -halfH, -halfD});
	standardRect.push_back({-halfW, -halfH, -halfD});
	standardRect.push_back({-halfW, halfH, -halfD});
	standardRect.push_back({halfW, halfH, -halfD});

	standardRect.push_back({-halfW, -halfH, -halfD});
	standardRect.push_back({-halfW, -halfH, halfD});
	standardRect.push_back({-halfW, halfH, halfD});
	standardRect.push_back({-halfW, halfH, -halfD});

	standardRect.push_back({halfW, -halfH, halfD});
	standardRect.push_back({halfW, -halfH, -halfD});
	standardRect.push_back({halfW, halfH, -halfD});
	standardRect.push_back({halfW, halfH, halfD});

	standardRect.push_back({-halfW, halfH, halfD});
	standardRect.push_back({halfW, halfH, halfD});
	standardRect.push_back({halfW, halfH, -halfD});
	standardRect.push_back({-halfW, halfH, -halfD});

	standardRect.push_back({-halfW, -halfH, -halfD});
	standardRect.push_back({halfW, -halfH, -halfD});
	standardRect.push_back({halfW, -halfH, halfD});
	standardRect.push_back({-halfW, -halfH, halfD});

	this->computeFacesForRectVertices(standardRect, result);
}
