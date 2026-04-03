#include "../includes/Window.hpp"

Window::Window(const char* name, int width, int height)
{
	this->window = SDL_CreateWindow(name, width, height, SDL_WINDOW_OPENGL);
	if (this->window == nullptr) {
		std::cout << "SHIIII WINDOW: " << SDL_GetError() << std::endl;
		throw FailedWindowCreation();
	}

	this->openGLContext = SDL_GL_CreateContext(this->window);
	if (this->openGLContext == nullptr) {
		std::cout << "SHIIII openGLContext: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(this->window);
		throw FailedWindowCreation();
	}
	
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cout << "SHIIII GLAD" << std::endl;
		throw FailedWindowCreation();
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glViewport(0, 0, width, height);
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
}

Window::~Window()
{
	SDL_GL_DestroyContext(this->openGLContext);
	SDL_DestroyWindow(this->window);
}

void Window::makeCurrent() {
	if (!SDL_GL_MakeCurrent(this->window, this->openGLContext)) {
		std::cout << "Failed to make current: " << SDL_GetError() << std::endl;
	}
	if (!SDL_GL_SetSwapInterval(1)) {
		std::cout << "Failed to setSwap: " << SDL_GetError() << std::endl;
	}
}

SDL_WindowID Window::getWindowId() {
	return SDL_GetWindowID(this->window);
}

void Window::drawMeshOnWindow(Mesh& mesh, Shader& shader) {
	shader.setUniformVec3(mesh.getColor(), "color");
	glBindVertexArray(mesh.getVAO());
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, mesh.getVertexCount());
	glBindVertexArray(0);	
}