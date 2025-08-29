#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

class Game {
	SDL_Window* win;
	SDL_Renderer* ren;
public:
	Game(const char* title, int width, int height, SDL_WindowFlags flags);
	void loop();
	void per_frame();
	~Game();
};