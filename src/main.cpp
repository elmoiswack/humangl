#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include "../includes/glad/glad.h"
#include "../includes/Shader.hpp"
#include <iostream>

int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;

void checkInput(SDL_Window* window, SDL_GLContext& openGLContext) {
	SDL_Event event;
	const bool* state = SDL_GetKeyboardState(nullptr);

	while (SDL_PollEvent(&event)) {
		if( event.type == SDL_EVENT_QUIT ) {
			std::cout << "SDL_EVENT_QUIT EVENT" << std::endl;
			SDL_GL_DestroyContext(openGLContext);
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(0);
		}
		if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
			std::cout << "ESCAPE EVENT" << std::endl;
			SDL_GL_DestroyContext(openGLContext);
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(0);
    	}
		if (state[SDL_SCANCODE_ESCAPE]) {
			std::cout << "SDL_SCANCODE_ESCAPE EVENT" << std::endl;
			SDL_GL_DestroyContext(openGLContext);
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(0);			
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

	SDL_GL_SetSwapInterval(1);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

	Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
	shader.useProgram();

	while (true) {
		checkInput(window, openGLContext);

		glBindVertexArray(VAO);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		SDL_GL_SwapWindow(window);
	}
	
	SDL_GL_DestroyContext(openGLContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}