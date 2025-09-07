#pragma once
#include <SDL3/SDL.h>

#include "camera.h"
#include "cell.h"

class Game {
	int win_height;
	int win_width;
	SDL_Window* win;
	SDL_Renderer* ren;
	Camera cam;
	bool dragging = false;
	float drag_last_x = 0, drag_last_y = 0;
public:
	Game(const char* title, int width, int height, SDL_WindowFlags flags);
	void loop();
	void draw_frame() ;

	void draw_grid() const;
	void handle_mouse_input(const SDL_Event& e);
	void handle_mouse_motion(const SDL_Event& e);
	void handle_mouse_wheel(const SDL_Event& e);
	void handle_keyboard_input(const SDL_KeyboardEvent& e);

	static void simulate_generation();
	void draw_cells() const;

	static int get_cell_state(const Cell& c);


	~Game();
};