#pragma once
#include "common.h"
#include <memory>
#include <unordered_set>
struct Cell {

	int x;
	int y;

	Cell(int x, int y) : x{ x }, y{ y } {}
	Cell(std::pair<int, int> p) : x{ p.first }, y{ p.second } {}

	std::pair<int, int> transform_global_to_tiles(int x, int y) {
		return std::pair{ x / GRID_SIZE, y / GRID_SIZE };
	}


	bool operator==(const Cell& other) const noexcept {
		return x == other.x &&
			y == other.y;
	}
	Cell operator +(const Cell& other) const {
		return Cell(x + other.x, y + other.y);
	}

};
namespace std {
	template<>
	struct hash<Cell> {
		size_t operator()(const Cell& c) const noexcept {
			size_t h1 = std::hash<int>{}(c.x);
			size_t h2 = std::hash<int>{}(c.y);
			return h1 ^ (h2 + 0x9e3779b97f4a7c15ull + (h1 << 6) + (h1 >> 2));
		}
	};
}
static std::unique_ptr<std::unordered_set<Cell>> set_active = std::make_unique<std::unordered_set<Cell >>();
static std::unique_ptr<std::unordered_set<Cell>> set_active_next = std::make_unique<std::unordered_set<Cell >>();
static std::unique_ptr<std::unordered_set<Cell>> set_potential = std::make_unique<std::unordered_set<Cell >>();
static std::unique_ptr<std::unordered_set<Cell>> set_potential_next = std::make_unique<std::unordered_set<Cell >>();

std::pair<int, int> transform_tiles_to_global(std::pair<int, int> p);
std::pair<int, int> transform_global_to_tiles(std::pair<int, int> p);
