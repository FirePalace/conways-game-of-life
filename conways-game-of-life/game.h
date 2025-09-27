#pragma once
#include <optional>
#include <SDL3/SDL.h>

#include "camera.h"
#include "cell.h"
#include "patterns/pattern.h"

class Game {
	int win_height;
	int win_width;
	SDL_Window* win;
	SDL_Renderer* ren;
	Camera cam;
	bool dragging = false;
	float drag_last_x = 0, drag_last_y = 0;
	bool shutdown_requested = false;
	std::optional<Pattern> selected_pattern;

public:
	Game(const char* title, int width, int height, SDL_WindowFlags flags);
	void loop();
	static void one_loop_iteration(void* userData);
	void draw_frame() ;

	void draw_grid() const;
	void handle_mouse_input(const SDL_Event& e);
	void handle_mouse_motion(const SDL_Event& e);
	void handle_mouse_wheel(const SDL_Event& e);
	void handle_keyboard_input(const SDL_KeyboardEvent& e);
	void place_cell(const Cell& m);
	void handle_window_event(const SDL_Event& e);


	void select_pattern(int p_number);
	void draw_selected_pattern();
	void place_selected_pattern(int x, int y);
	void deselect_pattern();


	static void simulate_generation();
	void draw_cells() const;
	bool is_point_in_viewport(int x_point, int y_point) const;
	static int get_cell_state(const Cell& c);


	~Game();
};