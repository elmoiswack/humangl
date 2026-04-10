#ifndef BUTTON_HPP
# define BUTTON_HPP

#include <iostream>
#include <vector>

struct SingleVertex2D {
	float x;
	float y;
};

enum ButtonType {
	PLUS,
	MINUS,
};

class Button
{
private:
	std::vector<SingleVertex2D> vertices;
	int size;
	ButtonType type;
public:
	Button(ButtonType type);
	~Button();

	std::vector<SingleVertex2D>& getVertices();
};



#endif