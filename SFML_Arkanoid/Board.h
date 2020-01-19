#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"

class Board
{
public:
	Board() = delete;
	Board(const float width, const float height);

	void Draw(sf::RenderWindow& wnd);
	void CheckWallCollision(Ball& ball);

private:

	sf::RectangleShape background;

	sf::Color backgroundFill = sf::Color::Transparent;
	static constexpr float padding = 15;
};

