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
	bool CheckWallCollision(Ball& ball);
	void CheckWallCollision(Paddle& paddle);

public:
	static constexpr float Padding = 15;
	const float LeftBoundry;
	const float RightBoundry;
	
private:
	sf::RectangleShape background;
	
	const sf::Color backgroundFill = sf::Color::Transparent;
};

