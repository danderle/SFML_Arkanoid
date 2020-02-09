#include "Game.h"

Game::Game(const std::string& title)
	: 
	window(sf::VideoMode(WndWidth, WndHeight), title),
    board((float)WndWidth, (float)WndHeight),
    paddle(WndWidth, WndHeight),
    ball({ paddle.GetCenter().x - Ball::Radius, paddle.GetPosition().y - Ball::Diameter }),
    lives("Lives", {5, 0}, 15, sf::Color::Green),
    gameOver("           Game Over\n"
             "Press Enter to restart", { (float)WndWidth / 2, (float)WndHeight / 2}, 20, sf::Color::Red)
{
    SetTextBoxes();
    bricks = Level::Create(board, level);
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
            else if (event.type == sf::Event::KeyPressed)
            {
                if (keybrd.isKeyPressed(sf::Keyboard::Space))
                {
                    if (!paddle.GameOver())
                    {
                        ball.StartMotion();
                    }
                }
                else if (keybrd.isKeyPressed(sf::Keyboard::Enter))
                {
                    if (paddle.GameOver())
                    {
                        auto size = window.getSize();
                        paddle.Reset(size);
                        bricks = Level::Create(board, 1);
                    }
                }
            }
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
    ball.Update(paddle);
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
    if (bricks.empty())
    {
        ball.StopMotion();
        bricks = Level::Create(board, level);
        level++;
    }
}

void Game::DrawFrame()
{
    board.Draw(window);
    lives.Draw(window);
    ball.Draw(window);
    paddle.Draw(window);
    paddle.DrawLives(window, lives.GetRighSideCenterline());
    for (auto& brick : bricks)
    {
        if (!brick.IsDestroyed())
        {
            brick.Draw(window);
        }
    }
    if (paddle.GameOver())
    {
        gameOver.Draw(window);
        bricks.clear();
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

void Game::SetTextBoxes()
{
    auto pos = lives.GetPosition();
    auto height = lives.GetHeight();
    lives.SetPosition({ pos.x, board.TopBoundry / 2 - height / 2 - Board::BorderThickness / 2});
    pos = gameOver.GetPosition();
    auto width = gameOver.GetWidth();
    height = gameOver.GetHeight();
    gameOver.SetPosition({ (float)WndWidth / 2 - width / 2, (float)WndHeight / 2 - height / 2 });
}