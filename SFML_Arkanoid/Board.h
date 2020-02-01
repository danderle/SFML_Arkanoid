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
	static constexpr float LeftPadding = 15;
	static constexpr float RightPadding = 15;
	static constexpr float TopPadding = 15 * 5;
	static constexpr float BottomPadding = 15;
	static constexpr float BorderThickness = 15;
	const float LeftBoundry;
	const float RightBoundry;
	const float TopBoundry;
	const float BottomBoundry;

private:
	sf::RectangleShape background;
	
	const sf::Color backgroundFill = sf::Color::Transparent;
};

