#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

#include "../includes/glad/glad.h"
#include "../includes/Shader.hpp"
#include "../includes/Matrix.hpp"
#include "../includes/Camera.hpp"
#include "../includes/BodyParts.hpp"
#include "../includes/Mesh.hpp"
#include "../includes/Animation.hpp"

#include <iostream>
#include <vector>
#include <array>

int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;

void inputSwitch(SDL_Keycode keyEvent, Camera& cam, bool& running) {
	switch (keyEvent)
	{
	case SDLK_LEFT:
		cam.rotateLeft();
		break ;
	case SDLK_RIGHT:
		cam.rotateRight();
		break;
	case SDLK_ESCAPE:
		running = false;
		break ;
	default:
		break;
	}
}

void checkInput(Camera& cam, bool& running) {
	SDL_Event event;
	const bool* state = SDL_GetKeyboardState(nullptr);

	while (SDL_PollEvent(&event)) {
		if( event.type == SDL_EVENT_QUIT ) {
			std::cout << "SDL_EVENT_QUIT EVENT" << std::endl;
			running = false;
		}
		if (event.type == SDL_EVENT_KEY_DOWN) {
			inputSwitch(event.key.key, cam, running);
    	}
		if (state[SDL_SCANCODE_ESCAPE]) {
			std::cout << "SDL_SCANCODE_ESCAPE EVENT" << std::endl;
			running = false;
		}
    }
}

void setModelForAnimation(Animation& animations, Shader& shader, Matrix& matrix, std::size_t i) {
	animations.walkingAnimation(shader, matrix, i);
}

void drawPartsOnScreen(std::vector<Mesh>& meshes, Shader& shader, Matrix& matrix, Animation& animations) {
	for (std::size_t i = 0; i < meshes.size(); i++) {
		setModelForAnimation(animations, shader, matrix, i);
		shader.setUniformVec3(meshes[i].getColor(), "color");
		glBindVertexArray(meshes[i].getVAO());
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, meshes[i].getVertexCount());
		glBindVertexArray(0);
	}
}

int main(void) {
	
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

	SDL_Window* window = SDL_CreateWindow("HumanGL", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		std::cout << "SHIIII WINDOW: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return -1;		
	}

	SDL_GLContext openGLContext = SDL_GL_CreateContext(window);
	if (openGLContext == nullptr) {
		std::cout << "SHIIII openGLContext: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(0);			
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cout << "SHIIII GLAD" << std::endl;
		SDL_GL_DestroyContext(openGLContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(0);
	}
	SDL_GL_MakeCurrent(window, openGLContext);
	SDL_GL_SetSwapInterval(1);

	BodyParts body;
	std::vector<Mesh> meshes;
	std::vector<std::array<float, 3>> colors = {
		{0.8f, 0.0f, 0.0f}, 
		{1.f, 1.f, 1.f}, 
		{0.0f, 0.4f, 0.0f},
		{0.0f, 0.4f, 0.0f}, 
		{0.8f, 0.0f, 0.8f}, 
		{0.8f, 0.0f, 0.8f}  
	};
	auto bodyParts = body.getBody();
	for (size_t i = 0; i < bodyParts.size(); ++i) {
		meshes.emplace_back(Mesh(bodyParts[i], colors[i].data()));
	}

	Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
	Camera camera;
	Matrix matrix(SCREEN_WIDTH, SCREEN_HEIGHT, camera);
	Animation animations;

	shader.useProgram();
	shader.setUniformMatrix4x4(matrix.getPerspective(), "perspective");
	shader.setUniformMatrix4x4(matrix.getView(), "view");
	shader.setUniformMatrix4x4(matrix.getModel(), "model");

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

	bool running = true;

	while (running) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		checkInput(camera, running);
		matrix.computeViewMatrix(camera);
		shader.setUniformMatrix4x4(matrix.getView(), "view");
		
		drawPartsOnScreen(meshes, shader, matrix, animations);

		if (!SDL_GL_SwapWindow(window)) {
			std::cout << "SHIIII SDL_GL_SwapWindow: " << SDL_GetError() << std::endl;
			break ;
		};
	}
	
	for (auto& mesh: meshes) {
		mesh.deleteMesh();
	}
	SDL_GL_DestroyContext(openGLContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}