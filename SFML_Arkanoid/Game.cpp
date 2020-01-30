#include "Game.h"

Game::Game(const std::string& title)
	: 
	window(sf::VideoMode(WndWidth, WndHeight), title),
    board((float)WndWidth, (float)WndHeight),
    ball({ (float)WndWidth / 2, (float)WndHeight * (4.f / 5.f) }),
    paddle(WndWidth, WndHeight)
{
    int yStep = -1;
    sf::Color color(255, 0, 0);
    for (int i = 0; i < 66; i++)
    {
        float x = (i * (int)Brick::Width) % 990 + Board::Padding;
        if (x == Board::Padding)
        {
            yStep++;
            if (yStep == 1)
            {
                color = sf::Color::Green;
            }
            else if (yStep == 2)
            {
                color = sf::Color::Yellow;
            }
        }
        float y = yStep * Brick::Height + 60;
        bricks.push_back({ {x,y}, color });
    }
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
    for (auto& brick : bricks)
    {
        if (!brick.IsDestroyed())
        {
            brick.CheckBallCollision(ball);
        }
    }
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
