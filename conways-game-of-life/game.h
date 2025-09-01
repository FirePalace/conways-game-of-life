#pragma once
#include <SDL3/SDL.h>
#include "cell.h"
#include <vector>
#include <memory>
//inline static std::unique_ptr<std::vector<Cell>> active_cells = std::make_unique< std::vector<Cell>>();
class Game {
	int win_height;
	int win_width;
	SDL_Window* win;
	SDL_Renderer* ren;
	SDL_Rect viewport;
public:
	Game(const char* title, int width, int height, SDL_WindowFlags flags);
	void loop();
	void draw_frame();
	void adjust_viewport();
	void draw_grid();

	~Game();
};