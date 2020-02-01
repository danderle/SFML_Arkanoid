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


//// Private Methods

void Paddle::SetInnerPaddlePosition(const sf::Vector2f outerPos)
{
	float x = outerPos.x + outerPad.getGlobalBounds().width / 2;
	x -= innerPad.getGlobalBounds().width / 2;
	innerPad.setPosition(x, outerPos.y);
}
