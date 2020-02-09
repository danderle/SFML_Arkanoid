#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class TextBox
{
public:
	TextBox() = delete;
	TextBox(const std::string& text, sf::Vector2f position, const float padding, sf::Color outlineFill);

	void Draw(sf::RenderWindow& wnd);
	sf::Vector2f GetPosition() const;
	float GetHeight() const;
	float GetWidth() const;
	sf::Vector2f GetRighSideCenterline() const;
	void SetPosition(sf::Vector2f position);

private:
	sf::Text text;
	sf::Font font;
	sf::RectangleShape shape;

	float padding = 0;

	const std::string fontFilePath = "Resources\\Roboto-Bold.ttf";
};

