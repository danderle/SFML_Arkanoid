#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Ball.h"

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
	Ball ball;
	sf::Clock clock;
};

