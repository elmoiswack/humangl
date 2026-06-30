#include "../includes/Window.hpp"

Window::Window(const char* name, int width, int height, const char* pathVertexShader, const char* pathFragmentShader, BodyParts& body) :
	camera(),
	matrix(width, height),
	animations()
{
	this->initWindow(name, width, height);
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
	auto bodyParts = body.getBody();
	for (size_t i = 0; i < bodyParts.size(); ++i) {
		this->meshes.emplace_back(Mesh(bodyParts[i], colors[i].data()));
	}

	this->shader = Shader(pathVertexShader, pathFragmentShader);
	this->shader.useProgram();
	this->shader.setUniformMatrix4x4(this->matrix.getPerspective(), "perspective");
	this->shader.setUniformMatrix4x4(this->matrix.getModel(), "model");
	this->computeView();
}

Window::Window(const char* name, int width, int height, const char* pathVertexShader, const char* pathFragmentShader) :
	camera(),
	matrix(width, height),
	animations()
{
	this->initWindow(name, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	if (!gltInit()) {
		fprintf(stderr, "Failed to initialize glText\n");
		SDL_GL_DestroyContext(this->openGLContext);
		SDL_DestroyWindow(this->window);
		throw FailedWindowCreation();
	}
	this->initButtons(width, height);
	
	this->meshes = {};
	this->shader = Shader(pathVertexShader, pathFragmentShader);
}

Window::~Window()
{
	SDL_GL_DestroyContext(this->openGLContext);
	SDL_DestroyWindow(this->window);
	for (auto& mesh: this->meshes) {
		mesh.deleteMesh();
	}
	for (auto& buttonLabel: this->buttonLabels) {
		gltDeleteText(buttonLabel);
	}
	gltTerminate();
}

void Window::initWindow(const char* name, int width, int height) {
	SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 0);

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

	static bool gladInitialized = false;
	if (!gladInitialized) {
		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
			std::cout << "SHIIII GLAD" << std::endl;
			SDL_GL_DestroyContext(this->openGLContext);
			SDL_DestroyWindow(this->window);
			throw FailedWindowCreation();
		}
		gladInitialized = true;
	}
	
	if (!SDL_GL_MakeCurrent(this->window, this->openGLContext)) {
		std::cout << "Failed to make current: " << SDL_GetError() << std::endl;
		SDL_GL_DestroyContext(this->openGLContext);
		SDL_DestroyWindow(this->window);
		throw FailedWindowCreation();
	}

	this->heigth = height;
	this->width = width;

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glViewport(0, 0, width, height);
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

void Window::drawMeshOnWindow(Mesh& mesh) {
	this->makeCurrent();
	this->shader.setUniformVec3(mesh.getColor(), "color");

	glBindVertexArray(mesh.getVAO());
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, mesh.getVertexCount());
	glBindVertexArray(0);
}

void Window::clearScreen() {
	this->makeCurrent();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::computeView() {
	this->makeCurrent();
	this->matrix.computeViewMatrix(this->camera.getX(), this->camera.getY(), this->camera.getZ(), this->camera.getAngle());
	this->shader.setUniformMatrix4x4(this->matrix.getView(), "view");
}

void Window::rotateRight(float deltaTime) {
	deltaTime = 0.0f;
	float updatedAngle = this->camera.getAngle() + 0.05f;
	this->camera.setAngle(updatedAngle);
}

void Window::rotateLeft(float deltaTime) {
	deltaTime = 0.0f;
	float updatedAngle = this->camera.getAngle() - 0.05f;
	this->camera.setAngle(updatedAngle);
}

void Window::rotateUp(float deltaTime) {

}

void Window::rotateDown(float deltaTime) {

}

std::vector<Mesh>& Window::getMeshes() {
	return this->meshes;
}

std::vector<Button>& Window::getButtons() {
	return this->buttons;
}

std::vector<GLTtext*>& Window::getButtonsLabels() {
	return this->buttonLabels;
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

void Window::drawText(Button& button, GLTtext* text) {
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	auto type = button.getType();

	float font = 3.0;
	if (type == ButtonType::WORD) {
		font = 2.5;
	} else if (type != ButtonType::WORD && type != ButtonType::UNCLICKABLE) {
		font = 6.0;
	}

	gltBeginDraw();
	if (type != ButtonType::WORD)
		gltColor(1.0f, 1.0f, 1.0f, 1.0f);
	else if (button.getActive() == true)
		gltColor(1.0f, 1.0f, 1.0f, 1.0f);
	else
		gltColor(0.7f, 0.7f, 0.7f, 1.0f);
	
	gltDrawText2D(
		text,
		(GLfloat)button.getX(),
		(GLfloat)button.getY(),
		font
	);
	gltEndDraw();

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}
