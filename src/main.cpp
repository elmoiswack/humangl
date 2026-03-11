#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include "../includes/glad/glad.h"
#include "../includes/Shader.hpp"
#include "../includes/Matrix.hpp"
#include "../includes/Camera.hpp"
#include "../includes/BodyParts.hpp"

#include <iostream>
#include <vector>

int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;
bool RUNNING = true;

void inputSwitch(SDL_Keycode keyEvent, Camera& cam) {
	switch (keyEvent)
	{
	case SDLK_LEFT:
		cam.rotateLeft();
		break ;
	case SDLK_RIGHT:
		cam.rotateRight();
		break;
	case SDLK_ESCAPE:
		RUNNING = false;
		break ;
	default:
		break;
	}
}

void checkInput(Camera& cam) {
	SDL_Event event;
	const bool* state = SDL_GetKeyboardState(nullptr);

	while (SDL_PollEvent(&event)) {
		if( event.type == SDL_EVENT_QUIT ) {
			std::cout << "SDL_EVENT_QUIT EVENT" << std::endl;
			RUNNING = false;
		}
		if (event.type == SDL_EVENT_KEY_DOWN) {
			inputSwitch(event.key.key, cam);
    	}
		if (state[SDL_SCANCODE_ESCAPE]) {
			std::cout << "SDL_SCANCODE_ESCAPE EVENT" << std::endl;
			RUNNING = false;
		}
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

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	BodyParts body;
	body.computeBody();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, body.getCombinedBody().size() * sizeof(SingleVertex), body.getCombinedBody().data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SingleVertex), (void*)sizeof(SingleVertex));
	glEnableVertexAttribArray(0);
	
	Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
	Camera camera;
	Matrix matrix(SCREEN_WIDTH, SCREEN_HEIGHT, camera);
	float headColor[3] = {0.8f, 0.0f, 0.0f};
	float torsoColor[3] = {1.f, 1.f, 1.f};
	float armLeftColor[3] = {0.0f, 0.4f, 0.0f};
	float armRightColor[3] = {0.0f, 0.4f, 0.0f};
	float legLeftColor[3] = {0.8f, 0.0f, 0.8f};
	float legRightColor[3] = {0.8f, 0.0f, 0.8f};
	
	shader.useProgram();
	shader.setUniformMatrix4x4(matrix.getPerspective(), "perspective");
	shader.setUniformMatrix4x4(matrix.getView(), "view");
	shader.setUniformMatrix4x4(matrix.getModel(), "model");
	shader.setUniformVec3(headColor, "headColor");
	shader.setUniformVec3(torsoColor, "torsoColor");
	shader.setUniformVec3(armLeftColor, "armLeftColor");
	shader.setUniformVec3(armRightColor, "armRightColor");
	shader.setUniformVec3(legLeftColor, "legLeftColor");
	shader.setUniformVec3(legRightColor, "legRightColor");

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

	while (RUNNING) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		checkInput(camera);
		matrix.computeViewMatrix(camera);
		shader.setUniformMatrix4x4(matrix.getView(), "view");

		glBindVertexArray(VAO);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, body.getCombinedBody().size());
		if (!SDL_GL_SwapWindow(window)) {
			std::cout << "SHIIII SDL_GL_SwapWindow: " << SDL_GetError() << std::endl;
		};
	}
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	SDL_GL_DestroyContext(openGLContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}