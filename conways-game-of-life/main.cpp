// g++ sdl3_square.cpp -lSDL3
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int, char**)
{
	if (!SDL_Init(SDL_INIT_VIDEO)) return 1;

	SDL_Window* win = SDL_CreateWindow("SDL3 square", 800, 600, SDL_WINDOW_RESIZABLE); // w,h,flags
	SDL_Renderer* ren = SDL_CreateRenderer(win, nullptr); // let SDL pick a backend
	if (!win || !ren) return 1;

	bool running = true;
	while (running) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) running = false;
		}

		// 1) clear
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

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}