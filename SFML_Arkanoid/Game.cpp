#include "Game.h"

Game::Game(const int width, const int height, const std::string& title)
	: 
	window(sf::VideoMode(width, height), title),
    board((float)width, (float)height),
    ball({ (float)width / 2, (float)height * (4.f / 5.f) })
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
        UpdateModel();
        DrawFrame();
        window.display();
    }
}

void Game::UpdateModel()
{
}

void Game::DrawFrame()
{
    board.Draw(window);
    ball.Draw(window);
}
