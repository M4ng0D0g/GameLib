#pragma once

#include <cstddef>
#include <vector>

struct Loc2 {
	int x;
	int y;
	int& col = x;
	int& row = y;
};

struct Size2 {
	size_t width;
	size_t height;
};

enum class Direction { STOP, UP, LEFT, DOWN, RIGHT };

