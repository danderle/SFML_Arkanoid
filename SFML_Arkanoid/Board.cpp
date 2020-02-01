#include "Board.h"

Board::Board(const float width, const float height)
	:
	background({width - LeftPadding - RightPadding, height - TopPadding - BottomPadding }),
	LeftBoundry(LeftPadding),
	RightBoundry(width - RightPadding),
	TopBoundry(TopPadding),
	BottomBoundry(height - BottomPadding)
{
	background.setFillColor(backgroundFill);
	background.setOutlineThickness(BorderThickness);
	background.setOutlineColor(sf::Color::Blue);
	background.setPosition(LeftBoundry, TopBoundry);
}

void Board::Draw(sf::RenderWindow& wnd)
{
	wnd.draw(background);
}

bool Board::Contains(sf::Vector2f position)
{
	return background.getGlobalBounds().contains(position);
}


