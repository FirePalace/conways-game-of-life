#pragma once
#include <SDL3/SDL.h>
#include "common.h"
struct Camera {
	// world-space top-left visible point (in world units)
	double x = 0.0;
	double y = 0.0;
	// scale: screen pixels per one world unit (zoom)
	double scale = GRID_SIZE;      // e.g., 1 cell = 32 px
	double min_scale = 10.0;
	double max_scale = 2000.0;
};

// world -> screen
inline SDL_FRect world_to_screen(const Camera& cam, SDL_FRect w) {
	return SDL_FRect{
		float((w.x - cam.x) * cam.scale),
		float((w.y - cam.y) * cam.scale),
		float(w.w * cam.scale),
		float(w.h * cam.scale)
	};
}

// single point conversion (screen -> world)
inline SDL_FPoint screen_to_world(const Camera& cam, int sx, int sy) {
	return SDL_FPoint{
		float(cam.x + sx / cam.scale),
		float(cam.y + sy / cam.scale)
	};
}