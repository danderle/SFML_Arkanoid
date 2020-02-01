#include "Ball.h"

Ball::Ball(const sf::Vector2f pos)
	:
	circle({Radius}),
	velocity(1.f,-1.f)
{
	NormalizeVelocity();
	circle.setPosition(pos);
	circle.setFillColor(background);
	circle.setOutlineThickness(outlineThickness);
}

void Ball::Update(float dt)
{
	float x = dt * speed * velocity.x;
	float y = dt * speed * velocity.y;
	auto curPos = circle.getPosition();
	curPos.x += x;
	curPos.y += y;
	circle.setPosition(curPos);
}

void Ball::Draw(sf::RenderWindow& wnd)
{
	wnd.draw(circle);
}

bool Ball::CheckWallCollison(Board& brd)
{
	bool collision = true;
	auto pos = GetPosition();
	sf::Vector2f leftBallPos(pos.x - Board::Padding, pos.y + Ball::Radius - Board::Padding);
	sf::Vector2f topBallPos(pos.x + Radius - Board::Padding, pos.y - Board::Padding);
	sf::Vector2f bottomBallPos(pos.x + Radius + Board::Padding, pos.y + Diameter + Board::Padding);
	sf::Vector2f rightBallPos(pos.x + Diameter + Board::Padding, pos.y + Radius + Board::Padding);

	sf::Vector2f vel(1.f, 1.f);
	if (!brd.Contains(leftBallPos))
	{
		ResetX(brd.LeftBoundry + 1);
		ReboundX();
	}
	else if (!brd.Contains(topBallPos))
	{
		ResetY(brd.TopBoundry + 1);
		ReboundY();
	}
	else if (!brd.Contains(bottomBallPos))
	{
		ResetY(brd.BottomBoundry - Diameter - 1);
		ReboundY();
	}
	else if (!brd.Contains(rightBallPos))
	{
		ResetX(brd.RightBoundry - Diameter -1);
		ReboundX();
	}
	else
	{
		collision = false;
	}
	lastHit = collision ? Hit::WALL : lastHit;
	return collision;
}

bool Ball::CheckPaddleCollision(Paddle& pdl, float timeStep)
{
	bool ballCollision = false;
	if (!LastHitPaddle())
	{
		if (pdl.Intersects(GetRect()))
		{
			ballCollision = true;
			lastHit = Hit::PADDLE;
			auto ballCenter = GetCenter();
			auto paddlePos = pdl.GetPosition();
			auto ballVel = GetVelocity();
			auto innerRange = pdl.GetInnerRange();
			auto middleRange = pdl.GetMiddleRange();
			auto pdlCenter = pdl.GetCenter();
			float xReset = ballCenter.x < pdlCenter.x ? paddlePos.x - Ball::Diameter - 1 : paddlePos.x + Paddle::Width + 1;
			float yReset = ballCenter.y < pdlCenter.y ? paddlePos.y - Ball::Diameter - 1: paddlePos.y + Paddle::Height + 1;
			if (ballCenter.x > paddlePos.x && ballCenter.x < paddlePos.x + Paddle::Width)
			{
				if (ballCenter.x > innerRange.x && ballCenter.x < innerRange.y)
				{
					ResetVelocityX(0.5f);
					ResetY(yReset);
					ReboundY();
				}
				else if (ballCenter.x > middleRange.x && ballCenter.x < middleRange.y)
				{
					ResetVelocityX(0.7f);
					ResetY(yReset);
					ReboundY();
				}
				else
				{
					ResetVelocityX(1.f);
					ResetY(yReset);
					ReboundY();
				}
			}
			else if (ballCenter.y > paddlePos.y && ballCenter.y < paddlePos.y + Paddle::Height)
			{
				ResetX(xReset);
				ReboundX();
			}
			else
			{
				float x;
				float y;
				if (ballCenter.x < paddlePos.x)
				{
					x = std::abs(paddlePos.x - ballCenter.x);
					y = std::abs(paddlePos.y - ballCenter.y);
				}
				else
				{
					x = std::abs(paddlePos.x + Paddle::Width - ballCenter.x);
					y = std::abs(paddlePos.y - ballCenter.y);
				}
				if (x <= y)
				{
					ResetVelocityX(1.f);
					ResetY(yReset);
					ReboundY();
				}
				else
				{
					ResetX(xReset);
					ReboundX();
				}
			}
		}
	}
	return ballCollision;
}

bool Ball::CheckBrickCollision(Brick& brk)
{
	bool ballCollision = false;
	if (brk.Intersects(GetRect()))
	{
		ballCollision = true;
		lastHit = Hit::BRICK;
		auto ballCenter = GetCenter();
		auto brickPos = brk.GetPosition();
		auto ballVel = GetVelocity();
		float yReset = ballVel.y > 0 ? brickPos.y - Ball::Diameter : brickPos.y + Brick::Height;
		float xReset = ballVel.x > 0 ? brickPos.x - Ball::Diameter : brickPos.x + Brick::Width;
		if (ballCenter.x > brickPos.x && ballCenter.x < brickPos.x + Brick::Width)
		{
			ResetY(yReset);
			ReboundY();
		}
		else if (ballCenter.y > brickPos.y && ballCenter.y < brickPos.y + Brick::Height)
		{
			ResetX(xReset);
			ReboundX();
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
				x = std::abs(brickPos.x + Brick::Width - ballCenter.x);
				y = std::abs(brickPos.y - ballCenter.y);
			}
			if (x <= y)
			{
				ResetY(yReset);
				ReboundY();
			}
			else
			{
				ResetX(xReset);
				ReboundX();
			}
		}
		else if (ballVel.y < 0)
		{
			float x;
			float y;
			if (ballCenter.x < brickPos.x)
			{
				x = std::abs(brickPos.x - ballCenter.x);
				y = std::abs(brickPos.y + Brick::Height - ballCenter.y);
			}
			else
			{
				x = std::abs(brickPos.x + Brick::Width - ballCenter.x);
				y = std::abs(brickPos.y + Brick::Height - ballCenter.y);
			}
			if (x <= y)
			{
				ResetY(yReset);
				ReboundY();
			}
			else
			{
				ResetX(xReset);
				ReboundX();
			}
		}
	}
	return ballCollision;
}

void Ball::DoCollision(const sf::Vector2f vel, const sf::Vector2f pos)
{
	velocity.x *= vel.x;
	velocity.y *= vel.y;
	circle.setPosition(pos);
}

sf::Vector2f Ball::GetPosition() const
{
	return circle.getPosition();
}

sf::Vector2f Ball::GetCenter() const
{
	auto pos = circle.getPosition();
	return sf::Vector2f(pos.x + Radius, pos.y + Radius);
}

sf::FloatRect Ball::GetRect() const
{
	return circle.getGlobalBounds();
}

sf::Vector2f Ball::GetVelocity() const
{
	return velocity;
}

float Ball::GetDistance(sf::Vector2f pos) const
{
	auto ballcenter = GetCenter();
	float x = std::abs(ballcenter.x - pos.x);
	float y = std::abs(ballcenter.y - pos.y);
	return std::sqrt(x * x + y * y);
}

void Ball::ResetVelocityX(const float x)
{
	int sign = 1;
	if (velocity.x < 0)
		sign *= -1;
	velocity.x = x * sign;
	NormalizeVelocity();
}

void Ball::ResetX(const float x)
{
	circle.setPosition({x, GetPosition().y});
}

void Ball::ResetY(const float y)
{
	circle.setPosition({ GetPosition().x, y });
}

void Ball::ReboundX()
{
	velocity.x *= -1;
}

void Ball::ReboundY()
{
	velocity.y *= -1;
}

bool Ball::LastHitPaddle() const
{
	return lastHit == Hit::PADDLE;
}

void Ball::NormalizeVelocity()
{
	float x = velocity.x * velocity.x;
	float y = velocity.y * velocity.y;
	float length = std::sqrt(x + y);
	velocity.x /= length;
	velocity.y /= length;
}
