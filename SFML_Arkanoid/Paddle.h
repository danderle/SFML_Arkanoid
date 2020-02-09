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
	sf::Vector2f GetCenter() const;
	sf::Vector2f GetInnerRange() const;
	sf::Vector2f GetMiddleRange() const;
	void DrawLives(sf::RenderWindow& wnd, sf::Vector2f textboxPosition);
	void SubtractLife(int minusLife);
	bool GameOver() const;
	void Reset(sf::Vector2u wndSize);

private: 
	void SetInnerPaddlePosition(const sf::Vector2f outerPos);

public:
	static constexpr float Width = 250.f;
	static constexpr float Height = 30.f;

private:
	sf::RectangleShape outerPad;
	sf::RectangleShape innerPad;

	int lives = 3;
	static constexpr float speed = 400.f;

	const sf::Color outerBckgrd = sf::Color::Cyan;
	const sf::Color innerBckgrd = sf::Color::Red;
};

