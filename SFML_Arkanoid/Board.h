#pragma once
#include <SFML/Graphics.hpp>

class Board
{
public:
	Board() = delete;
	Board(const float width, const float height);

	void Draw(sf::RenderWindow& wnd);

private:

	sf::RectangleShape background;

	sf::Color backgroundFill = sf::Color::Transparent;
	static constexpr float outlineThickness = 15;
};

