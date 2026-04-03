#ifndef WINDOW_HPP
# define WINDOW_HPP

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>

#include "glad/glad.h"
#include "Mesh.hpp"
#include "Shader.hpp"

class Window
{
private:
	SDL_Window* window;
	SDL_GLContext openGLContext;
public:
	Window(const char* name, int width, int height);
	~Window();

	void makeCurrent();

	SDL_WindowID getWindowId();

	void drawMeshOnWindow(Mesh& mesh, Shader& shader);

	class FailedWindowCreation : public std::exception {
	public:
		const char *what() const throw() {
			return ("Failed to create window or openGL context!");
		}
	};
};

#endif