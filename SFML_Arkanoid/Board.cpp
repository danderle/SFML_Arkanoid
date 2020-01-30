#include "Board.h"

Board::Board(const float width, const float height)
	:
	background({width - 2* Padding, height - 2* Padding }),
	LeftBoundry(Padding),
	RightBoundry(width - Padding),
	TopBoundry(Padding),
	BottomBoundry(height - Padding)
{
	background.setFillColor(backgroundFill);
	background.setOutlineThickness(Padding);
	background.setOutlineColor(sf::Color::Blue);
	background.setPosition(Padding, Padding);
}

void Board::Draw(sf::RenderWindow& wnd)
{
	wnd.draw(background);
}

bool Board::Contains(sf::Vector2f position)
{
	return background.getGlobalBounds().contains(position);
}


