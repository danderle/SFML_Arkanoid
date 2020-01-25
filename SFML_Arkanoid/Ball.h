#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
public:
	Ball() = delete;
	Ball(const sf::Vector2f pos);

	void Update(float dt);
	void Draw(sf::RenderWindow& wnd);
	void DoWallCollision(const sf::Vector2i vel, const sf::Vector2f pos);
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetCenter() const;
	sf::FloatRect GetRect() const;
	sf::Vector2i GetVelocity() const;
	void ResetX(const float x);
	void ResetY(const float y);
	void ReboundX();
	void ReboundY();

private:
	sf::CircleShape circle;
	sf::Vector2i velocity;

	sf::Color background = sf::Color::Yellow;

	static constexpr float speed = 500;
	static constexpr float outlineThickness = -5;

public:
	static constexpr float Radius = 8;
	static constexpr float Diameter = Radius *2;
};

