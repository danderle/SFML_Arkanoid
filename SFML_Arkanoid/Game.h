#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Ball.h"
#include "Paddle.h"
#include "Sound.h"

class Game
{
public:
	Game() = delete;
	Game(const std::string& title);

	void Go();
	void UpdateModel(float dt);
	void DrawFrame();

public:
	static constexpr int WndWidth = 1000;
	static constexpr int WndHeight = 900;

private:
	sf::RenderWindow window;
	Board board;
	Ball ball;
	Paddle paddle;
	Sound sound;
	sf::Keyboard keybrd;
	sf::Clock clock;
};

