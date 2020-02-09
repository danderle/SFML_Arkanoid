#include "Level.h"

std::vector<Brick> Level::Create(Board& brd, const int level)
{
    std::vector<Brick> bricks;

    int yStep = -1;
    switch (level)
    {
    case 1:
    {
        sf::Color color(255, 0, 0);
        for (int i = 0; i < 66; i++)
        {
            float x = (i * (int)Brick::Width) % 990 + brd.LeftBoundry;
            if (x == brd.LeftBoundry)
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
            float y = yStep * Brick::Height + brd.TopBoundry;
            bricks.push_back({ {x,y}, color });
        }
    }
    break;
    case 2:
    {
        sf::Color color(255, 0, 0);
        for (int i = 0; i < 60; i++)
        {
            float x = (i * (int)Brick::Width) % 900 + brd.LeftBoundry + 45;
            if (x == brd.LeftBoundry + 45)
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
            float y = yStep * Brick::Height + brd.TopBoundry + 60;
            bricks.push_back({ {x,y}, color });
        }
    }
    break;
    }
    return bricks;
}
