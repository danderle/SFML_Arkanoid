#include "TextBox.h"

TextBox::TextBox(const std::string& string, sf::Vector2f position, const float padding = 0)
{
	if (!font.loadFromFile(fontFilePath))
	{
		std::cout << "File not found: " << fontFilePath << std::endl;
		return;
	}
	text.setFont(font);
	text.setString(string);
	text.setPosition(position.x, position.y - text.getGlobalBounds().height/2);
	auto textWidth = text.getGlobalBounds().width;
	auto textHeight = text.getGlobalBounds().height;
	shape.setSize({ textWidth + padding * 2, textHeight + padding * 2});
	auto textPosTop = text.getGlobalBounds().top;
	auto textPosLeft = text.getGlobalBounds().left;
	shape.setPosition(textPosLeft + textWidth / 2 - shape.getSize().x / 2,
		textPosTop + textHeight / 2  - shape.getSize().y / 2);
	shape.setFillColor(sf::Color::Transparent);
}

void TextBox::Draw(sf::RenderWindow& wnd)
{
	wnd.draw(shape);
	wnd.draw(text);
}

sf::Vector2f TextBox::GetPosition() const
{
	return shape.getPosition();
}

sf::Vector2f TextBox::GetRighSideCenterline() const
{
	auto center = shape.getPosition();
	center.x += shape.getGlobalBounds().width;
	center.y += shape.getGlobalBounds().height / 2;
	return center;
}
