#include "game.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/bind.h>
#endif
#include <algorithm>
#include <iostream>
#include <cmath>
#include <filesystem>


Game::Game(const char *title, int width, int height, SDL_WindowFlags flags)
	: win_height{height}, win_width{width} {
	g_game = this;
	win = SDL_CreateWindow(title, width, height, flags);
	if (!win) {
		SDL_Log("Window creation failed: %s", SDL_GetError());
		std::cout << "Window creation failed\n";
		return;
	}

	ren = SDL_CreateRenderer(win, nullptr);
	if (!ren) {
		SDL_Log("Renderer creation failed: %s", SDL_GetError());
		std::cout << "Renderer creation failed\n";
		return;
	}
#ifndef __EMSCRIPTEN__
	std::filesystem::path newDir = R"(..\..\conways-game-of-life\patterns\rle)";
	std::filesystem::current_path(newDir);
#endif
	loop();
}

void Game::loop() {
#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg(one_loop_iteration, this, 0, true);
#else
	while (!shutdown_requested) {
		one_loop_iteration(this);
	}
#endif
}

void Game::one_loop_iteration(void *userData) {
	Game *game = static_cast<Game *>(userData);
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT || e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
			game->shutdown_requested = true;
#ifdef __EMSCRIPTEN__
			emscripten_cancel_main_loop();
#endif
			return;
		}

		if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN || e.type == SDL_EVENT_MOUSE_BUTTON_UP)
			game->handle_mouse_input(e);
		else if (e.type == SDL_EVENT_KEY_DOWN || e.type == SDL_EVENT_KEY_UP)
			game->handle_keyboard_input(e.key);
		else if (e.type == SDL_EVENT_MOUSE_MOTION)
			game->handle_mouse_motion(e);
		else if (e.type == SDL_EVENT_MOUSE_WHEEL)
			game->handle_mouse_wheel(e);
		else if (e.type == SDL_EVENT_WINDOW_RESIZED)
			game->handle_window_event(e);
	}
	game->handle_simulation_speed();
	game->draw_frame();
}

void Game::handle_simulation_speed() const {
	auto now = std::chrono::steady_clock::now();
	std::chrono::duration<double> delta = now - last_simulation;
	switch (simulation_speed) {
		case 1:
			if (delta >= std::chrono::seconds(1)) {
				simulate_generation();
			}
			break;
		case 2:
			if (delta >= std::chrono::milliseconds(500)) {
				simulate_generation();
			}
			break;
		case 3:
			if (delta >= std::chrono::milliseconds(250)) {
				simulate_generation();
			}
		default:
			return;
	}
}

void Game::draw_frame() {
	SDL_SetRenderDrawColor(ren, 20, 20, 20, 255);
	SDL_RenderClear(ren);

	draw_grid();
	if (selected_pattern) {
		draw_selected_pattern();
	}
	draw_cells();
	SDL_RenderPresent(ren);
}

void Game::draw_grid() const {
	if (cam.scale >= 6.0) {
		SDL_SetRenderDrawColor(ren, 128, 128, 128, 0);
		const double wx0 = cam.x;
		const double wy0 = cam.y;
		const double wx1 = cam.x + win_width / cam.scale;
		const double wy1 = cam.y + win_height / cam.scale;

		const int x0 = static_cast<int>(std::floor(wx0));
		const int y0 = static_cast<int>(std::floor(wy0));
		const int x1 = static_cast<int>(std::ceil(wx1));
		const int y1 = static_cast<int>(std::ceil(wy1));

		for (int x = x0; x <= x1; x++) {
			SDL_FPoint aW{static_cast<float>(x), static_cast<float>(wy0)};
			SDL_FPoint bW{static_cast<float>(x), static_cast<float>(wy1)};

			SDL_FPoint aS{
				static_cast<float>((aW.x - cam.x) * cam.scale), static_cast<float>((aW.y - cam.y) * cam.scale)
			};
			SDL_FPoint bS{
				static_cast<float>((bW.x - cam.x) * cam.scale), static_cast<float>((bW.y - cam.y) * cam.scale)
			};

			SDL_RenderLine(ren, aS.x, aS.y, bS.x, bS.y);
		}
		for (int y = y0; y <= y1; ++y) {
			SDL_FPoint aW{static_cast<float>(wx0), static_cast<float>(y)};
			SDL_FPoint bW{static_cast<float>(wx1), static_cast<float>(y)};

			SDL_FPoint aS{
				static_cast<float>((aW.x - cam.x) * cam.scale), static_cast<float>((aW.y - cam.y) * cam.scale)
			};
			SDL_FPoint bS{
				static_cast<float>((bW.x - cam.x) * cam.scale), static_cast<float>((bW.y - cam.y) * cam.scale)
			};

			SDL_RenderLine(ren, aS.x, aS.y, bS.x, bS.y);
		}
	}
}

void Game::handle_mouse_input(const SDL_Event &e) {
	if (e.button.button == SDL_BUTTON_LEFT && !e.button.down) {
		const int x = static_cast<int>(e.button.x);
		const int y = static_cast<int>(e.button.y);

		if (selected_pattern) {
			place_selected_pattern(x, y);
			return;
		}
		SDL_FPoint worldP = screen_to_world(cam, x, y);
		if (Cell m{static_cast<int>(std::floor(worldP.x)), static_cast<int>(std::floor(worldP.y))};
			!set_active->contains(m)) {
			place_cell(m);
		} else {
			set_active->erase(m);

			set_potential->erase(m);
			set_potential_next->erase(m);
			for (int i = -2; i <= 2; i++)
				for (int j = -2; j <= 2; j++) {
					set_potential_next->insert(m + Cell(i, j));
				}
		}
	}


	if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		if (e.button.button == SDL_BUTTON_RIGHT) {
			dragging = true;
			drag_last_x = e.button.x;
			drag_last_y = e.button.y;
		}
	}
	if (e.type == SDL_EVENT_MOUSE_BUTTON_UP) {
		if (e.button.button == SDL_BUTTON_RIGHT) dragging = false;
	}
}

void Game::place_cell(const Cell &m) {
	set_active->insert(m);

	for (int y = -1; y <= 1; y++)
		for (int x = -1; x <= 1; x++)
			set_potential_next->insert(m + Cell(x, y));
}

void Game::handle_mouse_motion(const SDL_Event &e) {
	if (dragging) {
		const int dx = static_cast<int>(e.motion.x - drag_last_x);
		const int dy = static_cast<int>(e.motion.y - drag_last_y);
		drag_last_x = e.motion.x;
		drag_last_y = e.motion.y;

		cam.x -= dx / cam.scale;
		cam.y -= dy / cam.scale;
	}
}

void Game::handle_keyboard_input(const SDL_KeyboardEvent &e) {
	if (e.key == SDLK_SPACE && e.type != SDL_EVENT_KEY_UP) {
		simulate_generation();
	} else if (e.key == SDLK_R && e.type != SDL_EVENT_KEY_DOWN) {
		if (selected_pattern)
			selected_pattern->rotate_pattern_90();
	}
#ifndef __EMSCRIPTEN__
	else if (e.key == SDLK_1 && e.type == SDL_EVENT_KEY_DOWN) {
		select_pattern(1);
	} else if (e.key == SDLK_2 && e.type == SDL_EVENT_KEY_DOWN) {
		select_pattern(2);
	} else if (e.key == SDLK_3 && e.type == SDL_EVENT_KEY_DOWN) {
		select_pattern(3);
	} else if (e.key == SDLK_4 && e.type == SDL_EVENT_KEY_DOWN) {
		select_pattern(4);
	} else if (e.key == SDLK_5 && e.type == SDL_EVENT_KEY_DOWN) {
		select_pattern(5);
	} else if (e.key == SDLK_6 && e.type == SDL_EVENT_KEY_DOWN) {
		select_pattern(6);
	} else if (e.key == SDLK_7 && e.type == SDL_EVENT_KEY_DOWN) {
		select_pattern(7);
	} else if (e.key == SDLK_8 && e.type == SDL_EVENT_KEY_DOWN) {
		select_pattern(8);
	} else if (e.key == SDLK_9 && e.type == SDL_EVENT_KEY_DOWN) {
		deselect_pattern();
	}
#endif
}

void Game::handle_window_event(const SDL_Event &e) {
	SDL_Window *window = SDL_GetWindowFromID(e.window.windowID);
	if (win == window) {
		win_width = e.window.data1;
		win_height = e.window.data2;
	}
}

void Game::select_pattern(int p_number) {
	selected_pattern = Pattern(p_number);
}

void Game::draw_selected_pattern() {
	SDL_SetRenderDrawColor(ren, 128, 128, 128, 100);
	float mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	SDL_FPoint worldP = screen_to_world(cam, static_cast<int>(mouse_x), static_cast<int>(mouse_y));

	for (const auto &[x,y]: selected_pattern->pattern_info) {
		const SDL_FRect cellW{
			(std::floor(worldP.x) + static_cast<float>(x)), (std::floor(worldP.y) + static_cast<float>(y)), 1.f, 1.f
		};

		SDL_FRect cellS = world_to_screen(cam, cellW);

		SDL_RenderFillRect(ren, &cellS);
	}
}

void Game::place_selected_pattern(int x, int y) {
	SDL_FPoint worldP = screen_to_world(cam, x, y);
	for (const auto &[x,y]: selected_pattern->pattern_info) {
		place_cell(Cell{
			static_cast<int>(std::floor(worldP.x) + static_cast<float>(x)),
			static_cast<int>(std::floor(worldP.y) + static_cast<float>(y))
		});
	}
}

void Game::deselect_pattern() {
	selected_pattern.reset();
}

void Game::handle_mouse_wheel(const SDL_Event &e) {
	float mx, my;
	SDL_GetMouseState(&mx, &my);

	SDL_FPoint before = screen_to_world(cam, static_cast<int>(mx), static_cast<int>(my));

	double factor = (e.wheel.y > 0) ? 1.1 : (e.wheel.y < 0 ? 1.0 / 1.1 : 1.0);
	double new_scale = std::clamp(cam.scale * factor, cam.min_scale, cam.max_scale);

	if (new_scale != cam.scale) {
		cam.scale = new_scale;
		SDL_FPoint after = screen_to_world(cam, static_cast<int>(mx), static_cast<int>(my));
		cam.x += (before.x - after.x);
		cam.y += (before.y - after.y);
	}
}


void Game::simulate_generation() {
	set_active_next->clear();
	set_active_next->reserve(set_active->size());

	*set_potential = *set_potential_next;
	*set_potential_next = *set_active;

	for (const auto &c: *set_potential) {
		int neighbours =
				get_cell_state(Cell(c.x - 1, c.y - 1)) +
				get_cell_state(Cell(c.x - 0, c.y - 1)) +
				get_cell_state(Cell(c.x + 1, c.y - 1)) +
				get_cell_state(Cell(c.x - 1, c.y + 0)) +
				get_cell_state(Cell(c.x + 1, c.y + 0)) +
				get_cell_state(Cell(c.x - 1, c.y + 1)) +
				get_cell_state(Cell(c.x + 0, c.y + 1)) +
				get_cell_state(Cell(c.x + 1, c.y + 1));


		if (get_cell_state(c) == 1) {
			bool cell_lives_on = (neighbours == 2 || neighbours == 3);

			if (!cell_lives_on) {
				for (int y = -1; y <= 1; y++)
					for (int x = -1; x <= 1; x++)
						set_potential_next->insert(c + Cell(x, y));
			} else {
				set_active_next->insert(c);
			}
		} else {
			bool cell_to_life = (neighbours == 3);
			if (cell_to_life) {
				set_active_next->insert(c);


				for (int y = -1; y <= 1; y++)
					for (int x = -1; x <= 1; x++)
						set_potential_next->insert(c + Cell(x, y));
			} else {
			}
		}
	}
	std::swap(set_active, set_active_next);
	g_game->last_simulation = std::chrono::steady_clock::now();
}

void Game::draw_cells() const {
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	for (const Cell &c: *set_active) {
		if (is_point_in_viewport(c.x, c.y)) {
			SDL_FRect cellW{static_cast<float>(c.x), static_cast<float>(c.y), 1.f, 1.f};
			SDL_FRect cellS = world_to_screen(cam, cellW);
			SDL_RenderFillRect(ren, &cellS);
		}
	}
}

bool Game::is_point_in_viewport(int x_point, int y_point) const {
	const int x0 = static_cast<int>(std::floor(cam.x));
	const int y0 = static_cast<int>(std::floor(cam.y));
	const int x1 = static_cast<int>(std::ceil(cam.x + win_width / cam.scale));
	const int y1 = static_cast<int>(std::ceil(cam.y + win_height / cam.scale));


	return (x_point >= x0 - GRID_SIZE && x_point <= x1 + GRID_SIZE &&
	        y_point >= y0 - GRID_SIZE && y_point <= y1 + GRID_SIZE);
}

int Game::get_cell_state(const Cell &c) {
	return set_active->contains(c) ? 1 : 0;
}

void Game::set_simulation_speed(int speed) {
	simulation_speed = speed;
}

Game::~Game() {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

#ifdef __EMSCRIPTEN__
void deselect_pattern_wrapper() {
	g_game->deselect_pattern();
}

void select_pattern_wrapper(int p_number) {
	g_game->select_pattern(p_number);
}
void set_simulation_speed_wrapper(int speed) {
	g_game->set_simulation_speed(speed);
}

EMSCRIPTEN_BINDINGS(my_module) {
	emscripten::function("select_pattern", &select_pattern_wrapper);
	emscripten::function("deselect_pattern", &deselect_pattern_wrapper);
	emscripten::function("set_simulation_speed", &set_simulation_speed_wrapper);
}
#endif