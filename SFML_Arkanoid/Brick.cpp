#include "Brick.h"

Brick::Brick(const sf::Vector2f position, sf::Color color)
	:
	shape({Width, Height})
{
	shape.setFillColor(color);
	shape.setPosition(position);
	shape.setOutlineThickness(boarderThickness);
	shape.setOutlineColor(sf::Color::Black);
}

void Brick::Draw(sf::RenderWindow& wnd)
{
	wnd.draw(shape);
}

bool Brick::CheckBallCollision(Ball& ball)
{
	bool ballCollision = false;
	if (shape.getGlobalBounds().intersects(ball.GetRect()))
	{
		ballCollision = true;
		auto ballCenter = ball.GetCenter();
		auto brickPos = shape.getPosition();
		auto ballVel = ball.GetVelocity();
		float y = ballVel.y > 0 ? brickPos.y - Ball::Diameter : brickPos.y + Height;
		float x = ballVel.x > 0 ? brickPos.x - Ball::Diameter : brickPos.x + Width;
		if (ballCenter.x > brickPos.x&& ballCenter.x < brickPos.x + Width)
		{
			ball.ResetY(y);
			ball.ReboundY();
		}
		else if (ballCenter.y > brickPos.y&& ballCenter.y < brickPos.y + Height)
		{
			ball.ResetX(x);
			ball.ReboundX();
		}
		else if (ballVel.y > 0)
		{
			float x;
			float y;
			if (ballCenter.x < brickPos.x)
			{
				x = std::abs(brickPos.x - ballCenter.x);
				y = std::abs(brickPos.y - ballCenter.y);
			}
			else
			{
				x = std::abs(brickPos.x + Width - ballCenter.x);
				y = std::abs(brickPos.y - ballCenter.y);
			}
			if (x <= y)
			{
				ball.ReboundY();
			}
			else
			{
				ball.ReboundX();
			}
		}
		else if (ballVel.y < 0)
		{
			float x;
			float y;
			if (ballCenter.x < brickPos.x)
			{
				x = std::abs(brickPos.x - ballCenter.x);
				y = std::abs(brickPos.y + Height - ballCenter.y);
			}
			else
			{
				x = std::abs(brickPos.x + Width - ballCenter.x);
				y = std::abs(brickPos.y + Height - ballCenter.y);
			}
			if (x <= y)
			{
				ball.ReboundY();
			}
			else
			{
				ball.ReboundX();
			}
		}
	}
	destroyed = ballCollision;
	return ballCollision;
}

bool Brick::IsDestroyed() const
{
	return destroyed;
}
