#include "../includes/Button.hpp"

Button::Button(ButtonType type)
{
	this->type = type;
	if (type == ButtonType::PLUS) {
		this->vertices = {
			SingleVertex2D{-0.6f,  0.2f},
			SingleVertex2D{0.6f,  0.2f},
			SingleVertex2D{0.6f, -0.2f},

			SingleVertex2D{-0.6f,  0.2f},
			SingleVertex2D{0.6f, -0.2f},
			SingleVertex2D{-0.6f, -0.2f},

			SingleVertex2D{-0.2f,  0.6f},
			SingleVertex2D{0.2f,  0.6f},
			SingleVertex2D{0.2f, -0.6f},

			SingleVertex2D{-0.2f,  0.6f},
			SingleVertex2D{0.2f, -0.6f},
			SingleVertex2D{-0.2f, -0.6f},
		};
		this->size = 12;
	} else if (type == ButtonType::MINUS) {
		this->vertices = {
			SingleVertex2D{-0.6f,  0.2f},
			SingleVertex2D{0.6f,  0.2f},
			SingleVertex2D{0.6f, -0.2f},

			SingleVertex2D{-0.6f,  0.2f},
			SingleVertex2D{0.6f, -0.2f},
			SingleVertex2D{-0.6f, -0.2f},
		};		
		this->size = 6;
	}
}

Button::~Button()
{

}

std::vector<SingleVertex2D>& Button::getVertices() {
	return this->vertices;
}

