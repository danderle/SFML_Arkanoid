#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include "Board.h"

class Game
{
public:
	Game() = delete;
	Game(const int width, const int height, const std::string& title);

	void Go();
	void UpdateModel();
	void DrawFrame();

private:
	sf::RenderWindow window;
	Board board;

};

