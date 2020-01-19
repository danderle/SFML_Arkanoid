#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
public:
	Ball() = delete;
	Ball(const sf::Vector2f pos);

	void Draw(sf::RenderWindow& wnd);

private:
	sf::CircleShape circle;

	sf::Color background = sf::Color::Yellow;

	static constexpr float radius = 8;
	static constexpr float outlineThickness = -5;
};

