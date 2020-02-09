#include "TextBox.h"

TextBox::TextBox(const std::string& string, sf::Vector2f position, const float padding, sf::Color outlineFill)
	:
	padding(padding)
{
	if (!font.loadFromFile(fontFilePath))
	{
		std::cout << "File not found: " << fontFilePath << std::endl;
		return;
	}
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(outlineFill);
	text.setFont(font);
	text.setString(string);
	shape.setOutlineThickness(-5);
	SetPosition(position);
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

float TextBox::GetHeight() const
{
	return shape.getGlobalBounds().height;
}

float TextBox::GetWidth() const
{
	return shape.getGlobalBounds().width;
}

sf::Vector2f TextBox::GetRighSideCenterline() const
{
	auto center = shape.getPosition();
	center.x += shape.getGlobalBounds().width;
	center.y += shape.getGlobalBounds().height / 2;
	return center;
}

void TextBox::SetPosition(sf::Vector2f position)
{
	shape.setPosition(position);
	auto textWidth = text.getLocalBounds().width;
	auto textHeight = text.getLocalBounds().height;
	shape.setSize({ textWidth + padding * 2, textHeight + padding * 2 });
	auto shapePos = shape.getSize();
	text.setPosition(position);
	text.setOrigin((textWidth - shapePos.x )/ 2 + text.getLocalBounds().left,
		(textHeight - shapePos.y) / 2 + text.getLocalBounds().top);
}
