#pragma once
#include <vector>
#include "Brick.h"
#include "Board.h"

class Level
{
public:
	Level() = default;

	static std::vector<Brick> Create(int level);
private:

};

