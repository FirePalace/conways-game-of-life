#pragma once
#include "common.h"
struct Coordinate {
	int x;
	int y;

	Coordinate(int x, int y) : x{ x }, y{ y } {}

	Coordinate transform_global_to_tiles() const {
		return Coordinate(x / GRID_SIZE, y / GRID_SIZE);
	}

};
Coordinate transform_tiles_to_global(int tile_x, int tile_y);
Coordinate transform_global_to_tiles(int tile_x, int tile_y);
