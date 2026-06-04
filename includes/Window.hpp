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

class Window
{
private:
	SDL_Window* window;
	SDL_GLContext openGLContext;
	int width;
	int heigth;

	std::vector<Mesh> meshes;
	std::vector<Button> buttons;
	Shader shader;
	Camera camera;
	Matrix matrix;
	Animation animations;

public:
	Window(const char* name, int width, int height, const char* pathVertexShader, const char* pathFragmentShader, BodyParts& body);
	Window(const char* name, int width, int height, const char* pathVertexShader, const char* pathFragmentShader);
	~Window();

	void initWindow(const char* name, int width, int height);

	void makeCurrent();

	SDL_Window* getWindow();
	SDL_WindowID getWindowId();

	void drawMeshOnWindow(Mesh& mesh);
	void clearScreen();

	void computeView();

	std::vector<Mesh>& getMeshes();
	std::vector<Button>& getButtons();
	Shader& getShader();
	Camera& getCamera();
	Matrix& getMatrix();
	Animation& getAnimations();

	class FailedWindowCreation : public std::exception {
	public:
		const char *what() const throw() {
			return ("Failed to create window or openGL context!");
		}
	};
};

#endif
