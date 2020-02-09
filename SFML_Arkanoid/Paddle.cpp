#include "Paddle.h"

Paddle::Paddle(const int wndWidth, const int wndHeight)
	:
	outerPad({ Width, Height }),
	innerPad({ Width * (3.f/4.f), Height })
{
	outerPad.setPosition({ (float)wndWidth / 2 - Width / 2,  (float)wndHeight * 6/7 });
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

void Paddle::CheckWallCollision(Board& brd)
{
	auto curPos = GetPosition();
	if (curPos.x < brd.LeftBoundry)
		curPos.x = brd.LeftBoundry;
	else if (curPos.x + Paddle::Width > brd.RightBoundry)
		curPos.x = brd.RightBoundry - Paddle::Width;

	SetOuterPaddlePosition(curPos);
}

bool Paddle::Intersects(sf::FloatRect rect)
{
	return outerPad.getGlobalBounds().intersects(rect);;
}

sf::Vector2f Paddle::GetCenter() const
{
	auto pos = outerPad.getPosition();
	pos.x += Width / 2;
	pos.y += Height / 2;
	return pos;
}

sf::Vector2f Paddle::GetInnerRange() const
{
	auto range = GetCenter();
	range.y = range.x + Width * 1.f / 3.f / 2.f;
	range.x -= Width * 1.f / 3.f / 2.f;
	return range;
}

sf::Vector2f Paddle::GetMiddleRange() const
{
	auto range = GetCenter();
	range.y = range.x + Width * 2.f / 3.f / 2.f;
	range.x -= Width * 2.f / 3.f / 2.f;
	return range;
}

void Paddle::DrawLives(sf::RenderWindow& wnd, sf::Vector2f textboxPos)
{
	int space = 15;
	float divisor = 3;
	for (int i = 0; i < lives; i++)
	{
		sf::RectangleShape outer({ Width / divisor, Height / divisor });
		sf::RectangleShape inner({ Width / divisor * 3 / 4, Height / divisor });
		float x = textboxPos.x + space + i * outer.getGlobalBounds().width;
		outer.setPosition(x, textboxPos.y - outer.getGlobalBounds().height / 2);
		auto outerPos = outer.getPosition();
		float xinner = outerPos.x + outer.getGlobalBounds().width / 2;
		xinner -= inner.getGlobalBounds().width / 2;
		inner.setPosition(xinner, outerPos.y);
		outer.setFillColor(outerBckgrd);
		inner.setFillColor(innerBckgrd);
		wnd.draw(outer);
		wnd.draw(inner);
		space += 15;
	}
}

void Paddle::SubtractLife(int minusLife)
{
	lives -= minusLife;
}

bool Paddle::GameOver() const
{
	return lives <= 0;
}

void Paddle::Reset(sf::Vector2u wndSize)
{
	outerPad.setPosition({ (float)wndSize.x / 2 - Width / 2,  (float)wndSize.y * 6/7 });
	SetInnerPaddlePosition(outerPad.getPosition());
	lives = 3;
}

//// Private Methods

void Paddle::SetInnerPaddlePosition(const sf::Vector2f outerPos)
{
	float x = outerPos.x + outerPad.getGlobalBounds().width / 2;
	x -= innerPad.getGlobalBounds().width / 2;
	innerPad.setPosition(x, outerPos.y);
}
