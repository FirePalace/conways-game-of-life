#include "cell.h"

std::pair<int, int> transform_tiles_to_global(std::pair<int, int> p)
{

	return std::pair(p.first * GRID_SIZE, p.second * GRID_SIZE);

}

std::pair<int, int> transform_global_to_tiles(std::pair<int, int> p)
{
	return std::pair(p.first / GRID_SIZE, p.second / GRID_SIZE);
}
