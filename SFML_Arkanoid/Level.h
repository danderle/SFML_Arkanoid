#pragma once
#include <vector>
#include "Brick.h"
#include "Board.h"

class Level
{
public:
	Level() = delete;

	static std::vector<Brick> Create(Board& brd, const int level);
};

