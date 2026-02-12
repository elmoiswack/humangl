#ifndef BODYPART_HPP
# define BODYPART_HPP

class BodyPart
{
private:
	float width;
	float height;

public:
	BodyPart();
	BodyPart(float width, float height);
	virtual ~BodyPart() = 0;

	float getWidth() const;
	float getHeight() const;
};

#endif