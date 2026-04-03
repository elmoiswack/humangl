#include "../includes/glad/glad.h"
#include "../includes/Shader.hpp"
#include "../includes/Matrix.hpp"
#include "../includes/Camera.hpp"
#include "../includes/BodyParts.hpp"
#include "../includes/Mesh.hpp"
#include "../includes/Animation.hpp"
#include "../includes/Window.hpp"

#include <iostream>
#include <vector>
#include <array>

int MAIN_SCREEN_WIDTH = 1900;
int MAIN_SCREEN_HEIGHT = 1080;
int SETTINGS_SCREEN_WIDTH = 700;
int SETTINGS_SCREEN_HEIGHT = 500;

void inputSwitchMainWindow(SDL_Keycode keyEvent, Animation& animations, Shader& shader, Camera& cam, bool& running) {
	switch (keyEvent)
	{
	case SDLK_LEFT:
		cam.rotateLeft();
		break ;
	case SDLK_RIGHT:
		cam.rotateRight();
		break;
	case SDLK_W:
		shader.setUniform1i(1, "walkingAnimation");
		animations.startCycle();
		break;
	case SDLK_ESCAPE:
		running = false;
		break ;
	default:
		break;
	}
}

void checkInput(Window& mainWindow, Window& settingsWindow, Animation& animations, Shader& shader, Matrix& matrix, Camera& cam, bool& running) {
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
			inputSwitchMainWindow(event.key.key, animations, shader, cam, running);
    	}
    }
}

void setModelForAnimation(Animation& animations, Shader& shader, Matrix& matrix, BodyParts& body, std::size_t i) {
	if (shader.getUniform1i("walkingAnimation") == 1)
		animations.walkingAnimation(shader, matrix, body, i);
}

void drawPartsOnScreen(Window& mainWindow, Window& settingsWindow, std::vector<Mesh>& meshes, Shader& shader, Matrix& matrix, BodyParts& body, Animation& animations) {
	for (std::size_t i = 0; i < meshes.size(); i++) {
		setModelForAnimation(animations, shader, matrix, body, i);
		mainWindow.drawMeshOnWindow(meshes[i], shader);
	}
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

		Window mainWindow("humanGL", MAIN_SCREEN_WIDTH, MAIN_SCREEN_HEIGHT);
		Window settingsWindow("Settings", SETTINGS_SCREEN_WIDTH, SETTINGS_SCREEN_HEIGHT);
		
		mainWindow.makeCurrent();

		BodyParts body;
		std::vector<Mesh> meshes;
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
			meshes.emplace_back(Mesh(bodyParts[i], colors[i].data()));
		}

		Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
		Camera camera;
		Matrix matrix(MAIN_SCREEN_WIDTH, MAIN_SCREEN_HEIGHT, camera);
		Animation animations;

		shader.useProgram();
		shader.setUniformMatrix4x4(matrix.getPerspective(), "perspective");
		shader.setUniformMatrix4x4(matrix.getView(), "view");
		shader.setUniformMatrix4x4(matrix.getModel(), "model");

		bool running = true;

		while (running) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			checkInput(mainWindow, settingsWindow, animations, shader, matrix, camera, running);
			matrix.computeViewMatrix(camera);
			shader.setUniformMatrix4x4(matrix.getView(), "view");
			
			drawPartsOnScreen(mainWindow, settingsWindow, meshes, shader, matrix, body, animations);

			if ((!SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow()))) {
				std::cout << "SHIIII SDL_GL_SwapWindow: " << SDL_GetError() << std::endl;
				break ;
			};
		}
		
		for (auto& mesh: meshes) {
			mesh.deleteMesh();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	SDL_Quit();
	return 0;
}