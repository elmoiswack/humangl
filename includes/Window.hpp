#ifndef WINDOW_HPP
# define WINDOW_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>
#include <iostream>
#include <vector>
#include <array>

#include "glad/glad.h"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Matrix.hpp"
#include "Animation.hpp"
#include "BodyParts.hpp"
#include "Button.hpp"

enum ButtonOrder {
	TITLE,
	BODY,
	COLOR,
	HEADINDEX,
	TORSOINDEX,
	LEFT,
	RIGHT,
	UPPER,
	LOWER,
	ARM,
	LEG,
	WIDTH,
	HEIGHT,
	DEPTH,
	RED,
	GREEN,
	BLUE,
};

struct SelectedButtons {
	bool body = false;
	bool color = false;
	bool head = false;
	bool torso = false;
	bool left = false;
	bool right = false;
	bool upper = false;
	bool lower = false;
	bool arm = false;
	bool leg = false;
	bool width = false;
	bool height = false;
	bool depth = false;
	bool red = false;
	bool green = false;
	bool blue = false;
};

class Window
{
private:
	SDL_Window* window;
	SDL_GLContext openGLContext;
	int width;
	int heigth;
	std::vector<Mesh> meshes;
	std::vector<Button> buttons;
	std::vector<GLTtext*> buttonLabels;
	SelectedButtons selectedButtons;
	Shader shader;
	Camera camera;
	Matrix matrix;
	Animation animations;

public:
	Window(const char* name, int width, int height, const char* pathVertexShader, const char* pathFragmentShader, BodyParts& body);
	Window(const char* name, int width, int height, const char* pathVertexShader, const char* pathFragmentShader);
	~Window();

	void initWindow(const char* name, int width, int height);
	void initButtons(int width, int height);
	void makeCurrent();

	SDL_Window* getWindow();
	SDL_WindowID getWindowId();

	void drawMeshOnWindow(Mesh& mesh);
	void drawText(Button& button, GLTtext* text);
	void clearScreen();

	void computeView();
	void rotateRight(float deltaTime);
	void rotateLeft(float deltaTime);
	void rotateUp(float deltaTime);
	void rotateDown(float deltaTime);

	std::vector<Mesh>& getMeshes();
	std::vector<Button>& getButtons();
	std::vector<GLTtext*>& getButtonsLabels();
	Shader& getShader();
	Camera& getCamera();
	Matrix& getMatrix();
	Animation& getAnimations();

	bool checkIfButtonPressed(float x, float y, BodyParts& body, std::vector<Mesh>& meshes);
	bool checkStruct(ButtonType type, BodyParts& body, std::vector<Mesh>& meshes);
	BodyPartsIndex getSelectedPart();
	bool modifyPart(BodyPartsIndex part, ButtonType type, BodyParts& body, std::vector<Mesh>& meshes);
	void updateMeshBody(BodyParts& body);
	void updateMeshColor(Mesh& mesh, int colorIndex, float value);

	void updateStruct(std::size_t i);
	void checkButtonCounterpart();

	class FailedWindowCreation : public std::exception {
	public:
		const char *what() const throw() {
			return ("Failed to create window or openGL context!");
		}
	};
};

#endif
