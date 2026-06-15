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
	
	this->buttons.emplace_back(Button(ButtonType::UNCLICKABLE, 285, 20, 230, 60, width, height));
	GLTtext* screenName = gltCreateText();
	gltSetText(screenName, "Settings");
	this->buttonLabels.push_back(screenName);

	this->buttons.emplace_back(Button(ButtonType::WORD, 150, 130, 110, 40, width, height));
	GLTtext* bodyText = gltCreateText();
	gltSetText(bodyText, "Body");
	this->buttonLabels.push_back(bodyText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 450, 130, 120, 40, width, height));
	GLTtext* colorText = gltCreateText();
	gltSetText(colorText, "Color");
	this->buttonLabels.push_back(colorText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 150, 240, 110, 40, width, height));
	GLTtext* leftText = gltCreateText();
	gltSetText(leftText, "Left");
	this->buttonLabels.push_back(leftText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 450, 240, 120, 40, width, height));
	GLTtext* rightText = gltCreateText();
	gltSetText(rightText, "Right");
	this->buttonLabels.push_back(rightText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 150, 350, 120, 40, width, height));
	GLTtext* upperText = gltCreateText();
	gltSetText(upperText, "Upper"); 
	this->buttonLabels.push_back(upperText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 450, 350, 120, 40, width, height));
	GLTtext* lowerText = gltCreateText();
	gltSetText(lowerText, "Lower");
	this->buttonLabels.push_back(lowerText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 150, 450, 90, 40, width, height));
	GLTtext* armText = gltCreateText();
	gltSetText(armText, "Arm");
	this->buttonLabels.push_back(armText);

	this->buttons.emplace_back(Button(ButtonType::WORD, 450, 450, 90, 40, width, height));
	GLTtext* legText = gltCreateText();
	gltSetText(legText, "Leg");
	this->buttonLabels.push_back(legText);

	this->buttons.emplace_back(Button(ButtonType::MINUS, 270, 800, 80, 80, width, height));
	GLTtext* minusText = gltCreateText();
	gltSetText(minusText, "-");
	this->buttonLabels.push_back(minusText);

	this->buttons.emplace_back(Button(ButtonType::PLUS, 450, 800, 80, 80, width, height));
	GLTtext* plusText = gltCreateText(); 
	gltSetText(plusText, "+");
	this->buttonLabels.push_back(plusText);
	
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
	this->matrix.computeViewMatrix(this->camera);
	this->shader.setUniformMatrix4x4(this->matrix.getView(), "view");
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