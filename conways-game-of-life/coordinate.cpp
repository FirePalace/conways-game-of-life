#include "coordinate.h"

Coordinate transform_tiles_to_global(int tile_x, int tile_y)
{

	return Coordinate(tile_x * GRID_SIZE, tile_y * GRID_SIZE);

}

Coordinate transform_global_to_tiles(int tile_x, int tile_y)
{
	return Coordinate(tile_x / GRID_SIZE, tile_y / GRID_SIZE);
}
