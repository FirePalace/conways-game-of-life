#pragma once
#include <SDL3/SDL.h>
#include "coordinate.h"

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
	void handle_mouse_buttons(const SDL_Event& e);
	void handle_mouse_botton_up(const SDL_Event& e);
	void simulate_generation();
	void draw_cells();
	int get_cell_state(const Cell& c);


	~Game();
};