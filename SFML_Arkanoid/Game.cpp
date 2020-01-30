#include "Game.h"

Game::Game(const std::string& title)
	: 
	window(sf::VideoMode(WndWidth, WndHeight), title),
    board((float)WndWidth, (float)WndHeight),
    ball({ (float)WndWidth / 2, (float)WndHeight * (4.f / 5.f) }),
    paddle(WndWidth, WndHeight)
{
    bricks = Level::Create(1);
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
        float fith = elapsedTime / 5.f;
        while (elapsedTime > 0)
        {
            float step = std::min(fith, elapsedTime);
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
    if (ball.CheckWallCollison(board))
    {
        sound.Play(sound.brickfilePath);
    }
    paddle.Update(keybrd, timeStep);
    paddle.CheckWallCollision(board);
    if (ball.CheckPaddleCollision(paddle, timeStep))
    {
        sound.Play(sound.padfilePath);
    }
    CheckBricksToDestroy(ball);
}

void Game::DrawFrame()
{
    board.Draw(window);
    ball.Draw(window);
    paddle.Draw(window);
    for (auto& brick : bricks)
    {
        if (!brick.IsDestroyed())
        {
            brick.Draw(window);
        }
    }
}

void Game::CheckBricksToDestroy(Ball& ball)
{
    int index = 0;
    float min = 100;
    int toDestroy = -1;
    for (auto& brick : bricks)
    {
        if (!brick.IsDestroyed())
        {
            if (ball.CheckBrickCollision(brick))
            {
                float distance = ball.GetDistance(brick.GetCenter());
                if (distance < min)
                {
                    min = distance;
                    toDestroy = index;
                }
            }
        }
        index++;
    }
    if (toDestroy > -1)
    {
        bricks[toDestroy].Destroy();
        sound.Play(sound.brickfilePath);
    }
}
