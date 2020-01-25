#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"

class Paddle
{
public:
	Paddle(const int wndWidth, const int wndHeight);

	void Update(sf::Keyboard kbd, const float dt);
	void Draw(sf::RenderWindow& wnd);
	sf::Vector2f GetPosition() const;
	void SetOuterPaddlePosition(sf::Vector2f& curPos);
	void CheckBallCollision(Ball& ball);

private: 
	void SetInnerPaddlePosition(const sf::Vector2f outerPos);

public:
	static constexpr float Width = 250;
	static constexpr float Height = 60;

private:
	sf::RectangleShape outerPad;
	sf::RectangleShape innerPad;

	static constexpr float speed = 400;
	

	const sf::Color outerBckgrd = sf::Color::Cyan;
	const sf::Color innerBckgrd = sf::Color::Red;
};

