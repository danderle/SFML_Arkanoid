#include "Game.h"

Game::Game(const std::string& title)
	: 
	window(sf::VideoMode(WndWidth, WndHeight), title),
    board((float)WndWidth, (float)WndHeight),
    ball({ (float)WndWidth / 2, (float)WndHeight * (4.f / 5.f) }),
    paddle(WndWidth, WndHeight)
{
}

void Game::Go()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        auto dt = clock.restart();
        auto elapsedTime = dt.asSeconds();
        while (elapsedTime > 0)
        {
            float step = std::min(0.0025f, elapsedTime);
            UpdateModel(step);
            elapsedTime -= step;
        }
        DrawFrame();
        window.display();
    }
}

void Game::UpdateModel(float timeStep)
{
    ball.Update(timeStep);
    if (board.CheckWallCollision(ball))
    {
        sound.Play(sound.brickfilePath);
    }
    paddle.Update(keybrd, timeStep);
    board.CheckWallCollision(paddle);
    if (paddle.CheckBallCollision(ball))
    {
        sound.Play(sound.padfilePath);
    }
}

void Game::DrawFrame()
{
    board.Draw(window);
    ball.Draw(window);
    paddle.Draw(window);
}
