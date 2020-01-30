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
            if (brick.CheckBallCollision(ball))
            {
                float distance = brick.GetDistance(ball);
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
