// g++ sdl3_square.cpp -lSDL3
#include "game.h"

int main(int, char**)
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
		return 1;
	}

	Game game("Game of life", 800, 600, SDL_WINDOW_RESIZABLE);
	return 0;
}