#include "Ball.h"

Ball::Ball(const sf::Vector2f pos)
	:
	circle({radius}),
	velocity(1,-1)
{
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

void Ball::DoWallCollision(const sf::Vector2i vel, const sf::Vector2f pos)
{
	velocity.x *= vel.x;
	velocity.y *= vel.y;
	circle.setPosition(pos);
	//play sound
}

sf::Vector2f Ball::GetPosition() const
{
	return circle.getPosition();
}
