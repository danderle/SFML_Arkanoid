#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class TextBox
{
public:
	TextBox() = delete;
	TextBox(const std::string& text, sf::Vector2f position, const float padding);

	void Draw(sf::RenderWindow& wnd);
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetRighSideCenterline() const;

private:
	sf::Text text;
	sf::Font font;
	sf::RectangleShape shape;

	const std::string fontFilePath = "Resources\\Roboto-Bold.ttf";
};

