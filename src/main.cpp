#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <iostream>

int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;

void checkInput(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_Event event;
	const bool* state = SDL_GetKeyboardState(nullptr);

	while (SDL_PollEvent(&event)) {
		if( event.type == SDL_EVENT_QUIT ) {
			std::cout << "SDL_EVENT_QUIT EVENT" << std::endl;
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(0);
		}
		if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
			std::cout << "ESCAPE EVENT" << std::endl;
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(0);
    	}
		if (state[SDL_SCANCODE_ESCAPE]) {
			std::cout << "SDL_SCANCODE_ESCAPE EVENT" << std::endl;
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(0);			
		}
    }
}

void render(SDL_Renderer* renderer) {

	if (!SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255))
		std::cout << "Failed to set color: " << SDL_GetError() << std::endl;

	if (!SDL_RenderLine(renderer, 20.0f, 20.0f, 500.0f, 500.0f))
		std::cout << "Failed to draw line: " << SDL_GetError() << std::endl;
	
	if (!SDL_RenderPresent(renderer))
		std::cout << "Failed to render: " << SDL_GetError() << std::endl;
}

int main(void) {
	
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "SHIIII INIT: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow("HumanGL", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		std::cout << "SHIIII WINDOW: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return -1;		
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
	if (renderer == nullptr) {
		std::cout << "SHIIII renderer: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;			
	}

	while (true) {
		render(renderer);
		checkInput(window, renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}