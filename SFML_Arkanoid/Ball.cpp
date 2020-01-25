#include "Ball.h"

Ball::Ball(const sf::Vector2f pos)
	:
	circle({Radius}),
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

sf::Vector2f Ball::GetCenter() const
{
	auto pos = circle.getPosition();
	return sf::Vector2f(pos.x + Radius, pos.y + Radius);
}

sf::FloatRect Ball::GetRect() const
{
	return circle.getGlobalBounds();
}

sf::Vector2i Ball::GetVelocity() const
{
	return velocity;
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
