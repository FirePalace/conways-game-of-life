#include "game.h"

Game::Game(const char* title, int width, int height, SDL_WindowFlags flags)
	: win_width{ width }, win_height{ height },
	win{ SDL_CreateWindow(title, width, height, flags) },
	ren{ SDL_CreateRenderer(win, nullptr) },
	viewport{ SDL_Rect(0,0,win_width,win_height) }
{
	if (!win || !ren) throw "Window or Renderer could not be created";
	loop();
}

void Game::loop()
{
	while (true) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT || e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) return;
		}

		draw_frame();
	}
}

void Game::draw_frame()
{
	SDL_SetRenderDrawColor(ren, 20, 20, 20, 255);
	SDL_RenderClear(ren);
	draw_grid();
	// 2) draw a 100x100 square at (200,150)
	SDL_FRect square{ 200.f, 150.f, GRID_SIZE, GRID_SIZE };

	// filled square
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderFillRect(ren, &square);          // filled, subpixel API

	SDL_SetRenderViewport(ren, &viewport);

	// 3) present
	SDL_RenderPresent(ren);
}

void Game::adjust_viewport()
{

}

void Game::draw_grid()
{
	//TODO Stop rendering grid when zoomed out
	SDL_SetRenderDrawColor(ren, 128, 128, 128, 0);
	int x = viewport.x;
	int y = viewport.y;
	while (x <= viewport.x + viewport.w) {
		SDL_RenderLine(ren, x, y, x, y + viewport.h);
		x += GRID_SIZE;
	}
	x = viewport.x;
	y = viewport.y;
	while (y <= viewport.y + viewport.h) {
		SDL_RenderLine(ren, x, y, x + viewport.w, y);
		y += GRID_SIZE;
	}

}



Game::~Game() {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
