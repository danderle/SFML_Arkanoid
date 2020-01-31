#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Paddle.h"
#include "Brick.h"

enum class Hit
{
	NONE,
	WALL,
	BRICK,
	PADDLE,
};

class Ball
{
public:
	Ball() = delete;
	Ball(const sf::Vector2f pos);

	void Update(float dt);
	void Draw(sf::RenderWindow& wnd);
	bool CheckWallCollison(Board& brd);
	bool CheckPaddleCollision(Paddle& pdl, float timeStep);
	bool CheckBrickCollision(Brick& brk);
	void DoCollision(const sf::Vector2f vel, const sf::Vector2f pos);
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetCenter() const;
	sf::FloatRect GetRect() const;
	sf::Vector2f GetVelocity() const;
	float GetDistance(sf::Vector2f pos) const;
	void ResetVelocityX(const float x);
	void ResetX(const float x);
	void ResetY(const float y);
	void ReboundX();
	void ReboundY();
	bool LastHitPaddle() const;

private:
	void NormalizeVelocity();

private:
	sf::CircleShape circle;
	sf::Vector2f velocity;

	sf::Color background = sf::Color::Yellow;

	Hit LastHit = Hit::NONE;

	static constexpr float speed = 500;
	static constexpr float outlineThickness = -5;

public:
	static constexpr float Radius = 8;
	static constexpr float Diameter = Radius *2;
};

