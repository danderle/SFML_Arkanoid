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


//// Private Methods

void Paddle::SetInnerPaddlePosition(const sf::Vector2f outerPos)
{
	float x = outerPos.x + outerPad.getGlobalBounds().width / 2;
	x -= innerPad.getGlobalBounds().width / 2;
	innerPad.setPosition(x, outerPos.y);
}
