#include "Board.h"

Board::Board(const float width, const float height)
	:
	background({width - 2* Padding, height - 2* Padding }),
	LeftBoundry(Padding),
	RightBoundry(width - Padding)
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

bool Board::CheckWallCollision(Ball& ball)
{
	bool collision = false;
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
	{
		ball.DoWallCollision(vel, pos);
		collision = true;
	}
	return collision;
}

void Board::CheckWallCollision(Paddle& paddle)
{
	auto curPos = paddle.GetPosition();
	if (curPos.x < LeftBoundry)
		curPos.x = LeftBoundry;
	else if (curPos.x + Paddle::Width > RightBoundry)
		curPos.x = RightBoundry - Paddle::Width;
	
	paddle.SetOuterPaddlePosition(curPos);
}
