#include "game.h"

Game::Game(const char* title, int width, int height, SDL_WindowFlags flags)
	: win{ SDL_CreateWindow(title, width, height, flags) }, ren{ SDL_CreateRenderer(win, nullptr) }
{
	if (!win || !ren) throw "Window or Renderer could not be created";
	loop();
}

void Game::loop()
{
	bool running = true;
	while (running) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT || e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) running = false;
		}

		per_frame();
	}
}

void Game::per_frame()
{
	SDL_SetRenderDrawColor(ren, 20, 20, 20, 255);
	SDL_RenderClear(ren);

	// 2) draw a 100x100 square at (200,150)
	SDL_FRect square{ 200.f, 150.f, 100.f, 100.f };

	// filled square
	SDL_SetRenderDrawColor(ren, 0, 200, 255, 255);
	SDL_RenderFillRect(ren, &square);          // filled, subpixel API

	// (optional) white outline on top
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderRect(ren, &square);              // outline only

	// 3) present
	SDL_RenderPresent(ren);
}



Game::~Game() {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
