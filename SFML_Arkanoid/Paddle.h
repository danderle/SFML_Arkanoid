#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class Paddle
{
public:
	Paddle(const int wndWidth, const int wndHeight);

	void Update(sf::Keyboard kbd, const float dt);
	void Draw(sf::RenderWindow& wnd);
	sf::Vector2f GetPosition() const;
	void SetOuterPaddlePosition(sf::Vector2f& curPos);
	void CheckWallCollision(Board& brd);
	bool Intersects(sf::FloatRect rect);

private: 
	void SetInnerPaddlePosition(const sf::Vector2f outerPos);

public:
	static constexpr float Width = 250.f;
	static constexpr float Height = 60.f;

private:
	sf::RectangleShape outerPad;
	sf::RectangleShape innerPad;

	static constexpr float speed = 400.f;

	const sf::Color outerBckgrd = sf::Color::Cyan;
	const sf::Color innerBckgrd = sf::Color::Red;
};

