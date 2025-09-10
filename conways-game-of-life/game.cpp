#include "game.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif
#include <algorithm>
#include <iostream>

Game::Game(const char* title, int width, int height, SDL_WindowFlags flags)
	: win_height{ height }, win_width{ width }
{

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
	std::cout << "Entering loop\n";
	loop();
}

void Game::loop()
{
	#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg(one_loop_iteration, this, 0, true);
	#else
	while (!shutdown_requested) {
		one_loop_iteration(this);
	}
	#endif
	std::cout << "Exiting loop\n";
}

 void Game::one_loop_iteration(void* userData) {
	Game* game = static_cast<Game*>(userData);
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

	}
	game->draw_frame();


}

void Game::draw_frame(){
	SDL_SetRenderDrawColor(ren, 20, 20, 20, 255);
	SDL_RenderClear(ren);
	draw_grid();

	draw_cells();
	SDL_RenderPresent(ren);
}

void Game::draw_grid() const {
	// compute visible world rect
	SDL_SetRenderDrawColor(ren, 128, 128, 128, 0);
	double wx0 = cam.x;
	double wy0 = cam.y;
	double wx1 = cam.x + win_width / cam.scale;
	double wy1 = cam.y + win_height / cam.scale;

	// choose grid cell range
	int x0 = (int)std::floor(wx0);
	int y0 = (int)std::floor(wy0);
	int x1 = (int)std::ceil (wx1);
	int y1 = (int)std::ceil (wy1);

	// draw grid lines (optional)
	// (skip if too dense to avoid overdraw at high zoom-out)
	if (cam.scale >= 6.0) {
		for (int x = x0; x <= x1; ++x) {
			SDL_FPoint aW{ (float)x, (float)wy0 };
			SDL_FPoint bW{ (float)x, (float)wy1 };

			SDL_FPoint aS{ (float)((aW.x - cam.x) * cam.scale), (float)((aW.y - cam.y) * cam.scale) };
			SDL_FPoint bS{ (float)((bW.x - cam.x) * cam.scale), (float)((bW.y - cam.y) * cam.scale) };

			SDL_RenderLine(ren, aS.x, aS.y, bS.x, bS.y);
		}
		for (int y = y0; y <= y1; ++y) {
			SDL_FPoint aW{ (float)wx0, (float)y };
			SDL_FPoint bW{ (float)wx1, (float)y };

			SDL_FPoint aS{ (float)((aW.x - cam.x) * cam.scale), (float)((aW.y - cam.y) * cam.scale) };
			SDL_FPoint bS{ (float)((bW.x - cam.x) * cam.scale), (float)((bW.y - cam.y) * cam.scale) };

			SDL_RenderLine(ren, aS.x, aS.y, bS.x, bS.y);
		}
	}
}

void Game::handle_mouse_input(const SDL_Event& e)
{
	if (e.button.button == SDL_BUTTON_LEFT && !e.button.down) {
		int x = e.button.x;
		int y = e.button.y;


		SDL_FPoint worldP = screen_to_world(cam, x, y);
		Cell m{ static_cast<int>(std::floor(worldP.x)), static_cast<int>(std::floor(worldP.y)) };
		set_active_next->insert(m);
		set_active->insert(m);

		for (int y = -1; y <= 1; y++)
			for (int x = -1; x <= 1; x++)
				set_potential_next->insert(m + Cell(x, y));
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

void Game::handle_mouse_motion(const SDL_Event& e) {

	if (dragging) {
		int dx = e.motion.x - drag_last_x;
		int dy = e.motion.y - drag_last_y;
		drag_last_x = e.motion.x;
		drag_last_y = e.motion.y;

		// screen delta -> world delta
		cam.x -= dx / cam.scale;
		cam.y -= dy / cam.scale;
	}
}
void Game::handle_keyboard_input(const SDL_KeyboardEvent& e)
{
	if (e.key == SDLK_SPACE && e.type != SDL_EVENT_KEY_UP) {
		simulate_generation();
	}
}

void Game::handle_mouse_wheel(const SDL_Event &e) {
	float mx, my;
	SDL_GetMouseState(&mx, &my);

	SDL_FPoint before = screen_to_world(cam, mx, my);

	// choose your zoom step (1.1 feels nice)
	double factor = (e.wheel.y > 0) ? 1.1 : (e.wheel.y < 0 ? 1.0/1.1 : 1.0);
	double new_scale = std::clamp(cam.scale * factor, cam.min_scale, cam.max_scale);

	// re-anchor: keep the world point under the cursor stationary
	if (new_scale != cam.scale) {
		cam.scale = new_scale;
		SDL_FPoint after = screen_to_world(cam, mx, my);
		cam.x += (before.x - after.x);
		cam.y += (before.y - after.y);
	}
}



void Game::simulate_generation()
{

	*set_active = *set_active_next;
	set_active_next->clear();
	set_active_next->reserve(set_active->size());


	*set_potential = *set_potential_next;
	*set_potential_next = *set_active;

	for (const auto& c : *set_potential)
	{
		int neighbours =
			get_cell_state(Cell(c.x - 1, c.y - 1)) +
			get_cell_state(Cell(c.x - 0, c.y - 1)) +
			get_cell_state(Cell(c.x + 1, c.y - 1)) +
			get_cell_state(Cell(c.x - 1, c.y + 0)) +
			get_cell_state(Cell(c.x + 1, c.y + 0)) +
			get_cell_state(Cell(c.x - 1, c.y + 1)) +
			get_cell_state(Cell(c.x + 0, c.y + 1)) +
			get_cell_state(Cell(c.x + 1, c.y + 1));


		if (get_cell_state(c) == 1)
		{

			bool cell_lives_on = (neighbours == 2 || neighbours == 3);

			if (!cell_lives_on)
			{

				for (int y = -1; y <= 1; y++)
					for (int x = -1; x <= 1; x++)
						set_potential_next->insert(c + Cell(x, y));
			}
			else
			{
				set_active_next->insert(c);
			}


		}
		else
		{
			bool cell_to_life = (neighbours == 3);
			if (cell_to_life)
			{
				set_active_next->insert(c);


				for (int y = -1; y <= 1; y++)
					for (int x = -1; x <= 1; x++)
						set_potential_next->insert(c + Cell(x, y));
			}
			else
			{

			}
		}

	}
}

void Game::draw_cells() const {
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	for (const Cell& c : *set_active) {
		// world rectangle: one unit per cell
		SDL_FRect cellW{ static_cast<float>(c.x), static_cast<float>(c.y), 1.f, 1.f };

		// transform to screen space using the camera
		SDL_FRect cellS = world_to_screen(cam, cellW);

		SDL_RenderFillRect(ren, &cellS);
	}
}

int Game::get_cell_state(const Cell& c)
{
	return set_active->contains(c) ? 1 : 0;;
}



Game::~Game() {
	std::cout << "Destructor called"<< std::endl;
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	std::cout << "Destructor called 2"<< std::endl;
}