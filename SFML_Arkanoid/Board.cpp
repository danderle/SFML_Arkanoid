#include "Board.h"

Board::Board(const float width, const float height)
	:
	width(width),
	height(height),
	background({width - 2* Padding, height - 2* Padding })
{
	background.setFillColor(backgroundFill);
	background.setOutlineThickness(Padding);
	background.setOutlineColor(sf::Color::Blue);
	background.setPosition(Padding, Padding);
}

void Board::Draw(sf::RenderWindow& wnd)
{
	wnd.draw(background);
}

void Board::CheckWallCollision(Ball& ball)
{
	auto pos = ball.GetPosition();
	sf::Vector2f LeftBallPos(pos.x - Padding, pos.y + Ball::Radius - Padding);
	sf::Vector2f topBallPos(pos.x + Ball::Radius - Padding, pos.y - Padding);
	sf::Vector2f bottomBallPos(pos.x + Ball::Radius + Padding, pos.y + Ball::Diameter + Padding);
	sf::Vector2f rightBallPos(pos.x + Ball::Diameter + Padding, pos.y + Ball::Radius + Padding);
	
	sf::Vector2i vel(1, 1);
	if (!background.getGlobalBounds().contains(LeftBallPos))
	{
		vel.x *= -1;
		pos.x = Padding;
	}
	else if (!background.getGlobalBounds().contains(topBallPos))
	{
		vel.y *= -1;
		pos.y = Padding;
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

void Board::CheckWallCollision(Paddle& paddle)
{
	auto curPos = paddle.GetPosition();
	if (curPos.x - Padding < 0)
		curPos.x = Padding;
	else if (curPos.x + Paddle::Width + Padding > width)
		curPos.x = width - Board::Padding - Paddle::Width;
	
	paddle.SetOuterPaddlePosition(curPos);
}
