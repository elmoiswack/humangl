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
	this->meshes = {};
	auto bodyParts = body.getBody();
	for (size_t i = 0; i < bodyParts.size(); ++i) {
		this->meshes.emplace_back(Mesh(bodyParts[i], colors[i].data()));
	}

	this->shader = Shader(pathVertexShader, pathFragmentShader);
	this->initShader(pathVertexShader, pathFragmentShader);
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
 	// create all buttons here
	// Button plus(ButtonType::PLUS, "+");
	Button minus(ButtonType::MINUS, "-");
	this->meshes = {};
	// this->meshes.emplace_back(Mesh(plus.getVertices()));
	this->meshes.emplace_back(Mesh(minus.getVertices()));
	this->initShader(pathVertexShader, pathFragmentShader);
}

Window::~Window()
{
	SDL_GL_DestroyContext(this->openGLContext);
	SDL_DestroyWindow(this->window);
	for (auto& mesh: this->meshes) {
		mesh.deleteMesh();
	}
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

void Window::initShader(const char* pathVertexShader, const char* pathFragmentShader) {
	this->shader = Shader(pathVertexShader, pathFragmentShader);
	this->shader.useProgram();
	this->shader.setUniformMatrix4x4(this->matrix.getPerspective(), "perspective");
	this->shader.setUniformMatrix4x4(this->matrix.getModel(), "model");
	this->computeView();
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

void Window::drawMeshOnWindow(std::size_t index, bool isColorAvailable) {
	this->makeCurrent();
	if (isColorAvailable)
		this->shader.setUniformVec3(this->meshes[index].getColor(), "color");
	else {
		float color[] = {.4f, .4f, .4f};
		this->shader.setUniformVec3(color, "color");
	}

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
	this->makeCurrent();
	this->matrix.computeViewMatrix(this->camera);
	this->shader.setUniformMatrix4x4(this->matrix.getView(), "view");
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

void Window::drawSettingsText() {
	float heightOffset = 10.f;
	float optionHeightOffset = 70.f;
	gltBeginDraw();
	gltColor(1.0f, 1.0f, 1.0f, 1.0f);

///////////////////////HEADER////////////////////////////////
// 	gltDrawText2DAligned(this->settingsTexts.name,
// 		(GLfloat)(this->width / 2),
// 		(GLfloat)(heightOffset),
// 		3.5f,
// 		GLT_CENTER, GLT_TOP
// 	);

// ///////////////////////BODY////////////////////////////////
// 	gltDrawText2DAligned(this->settingsTexts.body,
// 		(GLfloat)(this->width / 16),
// 		(GLfloat)(this->heigth / 16 + heightOffset),
// 		3.f,
// 		GLT_LEFT, GLT_TOP
// 	);

// 	gltDrawText2DAligned(this->settingsTexts.head,
// 		(GLfloat)(this->width / 16),
// 		(GLfloat)(this->heigth / 8 + heightOffset),
// 		2.f,
// 		GLT_LEFT, GLT_TOP
// 	);

// 	gltDrawText2DAligned(this->settingsTexts.torso,
// 		(GLfloat)(this->width / 16),
// 		(GLfloat)(this->heigth / 8 + heightOffset + optionHeightOffset),
// 		2.f,
// 		GLT_LEFT, GLT_TOP
// 	);

// 	gltDrawText2DAligned(this->settingsTexts.right,
// 		(GLfloat)(this->width / 16),
// 		(GLfloat)(this->heigth / 8 + heightOffset + (optionHeightOffset * 2)),
// 		2.5f,
// 		GLT_LEFT, GLT_TOP
// 	);

// 	gltDrawText2DAligned(this->settingsTexts.left,
// 		(GLfloat)(this->width / 16),
// 		(GLfloat)(this->heigth / 8 + heightOffset + (optionHeightOffset * 6.5)),
// 		2.5f,
// 		GLT_LEFT, GLT_TOP
// 	);
	
// 	gltDrawText2DAligned(this->settingsTexts.upper,
// 		(GLfloat)(this->width / 16),
// 		(GLfloat)(this->heigth / 8 + heightOffset + (optionHeightOffset * 7)),
// 		2.f,
// 		GLT_LEFT, GLT_TOP
// 	);

// 	gltDrawText2DAligned(this->settingsTexts.lower,
// 		(GLfloat)(this->width / 16),
// 		(GLfloat)(this->heigth / 8 + heightOffset + (optionHeightOffset * 8)),
// 		2.f,
// 		GLT_LEFT, GLT_TOP
// 	);
	
// 	gltDrawText2DAligned(this->settingsTexts.arm,
// 		(GLfloat)(this->width / 16),
// 		(GLfloat)(this->heigth / 8 + heightOffset + (optionHeightOffset * 9)),
// 		2.f,
// 		GLT_LEFT, GLT_TOP
// 	);

// 	gltDrawText2DAligned(this->settingsTexts.leg,
// 		(GLfloat)(this->width / 16),
// 		(GLfloat)(this->heigth / 8 + heightOffset + (optionHeightOffset * 10)),
// 		2.f,
// 		GLT_LEFT, GLT_TOP
// 	);

///////////////////////COLOR////////////////////////////////
// 	gltDrawText2DAligned(this->settingsTexts.color,
// 		(GLfloat)((this->width / 16) * 15),
// 		(GLfloat)(this->heigth / 16 + heightOffset),
// 		3.f,
// 		GLT_RIGHT, GLT_TOP
// 	);

// 	gltDrawText2DAligned(this->settingsTexts.head,
// 		(GLfloat)((this->width / 16) * 15),
// 		(GLfloat)(this->heigth / 8 + heightOffset),
// 		2.f,
// 		GLT_RIGHT, GLT_TOP
// 	);

// 	gltDrawText2DAligned(this->settingsTexts.torso,
// 		(GLfloat)((this->width / 16) * 15),
// 		(GLfloat)(this->heigth / 8 + heightOffset + optionHeightOffset),
// 		2.f,
// 		GLT_RIGHT, GLT_TOP
// 	);

// 	gltDrawText2DAligned(this->settingsTexts.right,
// 		(GLfloat)((this->width / 16) * 15),
// 		(GLfloat)(this->heigth / 8 + heightOffset + (optionHeightOffset * 2)),
// 		2.5f,
// 		GLT_RIGHT, GLT_TOP
// 	);

// 	gltDrawText2DAligned(this->settingsTexts.upperArm,
// 		(GLfloat)((this->width / 16) * 15),
// 		(GLfloat)(this->heigth / 8 + heightOffset + (optionHeightOffset * 2.5)),
// 		2.f,
// 		GLT_RIGHT, GLT_TOP
// 	);

// 	gltDrawText2DAligned(this->settingsTexts.lowerArm,
// 		(GLfloat)((this->width / 16) * 15),
// 		(GLfloat)(this->heigth / 8 + heightOffset + (optionHeightOffset * 3.5)),
// 		2.f,
// 		GLT_RIGHT, GLT_TOP
// 	);
	
// 	gltDrawText2DAligned(this->settingsTexts.upperLeg,
// 		(GLfloat)((this->width / 16) * 15),
// 		(GLfloat)(this->heigth / 8 + heightOffset + (optionHeightOffset * 4.5)),
// 		2.f,
// 		GLT_RIGHT, GLT_TOP
// 	);

// 	gltDrawText2DAligned(this->settingsTexts.lowerLeg,
// 		(GLfloat)((this->width / 16) * 15),
// 		(GLfloat)(this->heigth / 8 + heightOffset + (optionHeightOffset * 5.5)),
// 		2.f,
// 		GLT_RIGHT, GLT_TOP
// 	);

// 	gltDrawText2DAligned(this->settingsTexts.left,
// 		(GLfloat)((this->width / 16) * 15),
// 		(GLfloat)(this->heigth / 8 + heightOffset + (optionHeightOffset * 6.5)),
// 		2.5f,
// 		GLT_RIGHT, GLT_TOP
// 	);
	
// 	gltDrawText2DAligned(this->settingsTexts.upperArm,
// 		(GLfloat)((this->width / 16) * 15),
// 		(GLfloat)(this->heigth / 8 + heightOffset + (optionHeightOffset * 7)),
// 		2.f,
// 		GLT_RIGHT, GLT_TOP
// 	);

// 	gltDrawText2DAligned(this->settingsTexts.lowerArm,
// 		(GLfloat)((this->width / 16) * 15),
// 		(GLfloat)(this->heigth / 8 + heightOffset + (optionHeightOffset * 8)),
// 		2.f,
// 		GLT_RIGHT, GLT_TOP
// 	);
	
// 	gltDrawText2DAligned(this->settingsTexts.upperLeg,
// 		(GLfloat)((this->width / 16) * 15),
// 		(GLfloat)(this->heigth / 8 + heightOffset + (optionHeightOffset * 9)),
// 		2.f,
// 		GLT_RIGHT, GLT_TOP
// 	);

// 	gltDrawText2DAligned(this->settingsTexts.lowerLeg,
// 		(GLfloat)((this->width / 16) * 15),
// 		(GLfloat)(this->heigth / 8 + heightOffset + (optionHeightOffset * 10)),
// 		2.f,
// 		GLT_RIGHT, GLT_TOP
// 	);

	gltEndDraw();	
}
