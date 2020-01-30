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



void Brick::Destroy()
{
	destroyed = true;
}

bool Brick::IsDestroyed() const
{
	return destroyed;
}

sf::Vector2f Brick::GetPosition() const
{
	return shape.getPosition();
}

sf::Vector2f Brick::GetCenter() const
{
	auto pos = shape.getPosition();
	pos.x += Width / 2;
	pos.y += Height / 2;
	return pos;
}

bool Brick::Intersects(sf::FloatRect rect)
{
	return shape.getGlobalBounds().intersects(rect);
}


