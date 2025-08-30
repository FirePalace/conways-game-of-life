#pragma once
#include <SDL3/SDL.h>

class Game {
	int win_height;
	int win_width;
	SDL_Window* win;
	SDL_Renderer* ren;
public:
	Game(const char* title, int width, int height, SDL_WindowFlags flags);
	void loop();
	void per_frame();
	~Game();
};