#pragma once
#include <SFML/Graphics.hpp>

class Board
{
public:
	Board() = delete;
	Board(const float width, const float height);

	void Draw(sf::RenderWindow& wnd);
	bool Contains(sf::Vector2f position);

public:
	static constexpr float Padding = 15;
	const float LeftBoundry;
	const float RightBoundry;
	const float TopBoundry;
	const float BottomBoundry;

private:
	sf::RectangleShape background;
	
	const sf::Color backgroundFill = sf::Color::Transparent;
};

