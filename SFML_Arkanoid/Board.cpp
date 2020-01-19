#include "Board.h"

Board::Board(const float width, const float height)
	:
	background({width - 2*outlineThickness, height - 2*outlineThickness})
{
	background.setFillColor(backgroundFill);
	background.setOutlineThickness(outlineThickness);
	background.setOutlineColor(sf::Color::Blue);
	background.setPosition(outlineThickness, outlineThickness);
}

void Board::Draw(sf::RenderWindow& wnd)
{
	wnd.draw(background);
}
