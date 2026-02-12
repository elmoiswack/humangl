#include "./includes/BodyPart.hpp"

BodyPart::BodyPart( )
{
}

BodyPart::BodyPart(float width, float height) : width(width), height(height)
{
}

BodyPart::~BodyPart()
{
}

float BodyPart::getWidth() const {
	return this->width;
}

float BodyPart::getHeight() const {
	return this->height;
}
