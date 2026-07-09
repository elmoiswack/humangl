#include "../includes/Window.hpp"

int MAIN_SCREEN_WIDTH = 1900;
int MAIN_SCREEN_HEIGHT = 1080;
int SETTINGS_SCREEN_WIDTH = 800;
int SETTINGS_SCREEN_HEIGHT = 950;

void inputSwitchMainWindow(SDL_Keycode keyEvent, Window& mainWindow, bool& running, float deltaTime) {
	bool recomputeView = false;
	
	switch (keyEvent)
	{
	case SDLK_LEFT:
		mainWindow.rotateLeft(deltaTime);
		recomputeView = true;
		break ;
	case SDLK_RIGHT:
		mainWindow.rotateRight(deltaTime);
		recomputeView = true;
		break;
	case SDLK_W:
		if (mainWindow.getAnimations().isAnimationFinished() == true) {
			if (!mainWindow.makeCurrent())
				return ;
			mainWindow.getShader().setUniform1i(AnimationTypes::WALKING, "animation");
			mainWindow.getAnimations().startAnimation(AnimationTypes::WALKING);
		}
		break;
	case SDLK_SPACE:
		if (mainWindow.getAnimations().isAnimationFinished() == true) {
			if (!mainWindow.makeCurrent())
				return ;
			mainWindow.getShader().setUniform1i(AnimationTypes::JUMP, "animation");
			mainWindow.getAnimations().startAnimation(AnimationTypes::JUMP);
		}
		break;
	case SDLK_ESCAPE:
		running = false;
		break ;
	default:
		break;
	}

	if (recomputeView)
		mainWindow.computeView();
}

void checkInput(Window& mainWindow, Window& settingsWindow, BodyParts& body, bool& running, float deltaTime) {
	SDL_Event event;
	const bool* state = SDL_GetKeyboardState(nullptr);
	auto& buttons = settingsWindow.getButtons();

	while (SDL_PollEvent(&event)) {
		if(event.type == SDL_EVENT_QUIT) {
			std::cout << "SDL_EVENT_QUIT EVENT" << std::endl;
			running = false;
			return ;
		}
		if (state[SDL_SCANCODE_ESCAPE]) {
			std::cout << "SDL_SCANCODE_ESCAPE EVENT" << std::endl;
			running = false;
			return ;
		}
		if (event.window.windowID == mainWindow.getWindowId() && event.type == SDL_EVENT_KEY_DOWN) {
			inputSwitchMainWindow(event.key.key, mainWindow, running, deltaTime);
    	}
		if (event.window.windowID == settingsWindow.getWindowId() && event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
			if (settingsWindow.checkIfButtonPressed(event.motion.x, event.motion.y, body, mainWindow.getMeshes())) {	
				if (!mainWindow.makeCurrent())
					return ;
				mainWindow.updateMeshBody(body);
			}
		}
    }
}

void drawPartsOnScreen(Window& mainWindow, Window& settingsWindow, BodyParts& body) {
	if (!mainWindow.makeCurrent())
		return ;
	auto& mainWindowMeshes = mainWindow.getMeshes();
	auto& mainWindowAnimations = mainWindow.getAnimations();
	for (std::size_t i = 0; i < mainWindowMeshes.size(); i++) {
		mainWindowAnimations.checkAnimation(mainWindow.getShader(), mainWindow.getMatrix(), body, i);
		mainWindow.drawMeshOnWindow(mainWindowMeshes[i]);
	}

	if (!settingsWindow.makeCurrent())
		return ;
	auto& buttons = settingsWindow.getButtons();
	auto& labels = settingsWindow.getButtonsLabels();
	for (std::size_t i = 0; i < buttons.size(); i++) {
		if (buttons[ButtonOrder::COLOR].getActive() == true && i == ButtonOrder::WIDTH) {
			i = ButtonOrder::DEPTH;
			continue;
		} else if (buttons[ButtonOrder::BODY].getActive() == true && i == ButtonOrder::RED) {
			i = ButtonOrder::BLUE;
			continue;			
		} else if (buttons[ButtonOrder::BODY].getActive() == false && buttons[ButtonOrder::COLOR].getActive() == false && i == ButtonOrder::WIDTH) {
			i = ButtonOrder::BLUE;
			continue;			
		}
		settingsWindow.drawMeshOnWindow(buttons[i].getMesh());
		settingsWindow.drawText(buttons[i], labels[i]);
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
		float lastFrame = SDL_GetTicks();
		while (running) {
			float currentFrame = SDL_GetTicks();
			float deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			mainWindow.clearScreen();
			settingsWindow.clearScreen();

			checkInput(mainWindow, settingsWindow, body, running, deltaTime);

			drawPartsOnScreen(mainWindow, settingsWindow, body);

			if (mainWindow.makeCurrent()) {
				if ((!SDL_GL_SwapWindow(mainWindow.getWindow()))) {
					std::cout << "SHIIII SDL_GL_SwapWindow: " << SDL_GetError() << std::endl;
					break ;
				}
			}

			if (settingsWindow.makeCurrent()) {
				if ((!SDL_GL_SwapWindow(settingsWindow.getWindow()))) {
					std::cout << "SHIIII SDL_GL_SwapWindow: " << SDL_GetError() << std::endl;
					break ;
				}
			}
		}
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}

	SDL_Quit();
	return 0;
}