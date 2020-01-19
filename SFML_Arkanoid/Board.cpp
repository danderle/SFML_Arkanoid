#include "Board.h"

Board::Board(const float width, const float height)
	:
	background({width - 2* padding, height - 2* padding })
{
	background.setFillColor(backgroundFill);
	background.setOutlineThickness(padding);
	background.setOutlineColor(sf::Color::Blue);
	background.setPosition(padding, padding);
}

void Board::Draw(sf::RenderWindow& wnd)
{
	wnd.draw(background);
}

void Board::CheckWallCollision(Ball& ball)
{
	auto pos = ball.GetPosition();
	sf::Vector2f LeftBallPos(pos.x - padding, pos.y + Ball::radius - padding);
	sf::Vector2f topBallPos(pos.x + Ball::radius - padding, pos.y - padding);
	sf::Vector2f bottomBallPos(pos.x + Ball::radius + padding, pos.y + Ball::Diameter + padding);
	sf::Vector2f rightBallPos(pos.x + Ball::Diameter + padding, pos.y + Ball::radius + padding);
	
	sf::Vector2i vel(1, 1);
	if (!background.getGlobalBounds().contains(LeftBallPos))
	{
		vel.x *= -1;
		pos.x = padding;
	}
	else if (!background.getGlobalBounds().contains(topBallPos))
	{
		vel.y *= -1;
		pos.y = padding;
	}
	else if (!background.getGlobalBounds().contains(bottomBallPos))
	{
		vel.y *= -1;
		pos.y =  background.getSize().y - 1;
	}
	else if (!background.getGlobalBounds().contains(rightBallPos))
	{
		vel.x *= -1;
		pos.x = background.getSize().x - 1;
	}

	if (vel.x == -1 || vel.y == -1)
		ball.DoWallCollision(vel, pos);
}
