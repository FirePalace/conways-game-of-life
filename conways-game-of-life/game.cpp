#include "game.h"

Game::Game(const char* title, int width, int height, SDL_WindowFlags flags)
	: win_width{ width }, win_height{ height },
	win{ SDL_CreateWindow(title, width, height, flags) },
	ren{ SDL_CreateRenderer(win, nullptr) }
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

		per_frame();
	}
}

void Game::per_frame()
{
	SDL_SetRenderDrawColor(ren, 20, 20, 20, 255);
	SDL_RenderClear(ren);

	// 2) draw a 100x100 square at (200,150)
	SDL_FRect square{ 200.f, 150.f, 10.f, 10.f };

	// filled square
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderFillRect(ren, &square);          // filled, subpixel API

	SDL_FRect dst_rect{ 0.f, 0.f, 10.f, 10.f };
	SDL_Rect viewport;

	/* Setting a viewport has the effect of limiting the area that rendering
	   can happen, and making coordinate (0, 0) live somewhere else in the
	   window. It does _not_ scale rendering to fit the viewport. */

	   /* as you can see from this, rendering draws over whatever was drawn before it. */
  /* start with a blank canvas. */

	/* Draw once with the whole window as the viewport. */
	viewport.x = 0;
	viewport.y = 0;
	viewport.w = win_width / 2;
	viewport.h = win_width / 2;
	SDL_SetRenderViewport(ren, NULL);  /* NULL means "use the whole window" */


	/* top right quarter of the window. */
	viewport.x = win_width / 2;
	viewport.y = win_height / 2;
	viewport.w = win_width / 2;
	viewport.h = win_height / 2;
	SDL_SetRenderViewport(ren, &viewport);


	/* bottom 20% of the window. Note it clips the width! */
	viewport.x = 0;
	viewport.y = win_height - (win_height / 5);
	viewport.w = win_width / 5;
	viewport.h = win_height / 5;
	//SDL_SetRenderViewport(ren, &viewport);

	/* what happens if you try to draw above the viewport? It should clip! */
	viewport.x = 100;
	viewport.y = 200;
	viewport.w = win_width;
	viewport.h = win_height;
	//SDL_SetRenderViewport(ren, &viewport);
	dst_rect.y = -50;

	// 3) present
	SDL_RenderPresent(ren);
}



Game::~Game() {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
