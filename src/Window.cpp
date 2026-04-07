#include "../includes/Window.hpp"

Window::Window(const char* name, int width, int height, const char* pathVertexShader, const char* pathFragmentShader) :
	body(),
	camera(),
	matrix(width, height),
	animations()
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
	
	if (!SDL_GL_MakeCurrent(this->window, this->openGLContext)) {
		std::cout << "Failed to make current: " << SDL_GetError() << std::endl;
	}
	this->heigth = height;
	this->width = width;

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glViewport(0, 0, width, height);
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

	std::vector<std::array<float, 3>> colors = {
		{0.8f, 0.0f, 0.0f}, 
		{1.f, 1.f, 1.f}, 
		{0.0f, 0.4f, 0.0f},
		{1.0f, .0f, .0f},
		{0.0f, 0.4f, 0.0f},
		{1.0f, .0f, .0f},
		{0.8f, 0.0f, 0.8f}, 
		{0.0f, 0.8f, 0.0f}, 
		{0.8f, 0.0f, 0.8f},
		{0.0f, 0.8f, 0.0f}, 
	};
	this->meshes = {};
	auto bodyParts = this->body.getBody();
	for (size_t i = 0; i < bodyParts.size(); ++i) {
		this->meshes.emplace_back(Mesh(bodyParts[i], colors[i].data()));
	}

	this->shader = Shader(pathVertexShader, pathFragmentShader);
	this->shader.useProgram();
	this->shader.setUniformMatrix4x4(this->matrix.getPerspective(), "perspective");
	this->shader.setUniformMatrix4x4(this->matrix.getModel(), "model");
	this->computeView();
}

Window::~Window()
{
	SDL_GL_DestroyContext(this->openGLContext);
	SDL_DestroyWindow(this->window);
	for (auto& mesh: this->meshes) {
		mesh.deleteMesh();
	}
}

void Window::makeCurrent() {
	if (!SDL_GL_MakeCurrent(this->window, this->openGLContext)) {
		std::cout << "Failed to make current: " << SDL_GetError() << std::endl;
	}

	if (!SDL_GL_SetSwapInterval(1)) {
		std::cout << "Failed to setSwap: " << SDL_GetError() << std::endl;
	}
	this->shader.useProgram();
}

SDL_Window* Window::getWindow() {
	return this->window;
}


SDL_WindowID Window::getWindowId() {
	return SDL_GetWindowID(this->window);
}

void Window::drawMeshOnWindow(std::size_t index) {
	this->shader.setUniformVec3(this->meshes[index].getColor(), "color");
	glBindVertexArray(this->meshes[index].getVAO());
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, this->meshes[index].getVertexCount());
	glBindVertexArray(0);
}

void Window::clearScreen() {
	this->makeCurrent();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::computeView() {
	this->matrix.computeViewMatrix(this->camera);
	this->shader.setUniformMatrix4x4(this->matrix.getView(), "view");
}

BodyParts& Window::getBody() {
	return this->body;
}

std::vector<Mesh>& Window::getMeshes() {
	return this->meshes;
}

Shader& Window::getShader() {
	return this->shader;
}

Camera& Window::getCamera() {
	return this->camera;
}

Matrix& Window::getMatrix() {
	return this->matrix;
}

Animation& Window::getAnimations() {
	return this->animations;
}
