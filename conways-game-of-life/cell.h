#pragma once
#include "coordinate.h"
class Cell {
	Coordinate coordinate;
public:
	Cell(int x, int y);
	void check_surroundings();
};