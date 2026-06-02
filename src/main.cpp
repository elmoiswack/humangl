#include "../includes/Window.hpp"

int MAIN_SCREEN_WIDTH = 1900;
int MAIN_SCREEN_HEIGHT = 1080;
int SETTINGS_SCREEN_WIDTH = 800;
int SETTINGS_SCREEN_HEIGHT = 950;

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
		if (mainWindow.getAnimations().isAnimationFinished() == true) {
			mainWindow.makeCurrent();
			mainWindow.getShader().setUniform1i(1, "walkingAnimation");
			mainWindow.getAnimations().startAnimation(AnimationTypes::WALKING);
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
		if(event.type == SDL_EVENT_QUIT) {
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
	if (animations.getCurrentAnimation() == AnimationTypes::WALKING)
	{
		animations.walkingAnimation(shader, matrix, body, i);
	}
}

void drawPartsOnScreen(Window& mainWindow, Window& settingsWindow, BodyParts& body) {
	mainWindow.makeCurrent();
	auto mainWindowMeshesSize = mainWindow.getMeshes().size();
	for (std::size_t i = 0; i < mainWindowMeshesSize; i++) {
		setModelForAnimation(mainWindow.getAnimations(), mainWindow.getShader(), mainWindow.getMatrix(), body, i);
		mainWindow.drawMeshOnWindow(i, true);
	}

	settingsWindow.makeCurrent();
	settingsWindow.drawSettingsText();
	auto settingsWindowMeshesSize = settingsWindow.getMeshes().size();
	for (std::size_t i = 0; i < settingsWindowMeshesSize; i++) {
		settingsWindow.drawMeshOnWindow(i, false);
	}
}

int main(void) {
	try {
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

		BodyParts body;
		Window mainWindow("HumanGL", MAIN_SCREEN_WIDTH, MAIN_SCREEN_HEIGHT, "shaders/MainWVertex.glsl", "shaders/MainWFragment.glsl", body);
		Window settingsWindow("Settings", SETTINGS_SCREEN_WIDTH, SETTINGS_SCREEN_HEIGHT, "shaders/SettingsWVertex.glsl", "shaders/SettingsWFragment.glsl");

		bool running = true;

		while (running) {
			mainWindow.clearScreen();
			settingsWindow.clearScreen();

			checkInput(mainWindow, settingsWindow, running);

			mainWindow.computeView();
			drawPartsOnScreen(mainWindow, settingsWindow, body);

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
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}

	SDL_Quit();
	return 0;
}