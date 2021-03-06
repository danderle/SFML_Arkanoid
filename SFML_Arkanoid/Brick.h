#pragma once
#include <SFML/Graphics.hpp>

class Brick
{
public:
	Brick() = delete;
	Brick(const sf::Vector2f position, sf::Color color);

	void Draw(sf::RenderWindow& wnd);
	
	void Destroy();
	bool IsDestroyed() const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetCenter() const;
	bool Intersects(sf::FloatRect rect);

public:
	static constexpr float Width = 90;
	static constexpr float Height = 30;

private:
	sf::RectangleShape shape;
	bool destroyed = false;
	const sf::Color green = sf::Color::Green;
	const sf::Color red = sf::Color::Red;
	const sf::Color yellow = sf::Color::Yellow;
	const sf::Color blue = sf::Color::Blue;

	static constexpr float boarderThickness = -1;
};

