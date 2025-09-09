
#include "game.h"

int main(int, char**)
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
		return 1;
	}

	Game game("Game of life", 1248, 760, SDL_WINDOW_BORDERLESS);
	return 0;
}