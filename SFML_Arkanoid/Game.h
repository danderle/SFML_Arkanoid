#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Ball.h"
#include "Paddle.h"
#include "Sound.h"
#include "Brick.h"
#include "Level.h"

class Game
{
public:
	Game() = delete;
	Game(const std::string& title);

	void Go();
	void UpdateModel(float dt);
	void DrawFrame();

private:
	void CheckBricksToDestroy(Ball& ball);

public:
	static constexpr int WndWidth = 1020;
	static constexpr int WndHeight = 900;

private:
	sf::RenderWindow window;
	Board board;
	Ball ball;
	Paddle paddle;
	Sound sound;

	std::vector<Brick> bricks;

	sf::Keyboard keybrd;
	sf::Clock clock;
};

