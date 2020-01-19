#include "Ball.h"

Ball::Ball(const sf::Vector2f pos)
	:
	circle({radius})
{
	circle.setPosition(pos);
	circle.setFillColor(background);
	circle.setOutlineThickness(outlineThickness);
}

void Ball::Draw(sf::RenderWindow& wnd)
{
	wnd.draw(circle);
}
