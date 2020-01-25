#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"

class Board
{
public:
	Board() = delete;
	Board(const float width, const float height);

	void Draw(sf::RenderWindow& wnd);
	void CheckWallCollision(Ball& ball);
	void CheckWallCollision(Paddle& paddle);

public:
	static constexpr float Padding = 15;
	
private:
	sf::RectangleShape background;
	float width;
	float height;
	sf::Color backgroundFill = sf::Color::Transparent;
};

