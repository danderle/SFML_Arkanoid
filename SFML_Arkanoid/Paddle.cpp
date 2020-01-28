#include "Paddle.h"

Paddle::Paddle(const int wndWidth, const int wndHeight)
	:
	outerPad({ Width, Height }),
	innerPad({ Width * (3.f/4.f), Height })
{
	outerPad.setPosition({ (float)wndWidth / 2 - Width / 2,  (float)wndHeight * 5/6 });
	SetInnerPaddlePosition(outerPad.getPosition());
	outerPad.setFillColor(outerBckgrd);
	innerPad.setFillColor(innerBckgrd);
}

void Paddle::Update(sf::Keyboard kbd, const float dt)
{
	auto curPos = GetPosition();
	if (kbd.isKeyPressed(sf::Keyboard::Left))
	{
		curPos.x += speed * dt * -1;
	}
	else if (kbd.isKeyPressed(sf::Keyboard::Right))
	{
		curPos.x += speed * dt * 1;
	}
	SetOuterPaddlePosition(curPos);
}

void Paddle::Draw(sf::RenderWindow& wnd)
{
	wnd.draw(outerPad);
	wnd.draw(innerPad);
}

sf::Vector2f Paddle::GetPosition() const
{
	return outerPad.getPosition();
}

void Paddle::SetOuterPaddlePosition(sf::Vector2f& curPos)
{
	outerPad.setPosition(curPos);
	SetInnerPaddlePosition(curPos);
}

bool Paddle::CheckBallCollision(Ball& ball)
{
	bool ballCollision = false;
	if (outerPad.getGlobalBounds().intersects(ball.GetRect()))
	{
		ballCollision = true;
		auto ballCenter = ball.GetCenter();
		auto paddlePos = outerPad.getPosition();
		auto ballVel = ball.GetVelocity();
		float y = ballVel.y > 0 ? paddlePos.y - Ball::Diameter : paddlePos.y + Height;
		float x = ballVel.x > 0 ? paddlePos.x - Ball::Diameter : paddlePos.x + Width;
		if (ballCenter.x > paddlePos.x && ballCenter.x < paddlePos.x + Width)
		{
			ball.ResetY(y);
			ball.ReboundY();
		}
		else if (ballCenter.y > paddlePos.y && ballCenter.y < paddlePos.y + Height)
		{
			ball.ResetX(x); 
			ball.ReboundX();
		}
		else if(ballVel.y > 0)
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
				x = std::abs(paddlePos.x + Width - ballCenter.x);
				y = std::abs(paddlePos.y - ballCenter.y);
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
			if (ballCenter.x < paddlePos.x)
			{
				x = std::abs(paddlePos.x - ballCenter.x);
				y = std::abs(paddlePos.y + Height - ballCenter.y);
			}
			else
			{
				x = std::abs(paddlePos.x + Width - ballCenter.x);
				y = std::abs(paddlePos.y + Height - ballCenter.y);
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
	return ballCollision;
}


//// Private Methods

void Paddle::SetInnerPaddlePosition(const sf::Vector2f outerPos)
{
	float x = outerPos.x + outerPad.getGlobalBounds().width / 2;
	x -= innerPad.getGlobalBounds().width / 2;
	innerPad.setPosition(x, outerPos.y);
}
