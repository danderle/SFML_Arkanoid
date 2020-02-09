#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Ball.h"
#include "Paddle.h"
#include "Sound.h"
#include "Brick.h"
#include "Level.h"
#include "TextBox.h"

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
	void SetTextBoxes();

public:
	static constexpr int WndWidth = 1020;
	static constexpr int WndHeight = 900;

private:
	sf::RenderWindow window;
	Board board;
	Paddle paddle;
	Ball ball;
	TextBox lives;
	TextBox gameOver;
	Sound sound;

	std::vector<Brick> bricks;

	sf::Keyboard keybrd;
	sf::Clock clock;

	bool gameStarted = false;
	int level = 1;
};

