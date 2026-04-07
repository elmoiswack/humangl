#include "../includes/glad/glad.h"
#include "../includes/Shader.hpp"
#include "../includes/Matrix.hpp"
#include "../includes/Camera.hpp"
#include "../includes/BodyParts.hpp"
#include "../includes/Mesh.hpp"
#include "../includes/Animation.hpp"
#include "../includes/Window.hpp"

int MAIN_SCREEN_WIDTH = 1900;
int MAIN_SCREEN_HEIGHT = 1080;
int SETTINGS_SCREEN_WIDTH = 700;
int SETTINGS_SCREEN_HEIGHT = 500;

void inputSwitchMainWindow(SDL_Keycode keyEvent, Window& mainWindow, bool& running) {
	switch (keyEvent)
	{
	case SDLK_LEFT:
		mainWindow.getCamera().rotateLeft();
		break ;
	case SDLK_RIGHT:
		mainWindow.getCamera().rotateRight();
		break;
	case SDLK_W:
		if (mainWindow.getShader().getUniform1i("walkingAnimation") != 1) {
			mainWindow.getShader().setUniform1i(1, "walkingAnimation");
			mainWindow.getAnimations().startCycle();
			std::cout << "start animation" << std::endl;
		}
		break;
	case SDLK_ESCAPE:
		running = false;
		break ;
	default:
		break;
	}
}

void checkInput(Window& mainWindow, Window& settingsWindow, bool& running) {
	SDL_Event event;
	const bool* state = SDL_GetKeyboardState(nullptr);

	while (SDL_PollEvent(&event)) {
		if( event.type == SDL_EVENT_QUIT ) {
			std::cout << "SDL_EVENT_QUIT EVENT" << std::endl;
			running = false;
		}
		if (state[SDL_SCANCODE_ESCAPE]) {
			std::cout << "SDL_SCANCODE_ESCAPE EVENT" << std::endl;
			running = false;
		}
		if (event.window.windowID == mainWindow.getWindowId() && event.type == SDL_EVENT_KEY_DOWN) {
			inputSwitchMainWindow(event.key.key, mainWindow, running);
    	}
    }
}

void setModelForAnimation(Animation& animations, Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i) {
	if (shader.getUniform1i("walkingAnimation") == 1)
	{
		std::cout << "do animation" << std::endl;
		animations.walkingAnimation(shader, matrix, body, i);
	}
}

void drawPartsOnScreen(Window& mainWindow, Window& settingsWindow) {
	mainWindow.makeCurrent();
	auto& mainWindowMeshes = mainWindow.getMeshes();
	for (std::size_t i = 0; i < mainWindowMeshes.size(); i++) {
		setModelForAnimation(mainWindow.getAnimations(), mainWindow.getShader(), mainWindow.getMatrix(), mainWindow.getBody(), i);
		mainWindow.drawMeshOnWindow(i);
	}

	settingsWindow.makeCurrent();
	//draw settings on screen
}

int main(void) {
	try
	{
		if (!SDL_Init(SDL_INIT_VIDEO)) {
			std::cout << "SHIIII INIT: " << SDL_GetError() << std::endl;
			return -1;
		}

		SDL_GL_LoadLibrary(NULL);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		Window mainWindow("humanGL", MAIN_SCREEN_WIDTH, MAIN_SCREEN_HEIGHT, "shaders/MainWVertex.glsl", "shaders/MainWFragment.glsl");
		Window settingsWindow("Settings", SETTINGS_SCREEN_WIDTH, SETTINGS_SCREEN_HEIGHT, "shaders/SettingsWVertex.glsl", "shaders/SettingsWFragment.glsl");
		
		std::cout << "MAIN" << std::endl;
		mainWindow.makeCurrent();
		std::cout << "Settings" << std::endl;
		settingsWindow.makeCurrent();
		std::cout << "main" << std::endl;
		mainWindow.makeCurrent();

		bool running = true;

		while (running) {
			mainWindow.clearScreen();
			settingsWindow.clearScreen();

			checkInput(mainWindow, settingsWindow, running);

			mainWindow.computeView();
			drawPartsOnScreen(mainWindow, settingsWindow);

			mainWindow.makeCurrent();
			if ((!SDL_GL_SwapWindow(mainWindow.getWindow()))) {
				std::cout << "SHIIII SDL_GL_SwapWindow: " << SDL_GetError() << std::endl;
				break ;
			};

			settingsWindow.makeCurrent();
			if ((!SDL_GL_SwapWindow(settingsWindow.getWindow()))) {
				std::cout << "SHIIII SDL_GL_SwapWindow: " << SDL_GetError() << std::endl;
				break ;
			};
		}

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	glfwTerminate();
	SDL_Quit();
	return 0;
}