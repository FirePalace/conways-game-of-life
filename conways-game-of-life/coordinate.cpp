#include "coordinate.h"

Cell transform_tiles_to_global(int tile_x, int tile_y)
{

	return Cell(tile_x * GRID_SIZE, tile_y * GRID_SIZE);

}

Cell transform_global_to_tiles(int tile_x, int tile_y)
{
	return Cell(tile_x / GRID_SIZE, tile_y / GRID_SIZE);
}
