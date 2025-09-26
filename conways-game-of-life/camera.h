#pragma once
#include <SDL3/SDL.h>
#include "common.h"
struct Camera {
	double x = 0.0;
	double y = 0.0;
	double scale = GRID_SIZE;
	double min_scale = 0.0;
	double max_scale = 10000.0;
};


inline SDL_FRect world_to_screen(const Camera& cam, SDL_FRect w) {
	return SDL_FRect{
		float((w.x - cam.x) * cam.scale),
		float((w.y - cam.y) * cam.scale),
		float(w.w * cam.scale),
		float(w.h * cam.scale)
	};
}


inline SDL_FPoint screen_to_world(const Camera& cam, int sx, int sy) {
	return SDL_FPoint{
		static_cast<float>(cam.x + sx / cam.scale),
		static_cast<float>(cam.y + sy / cam.scale)
	};
}