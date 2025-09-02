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
		//TODO only simulate once ready
		simulate_generation();
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

void Game::simulate_generation()
{

	*set_active = *set_active_next;
	set_active_next->clear();
	set_active_next->reserve(set_active->size());


	*set_potential = *set_potential_next;

	// We know all active cells this epoch have potential to stimulate next epoch
	*set_potential_next = *set_active;

	for (const auto& c : *set_potential)
	{
		// Cell has changed, apply rules

		// The secret of artificial life =================================================
		int nNeighbours =
			get_cell_state(Cell(c.x - 10, c.y - 10)) +
			get_cell_state(Cell(c.x - 0, c.y - 10)) +
			get_cell_state(Cell(c.x + 10, c.y - 10)) +
			get_cell_state(Cell(c.x - 10, c.y + 0)) +
			get_cell_state(Cell(c.x + 10, c.y + 0)) +
			get_cell_state(Cell(c.x - 10, c.y + 10)) +
			get_cell_state(Cell(c.x + 0, c.y + 10)) +
			get_cell_state(Cell(c.x + 10, c.y + 10));


		if (get_cell_state(c) == 1)
		{
			// if cell is alive and has 2 or 3 neighbours, cell lives on
			bool cell_lives_on = (nNeighbours == 2 || nNeighbours == 3);

			if (!cell_lives_on)
			{
				// Kill cell through activity omission		

				// Neighbours are stimulated for computation next epoch												
				for (int y = -1; y <= 1; y++)
					for (int x = -1; x <= 1; x++)
						set_potential_next->insert(c + Cell(x, y));
			}
			else
			{
				// No Change - Keep cell alive
				set_active_next->insert(c);
			}


		}
		else
		{
			int s = (nNeighbours == 3);
			if (s == 1)
			{
				// Spawn cell
				set_active_next->insert(c);

				// Neighbours are stimulated for computation next epoch												
				for (int y = -1; y <= 1; y++)
					for (int x = -1; x <= 1; x++)
						set_potential_next->insert(c + Cell(x, y));
			}
			else
			{
				// No Change - Keep cell dead						
			}
		}
		// ===============================================================================
	}
}

void Game::draw_cells()
{
	for (const Cell& c : *set_active) {
		//TODO
	}
}

int Game::get_cell_state(const Cell& c)
{
	return set_active->contains(c) ? 1 : 0;;
}



Game::~Game() {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
